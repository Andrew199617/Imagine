#include "SaveLogger.h"
#include <iostream>
#include <ostream>
#include "ConfigReader.h"
#include "GameLogger.h"
#include <windows.h>
#include "ImgnViewport.h"
#include "ImgnProperties.h"
#include "ImgnComponent.h"
#include "Physics/PhysicsTypeDefs.hpp"
#include "gtx/string_cast.hpp"

#define SETCOMPONENTDATA(type) if (name == typeid(type*).name()) \
{ \
	type* val = reinterpret_cast<type*>(DisplayData->values[iVar]); \
	componentsData[ObjNum][j][iVar] = std::to_string(*val); \
} \

#define SETVALUESOFCOMPONENT(type) if (name == typeid(type*).name()) \
{ \
	if(componentsData[i][j][iVar] != "") \
	{ \
		*meOutput << "			iVar = " << iVar << "; "; \
		*meOutput << "" << #type << "* val" << std::to_string(iVar) << " = reinterpret_cast<" << #type << "*>(displayData->values[iVar]);" << " "; \
		*meOutput << "*val" << std::to_string(iVar) << " = (" << #type << ")" << componentsData[i][j][iVar] << ";" << "\n"; \
	} \
} 

using std::endl;
using std::cout;
using std::ifstream;
using std::ios;

SaveLogger* SaveLogger::saveLogger = 0;

void SaveLogger::RemoveEntity(int EntityToRemove)
{
	for (int j = EntityToRemove * Imgn::MAXENTITYDATA; j < currentEntityDataType - Imgn::MAXENTITYDATA; j+=Imgn::MAXENTITYDATA)
	{
		for (int k = j; k < j + Imgn::MAXENTITYDATA; ++k)
		{
			entities[k][1] = entities[k + Imgn::MAXENTITYDATA][1];
		}
	}
	for (int iCurEntity = EntityToRemove; iCurEntity < curNumEntities-1; ++iCurEntity)
	{
		for (int jCurComponent = 0; jCurComponent < Imgn::MAX_COMPONENTS_PERENTITY; ++jCurComponent)
		{
			components[iCurEntity][jCurComponent] = components[iCurEntity + 1][jCurComponent];
			componentNames[iCurEntity][jCurComponent] = componentNames[iCurEntity + 1][jCurComponent];
			for (int kCurComponentData = 0; kCurComponentData < Imgn::MAX_VARIABLES; ++kCurComponentData)
			{
				componentsData[iCurEntity][jCurComponent][kCurComponentData] = componentsData[iCurEntity + 1][jCurComponent][kCurComponentData];
			}
		}
	}
	for (int k = (curNumEntities-1) * Imgn::MAXENTITYDATA; k < curNumEntities * Imgn::MAXENTITYDATA; ++k)
	{
		entities[k][0] = "";
		entities[k][1] = "";
	}
	int iCurEntity = curNumEntities - 1;
	for (int jCurComponent = 0; jCurComponent < Imgn::MAX_COMPONENTS_PERENTITY; ++jCurComponent)
	{
		components[iCurEntity][jCurComponent] = 0;
		componentNames[iCurEntity][jCurComponent] = "";
		for (int kCurComponentData = 0; kCurComponentData < Imgn::MAX_VARIABLES; ++kCurComponentData)
		{
			componentsData[iCurEntity][jCurComponent][kCurComponentData] = "";
		}
	}
	curNumEntities--;
	currentEntityDataType -= Imgn::MAXENTITYDATA;
	
}

SaveLogger::SaveLogger()
{
	memset(components, 0, sizeof(components));
	Open();
	autoSave = true;
}

SaveLogger::~SaveLogger()
{
}

void SaveLogger::Open(const char* filename)
{
	if (currentFilename == filename) { return; }
	else { DeleteData(); currentFilename = filename; }

	ifstream meInput(filename);

	if (!meInput.good())
	{
		string s = filename;
		GameLogger::log("file failed to load..." + s);
		GameLogger::shutdownLog();
		exit(1);
	}
	buffer << meInput.rdbuf();
	string saveFile = buffer.str();
	buffer = std::stringstream(saveFile);

	string word;
	currentEntityDataType = 0;
	entityData = 0;
	curNumEntities = 0;
	while (buffer.good())
	{

		buffer >> word;
		if (word == "Components")
		{
			//AddComponents
			LoadComponents(word);
			//Finished adding object move on to next object.
			curNumEntities++;
		}
		else
		{
			//Add Data for current Entity.
			LoadEntityData(word);
		}


	}

	meInput.close();
	GameLogger::log("Save Logger file loaded");
}

void SaveLogger::LoadEntityData(string &word)
{
	entities[currentEntityDataType][entityData] = word;
	buffer >> word;
	entityData++;

	entities[currentEntityDataType][entityData] = word;

	if (currentEntityDataType >= Imgn::MAX_ENTITIES * Imgn::MAXENTITYDATA - 1)
	{
		GameLogger::log("To many Keys In Save Logger File");
		GameLogger::shutdownLog();
		exit(1);
	}
	else
	{
		currentEntityDataType++;
		entityData = 0;
	}
}

void SaveLogger::LoadComponents(string &word)
{
	buffer >> word;
	componentNames[curNumEntities][0] = word;
	int currentComponent = 1;
	buffer >> word;
	while (buffer.good())
	{
		buffer >> word;
		if (word == "{")
		{
			LoadComponentData(currentComponent);
		}
		else if (word == "}")
		{
			break;
		}
		else
		{
			componentNames[curNumEntities][currentComponent] = word;
			currentComponent++;
		}
	}
}

void SaveLogger::LoadComponentData(int currentComponent)
{
	string word;
	int currentData = 0;
	while (buffer.good())
	{
		buffer >> word;
		if (word == "}")
		{
			break;
		}
		else if (word.at(0) == '(')
		{
			string vec = word;
			while (word.at(word.length() - 1) != ')')
			{
				buffer >> word;
				vec += word;
			}
			componentsData[curNumEntities][currentComponent - 1][currentData] = vec;
			currentData++;
		}
		else
		{
			componentsData[curNumEntities][currentComponent - 1][currentData] = word;
			currentData++;
		}
	}
}

void SaveLogger::DeleteData()
{
	if (currentFilename != "")
	{
		numUniqueComponents = 0;
		uniqueComponentNames.clear();
		currentFilename = "";
		memset(componentNames, 0, sizeof(componentNames));
		memset(entities, 0, sizeof(entities));
		memset(componentsData, 0, sizeof(componentsData));
		memset(components, 0, sizeof(components));
	}
}

bool SaveLogger::shutdownLog()
{
	if (autoSave)
	{
		ImgnViewport::entityManager.SaveEntities();
		if ( !WriteToSaveFile() ) 
		{
			return false;
		}
		GenerateUniqueComponents();
		WriteToEntityManager();
	}
	return true;
}

void SaveLogger::WriteToEntityManager()
{
	ifstream meInput("..\\GraphicsPad\\EntityManager.cpp");
	if (meInput)
	{
		std::stringstream emBuffer;
		emBuffer << meInput.rdbuf();
		std::ofstream meOutput("..\\GraphicsPad\\EntityManager.cpp", ios::out);
		string s;
		while (emBuffer.good())
		{
			getline(emBuffer, s);
			meOutput << s << "\n";
			if (s == "//Add Here")
			{
				for (std::list<string>::iterator it = uniqueComponentNames.begin(); it != uniqueComponentNames.end(); ++it)
				{
					string className = *it;
					string path = "";
					if ((*it).find("::") != std::string::npos) {
						className = (*it).substr((*it).find("::") + 2);
					}
					if (*it == "Imgn::RigidBody" || *it == "RigidBody")
					{
						path = "Physics/";
					}
					else if (*it == "BoxCollider" || *it == "SphereCollider")
					{
						path = "CollisionDetection/";
					}
					meOutput << "#include \"" << path << className << ".h\"" << "\n";
				}
				meOutput << "\n";
				meOutput << "ImgnComponent ** EntityManager::GetComponents(int objNum)" << "\n";
				meOutput << "{" << "\n";
				meOutput << "	ImgnComponent** components;" << "\n";
				meOutput << "	string name = saveLogger->GetName(objNum);" << "\n";
				meOutput << "	int numComponents = 1;" << "\n";
				meOutput << "	Imgn::DisplayData* displayData;" << "\n";
				meOutput << "	int iVar = 0;" << "\n\n";
				WriteComponentData(&meOutput);
				meOutput << "\n";
				/*meOutput << "if (numComponents == 0)" << "\n";
				meOutput << "{" << "\n";
				meOutput << "	delete[] components;" << "\n";
				meOutput << "	return 0;" << "\n";
				meOutput << "}" << "\n";*/
				meOutput << "	if(numComponents == 1)" << "{ components = new ImgnComponent*[1]; }" << "\n";
				
				meOutput << "	numComponent[objNum] += numComponents;" << "\n";
				meOutput << "	return components;" << "\n";
				meOutput << "}" << "\n";
				break;
			}
		}
		meOutput.close();

	}
}

bool SaveLogger::WriteToSaveFile()
{
	ofstream out(currentFilename, ios::out | ios::trunc);
	if (out.is_open())
	{
		for (int i = 0; i < curNumEntities; ++i)
		{
			int index = i * Imgn::MAXENTITYDATA;
			for (int jEntityData = index; jEntityData < index + Imgn::MAXENTITYDATA; ++jEntityData)
			{
				out << entities[jEntityData][0] << " " << entities[jEntityData][1] << "\n";
			}
			WriteComponents(&out, i);

			out << "}\n\n";
		}
		out.close();
	}
	else
	{
		cout << "could not save file canceled close so that you did not lose data." << std::endl;
		return false;
	}
	return true;
}

void SaveLogger::WriteComponents(ofstream* out, int iEntity)
{
	*out << "Components " << componentNames[iEntity][0] << " {\n";
	int numComponents = std::stoi(componentNames[iEntity][0]);
	for (int j = 1; j < numComponents+1; ++j)
	{
		*out << "    " << componentNames[iEntity][j] << "\n";
		if (components[iEntity][j])
		{
			Imgn::DisplayData* displayData = components[iEntity][j]->GetDisplayData();
			if (displayData)
			{
				*out << "    {" << "\n";
				for (int iCompData = 0; iCompData < displayData->numValues; ++iCompData)
				{
					if (componentsData[iEntity][j][iCompData] == "")
					{
						continue;
					}
					*out << "        " << componentsData[iEntity][j][iCompData] << "\n";
				}
				*out << "    }" << "\n";
			}
		}
	}
}

void SaveLogger::WriteComponentData(std::ofstream* meOutput)
{
	for (int i = 0; i < curNumEntities; ++i)
	{
		int numComponents = std::stoi(componentNames[i][0]);
		if (numComponents <= 2)
		{
			continue;
		}
		*meOutput << "	if (name == \"" << entities[i * Imgn::MAXENTITYDATA][1] << "\")" << "\n";
		*meOutput << "	{																		" << "\n";
		*meOutput << "		components = new ImgnComponent*[" << (numComponents - 1) << "];" << "\n";
		for (int j = 3; j < numComponents + 1; ++j)
		{
			if (componentNames[i][j] == "RigidBody")
			{
				*meOutput << "		components[numComponents] = new " << "Imgn::" << componentNames[i][j] << "();" << "\n";
			}
			else
			{
				*meOutput << "		components[numComponents] = new " << componentNames[i][j] << "();" << "\n";
			}
			Imgn::DisplayData* displayData = components[i][j]->GetDisplayData();
			if (displayData)
			{
				*meOutput << "		displayData = components[numComponents]->GetDisplayData();" << "\n";
				*meOutput << "		if (displayData)" << "\n";
				*meOutput << "		{" << "\n";
				for (int iVar = 0; iVar < displayData->numValues; iVar++)
				{
					std::string name = displayData->typeName[iVar];
					SETVALUESOFCOMPONENT(int)
					else SETVALUESOFCOMPONENT(float)
					else SETVALUESOFCOMPONENT(double)
					else SETVALUESOFCOMPONENT(long)
					else SETVALUESOFCOMPONENT(short)
					else SETVALUESOFCOMPONENT(unsigned int)
					else SETVALUESOFCOMPONENT(char*)
					else SETVALUESOFCOMPONENT(bool)
					else if (name == typeid(glm::vec3*).name()) 
					{ 
						if (componentsData[i][j][iVar] != "") 
						{ 
							*meOutput << "			iVar = " << iVar << "; "; 
							*meOutput << "" << "glm::detail::tvec3<float>" << "* val" << std::to_string(iVar) << " = reinterpret_cast<" << "glm::detail::tvec3<float>" << "*>(displayData->values[iVar]);" << " ";
							*meOutput << "*val" << std::to_string(iVar) << " = " << "glm::vec3" << componentsData[i][j][iVar] << ";" << "\n"; 
						} \
					}
					else SETVALUESOFCOMPONENT(glm::vec3)
				}
				*meOutput << "		}" << "\n";
			}
			*meOutput << "		numComponents++;" << "\n";
		}
		*meOutput << "	}" << "\n";
	}
}

void SaveLogger::GenerateUniqueComponents()
{
	for (int i = 0; i < curNumEntities; ++i)
	{
		int numComponents = std::stoi(componentNames[i][0]);
		for (int j = 3; j < numComponents + 1; ++j)
		{
			uniqueComponentNames.push_back(componentNames[i][j]);
		}
	}
	uniqueComponentNames.sort();
	uniqueComponentNames.unique();
}

int SaveLogger::GetNumObjs()
{
	return curNumEntities;
}

void SaveLogger::SetEntityName(string oldName, string name)
{
	int objNum = GetObjNum(oldName);
	entities[objNum * Imgn::MAXENTITYDATA][1] = name;
}

string SaveLogger::GetName(int objId)
{
	int currentObjId = objId * Imgn::MAXENTITYDATA;
	return entities[currentObjId][1];
}

string SaveLogger::GetSceneName(int objId)
{
	int currentObjId = objId * Imgn::MAXENTITYDATA;
	return entities[currentObjId + Imgn::SceneName][1];
}

void SaveLogger::AddObj(string SceneName, string ObjName)
{
	int index = curNumEntities * Imgn::MAXENTITYDATA;

	entities[index][0] = "Name";
	if(ObjName == " ") entities[index][1] = "DefaultObject_" + std::to_string(curNumEntities + 1);
	else entities[index][1] = ObjName + "_" + std::to_string(curNumEntities + 1);

	index++;
	entities[index][0] = "SceneName";
	entities[index][1] = SceneName;

	componentNames[curNumEntities][0] = "1";
	componentNames[curNumEntities][1] = "MeshComponent";
	curNumEntities++;
	currentEntityDataType = index + 1;
	ImgnViewport::entityManager.AddEntity();
}

void SaveLogger::SetComponent(int ObjNum, int componentNum, ImgnComponent* component)
{
	components[ObjNum][componentNum] = component;
}

void SaveLogger::AddComponent(string objName, string ComponentName, ImgnComponent* Component)
{
	int currentObjNum = GetObjNum(objName);

	AddComponent(currentObjNum, ComponentName,Component);
}

void SaveLogger::AddComponent(int objNum, string ComponentName, ImgnComponent* Component)
{
	int numComponents = std::stoi(componentNames[objNum][0]);
	++numComponents;

	componentNames[objNum][0] = std::to_string(numComponents);
	componentNames[objNum][numComponents] = ComponentName;
	components[objNum][numComponents] = Component;
}

int SaveLogger::GetObjNum(string objName)
{
	int currentObjNum = -1;
	for (int i = 0; i < currentEntityDataType; i += Imgn::MAXENTITYDATA)
	{
		if (entities[i][0] == "Name")
		{
			currentObjNum++;
		}
		if (entities[i][1] == objName)
		{
			break;
		}
	}	
	return currentObjNum;
}

void SaveLogger::AddComponentData(int ObjNum, string ComponentName, Imgn::DisplayData* DisplayData)
{
	if (!DisplayData || !DisplayData->hasData)
	{
		return;
	}
	int numComponents = std::stoi(componentNames[ObjNum][0]);
	int j = 0;
	for (int i = 1; i < numComponents+1; ++i)
	{
		if (componentNames[ObjNum][i] == ComponentName)
		{
			j = i;
			break;
		}
	}
	for (int iVar = 0; iVar < DisplayData->numValues; iVar++)
	{
		std::string name = DisplayData->typeName[iVar];
		SETCOMPONENTDATA(int)
		else SETCOMPONENTDATA(float)
		else SETCOMPONENTDATA(double)
		else SETCOMPONENTDATA(long)
		else SETCOMPONENTDATA(short)
		else SETCOMPONENTDATA(unsigned int)
		else SETCOMPONENTDATA(bool)
		else if (name == typeid(string*).name())
		{
			string* c = reinterpret_cast<string*>(DisplayData->values[iVar]);
			componentsData[ObjNum][j][iVar] = *c;
		}
		else if (name == typeid(glm::vec3*).name())
		{
			glm::vec3* c = reinterpret_cast<glm::vec3*>(DisplayData->values[iVar]);
			string vecBad = glm::to_string(*c);
			string vec = vecBad.substr(5, vecBad.npos);
			componentsData[ObjNum][j][iVar] = vec;
		}
	}
}

string SaveLogger::GetComponentName(int objNum, int componentNum)
{
	return componentNames[objNum][componentNum];
}

glm::vec3 SaveLogger::GetSpatialData(int curEntity, int CurDataNum)
{
	return glm::vec3(GetVec3FromString(componentsData[curEntity][2][CurDataNum]));
}

string SaveLogger::GetMeshData(int curEntity, int CurDataNum)
{
	return componentsData[curEntity][1][CurDataNum];
}

glm::vec3 SaveLogger::GetVec3FromString(string vec)
{
	ConfigReader* configReader = ConfigReader::Instance();
	glm::vec3 vecFromString;
	int curXYZ = 0;
	string curNum = "";
	for (unsigned i = 1; i < vec.length(); ++i)
	{
		if (vec[i] == ',' || vec[i] == ')')
		{
			switch (curXYZ)
			{
			case 0:
				vecFromString.x = configReader->GetFloatFromString(curNum);
				break;
			case 1:
				vecFromString.y = configReader->GetFloatFromString(curNum);
				break;
			case 2:
				vecFromString.z = configReader->GetFloatFromString(curNum);
				break;
			}
			curXYZ++;
			curNum = "";
			continue;
		}
		curNum += vec[i];
	}
	return vecFromString;
}
