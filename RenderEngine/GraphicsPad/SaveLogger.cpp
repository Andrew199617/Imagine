#include "SaveLogger.h"
#include <iostream>
#include <ostream>
#include "ConfigReader.h"
#include "GameLogger.h"
#include <windows.h>
#include "OriginalGame.h"
#include "ImgnProperties.h"
#include "ImgnComponent.h"
#define SETCOMPONENTDATA(type) if (name == typeid(type*).name()) \
{ \
	type* val = reinterpret_cast<type*>(DisplayData->values[iVar]); \
	componentsData[ObjNum][j][iVar] = std::to_string(*val); \
} \

#define SETVALUESOFCOMPONENT(type) if (name == typeid(type*).name()) \
{ \
*meOutput << "				" << #type << "* val" << std::to_string(iVar) << " = reinterpret_cast<" << #type << "*>(displayData->values[iVar]);" << "\n"; \
*meOutput << "				*val" << std::to_string(iVar) << " = " << componentsData[i][j][iVar] << ";" << "\n"; \
} 

using std::endl;
using std::cout;
using std::ifstream;
using std::ios;

SaveLogger* SaveLogger::saveLogger = 0;

SaveLogger::SaveLogger()
{
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
	string s;
	currentEntityDataType = 0;
	entityData = 0;
	curNumEntities = 0;
	while (buffer.good())
	{

		buffer >> word;
		if (word == "Components")
		{
			//AddComponents
			AddComponentsForEntity(word);
			//Finished adding object move on to next object.
			curNumEntities++;
		}
		else
		{
			//Add Data for current Entity.
			AddEntityData(word, s);
		}


	}

	meInput.close();
	GameLogger::log("Save Logger file loaded");
}

void SaveLogger::AddEntityData(string &word, string &s)
{
	entities[currentEntityDataType][entityData] = word;
	buffer >> word;
	entityData++;

	if (word[0] == '"')
	{
		word[0] = ' ';
		inQuotes = true;
	}
	else
	{
		entities[currentEntityDataType][entityData] = word;
	}
	while (inQuotes)
	{
		for (unsigned int j = 1; j < word.length(); j++)
		{
			if (word[j] == '"')
			{
				inQuotes = false;
				word[j] = ' ';
				break;
			}
			else if (word[j] == ',')
			{
				entities[currentEntityDataType][entityData] = s;
				s = "";
				entityData++;
			}
			else
			{
				s += word[j];
			}

		}
		entities[currentEntityDataType][entityData] = s;
		entityData++;
		s = "";
	}
	if (currentEntityDataType > Imgn::MAX_ENTITIES*Imgn::MAXENTITYDATA)
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

void SaveLogger::AddComponentsForEntity(string &word)
{
	buffer >> word;
	componentNames[curNumEntities][0] = word;
	int currentComponent = 1;
	buffer >> word;
	while (true)
	{
		buffer >> word;
		if (word == "}")
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

void SaveLogger::DeleteData()
{
	if (currentFilename != "")
	{
		for (int j = 0; j < currentEntityDataType; j++)
		{
			for (int j2 = 0; j2 < Imgn::MAXDATALENGTH; j2++)
			{
				entities[j][j2] = " ";
			}
			for (int j2 = 0; j2 < Imgn::MAX_COMPONENTS + 1; j2++)
			{
				componentNames[j][j2] = " ";
			}
		}
	}
}

bool SaveLogger::shutdownLog()
{
	if (autoSave)
	{
		ofstream out(currentFilename, ios::out | ios::trunc);
		if (out.is_open())
		{
			for (int i = 0; i < curNumEntities; ++i)
			{
				int index = i * Imgn::MAXENTITYDATA;
				out << entities[index][0] << " " << entities[index][1] << "\n";
				index++;
				out << entities[index][0] << " " << entities[index][1] << "\n";
				index++;
				out << entities[index][0] << " " << '"' << entities[index][1] << "," << entities[index][2] << "," << entities[index][3] << '"' << "\n";
				index++;
				out << entities[index][0] << " " << '"' << entities[index][1] << "," << entities[index][2] << "," << entities[index][3] << '"' << "\n";
				index++;
				out << entities[index][0] << " " << '"' << entities[index][1] << "," << entities[index][2] << "," << entities[index][3] << '"' << "\n";

				out << "Components " << componentNames[i][0] << " {\n";
				int numComponents = std::stoi(componentNames[i][0]);
				for (int j = 0; j < numComponents; ++j)
				{
					out << "    " << componentNames[i][j + 1] << "\n";
				}
				out << "}\n\n";
			}
			out.close();
		}
		else
		{
			cout << "could not save file canceled close so that you did not lose data." << std::endl;
			return false;
		}
		
		GenerateUniqueComponents();
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
					for (std::list<string>::iterator it = uniqueComponents.begin(); it != uniqueComponents.end(); ++it)
					{
						meOutput << "#include \"" << *it << ".h\"" << "\n";
					}
					meOutput << "\n";
					meOutput << "ImgnComponent ** EntityManager::GetComponents(int objNum)" << "\n";
					meOutput << "{" << "\n";
					meOutput << "	ImgnComponent** components = new ImgnComponent*[Imgn::MAX_COMPONENTS - 2];" << "\n";
					meOutput << "	string name = saveLogger->GetName(objNum);" << "\n";
					meOutput << "	int numComponents = 0;" << "\n";
					meOutput << "	Imgn::DisplayData* displayData;" << "\n";
					meOutput << "	int iVar = 0;" << "\n\n";
					WriteComponentData(&meOutput);
					meOutput << "\n";
					/*if (numComponents == 0)
					{
						delete[] components;
						return 0;
					}*/
					meOutput << "	numComponent[objNum] += numComponents;										" << "\n";
					meOutput << "	return components;															" << "\n";
					meOutput << "}																				" << "\n";
					break;
				}
			}
			meOutput.close();

		}
	}
	return true;
}

void SaveLogger::WriteComponentData(std::ofstream* meOutput)
{
	for (int i = 0; i < curNumEntities; ++i)
	{
		*meOutput << "	if (name == \"" << entities[i * Imgn::MAXENTITYDATA][1] << "\")" << "\n";
		*meOutput << "	{																		" << "\n";
		int numComponents = std::stoi(componentNames[i][0]);
		for (int j = 3; j < numComponents + 1; ++j)
		{
			*meOutput << "		components[numComponents] = new " << componentNames[i][j] << "();" << "\n";
			Imgn::DisplayData* displayData = components[i][j]->GetDisplayData();
			if (displayData)
			{
				*meOutput << "		displayData = components[numComponents]->GetDisplayData();" << "\n";
				*meOutput << "		if (displayData)" << "\n";
				*meOutput << "		{" << "\n";
				for (int iVar = 0; iVar < displayData->numValues; iVar++)
				{
					*meOutput << "			iVar = " << iVar << ";\n";
					const char* name = displayData->typeName[iVar];
					SETVALUESOFCOMPONENT(int)
					else SETVALUESOFCOMPONENT(float)
					else SETVALUESOFCOMPONENT(double)
					else SETVALUESOFCOMPONENT(long)
					else SETVALUESOFCOMPONENT(short)
					else SETVALUESOFCOMPONENT(unsigned int)
					else SETVALUESOFCOMPONENT(char*)
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
			uniqueComponents.push_back(componentNames[i][j]);
		}
	}
	uniqueComponents.sort();
	uniqueComponents.unique();
}

int SaveLogger::GetNumObjs()
{
	return curNumEntities;
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
	int index = curNumEntities * 5;

	entities[index][0] = "Name";
	if(ObjName == " ") entities[index][1] = "DefaultObject" + std::to_string(curNumEntities + 1);
	else entities[index][1] = ObjName + std::to_string(curNumEntities + 1);

	index++;
	entities[index][0] = "SceneName";
	entities[index][1] = SceneName;

	index++;
	entities[index][0] = "Position";
	entities[index][1] = "0.0";
	entities[index][2] = "0.0";
	entities[index][3] = "0.0";
	
	index++;
	entities[index][0] = "Rotate";
	entities[index][1] = "0.0";
	entities[index][2] = "1.0";
	entities[index][3] = "0.0";

	index++;
	entities[index][0] = "Scale";
	entities[index][1] = "1.0";
	entities[index][2] = "1.0";
	entities[index][3] = "1.0";

	componentNames[curNumEntities][0] = "2";
	componentNames[curNumEntities][1] = "SpatialComponent";
	componentNames[curNumEntities][2] = "MeshComponent";
	curNumEntities++;
	currentEntityDataType = index + 1;
	OriginalGame::entityManager.AddEntity();
}

void SaveLogger::LoadComponent(int ObjNum, int componentNum, ImgnComponent* component)
{
	components[ObjNum][componentNum] = component;
}

void SaveLogger::AddNewComponent(string objName, string ComponentName, ImgnComponent* Component)
{
	int currentObjNum = -1;
	for (int i = 0; i < currentEntityDataType; ++i)
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
	AddNewComponent(currentObjNum, ComponentName,Component);
}

void SaveLogger::AddNewComponent(int objNum, string ComponentName, ImgnComponent* Component)
{
	int numComponents = std::stoi(componentNames[objNum][0]);
	componentNames[objNum][0] = std::to_string(numComponents + 1);
	componentNames[objNum][numComponents + 1] = ComponentName;
	components[objNum][numComponents + 1] = Component;
}

void SaveLogger::AddComponentData(int ObjNum, string ComponentName, Imgn::DisplayData* DisplayData)
{
	int numComponents = std::stoi(componentNames[ObjNum][0]);
	int j = 0;
	for (int i = 3; i < numComponents+1; ++i)
	{
		if (componentNames[ObjNum][i] == ComponentName)
		{
			j = i;
			break;
		}
	}
	for (int iVar = 0; iVar < DisplayData->numValues; iVar++)
	{
		const char* name = DisplayData->typeName[iVar];
		SETCOMPONENTDATA(int)
		else SETCOMPONENTDATA(float)
		else SETCOMPONENTDATA(double)
		else SETCOMPONENTDATA(long)
		else SETCOMPONENTDATA(short)
		else SETCOMPONENTDATA(unsigned int)
		else if (name == typeid(char**).name())
		{
			char** c = reinterpret_cast<char**>(DisplayData->values[iVar]);
			componentsData[ObjNum][j][iVar] = string(*c);
		}
	}
}

glm::vec3 SaveLogger::GetPosition(string objName)
{
	for (int i = 0; i < currentEntityDataType; i++)
	{
		if (entities[i][1] == objName)
		{
			return glm::vec3(ConfigReader::Instance()->GetFloatFromString(entities[i+2][1]), ConfigReader::Instance()->GetFloatFromString(entities[i + 2][2]), ConfigReader::Instance()->GetFloatFromString(entities[i + 2][3]));
		}
	}
	GameLogger::log("could not find Position for Obj:" + objName);
	cout << "check log" << endl;
	return glm::vec3();
}

glm::vec3 SaveLogger::GetRotate(string objName)
{
	for (int i = 0; i < currentEntityDataType; i++)
	{
		if (entities[i][1] == objName)
		{
			return glm::vec3(ConfigReader::Instance()->GetFloatFromString(entities[i + 3][1]), ConfigReader::Instance()->GetFloatFromString(entities[i + 3][2]), ConfigReader::Instance()->GetFloatFromString(entities[i + 3][3]));
		}
	}
	GameLogger::log("could not find Rotate for Obj:" + objName);
	cout << "check log" << endl;
	return glm::vec3();
}

glm::vec3 SaveLogger::GetScale(string objName)
{
	for (int i = 0; i < currentEntityDataType; i++)
	{
		if (entities[i][1] == objName)
		{
			return glm::vec3(ConfigReader::Instance()->GetFloatFromString(entities[i + 4][1]), ConfigReader::Instance()->GetFloatFromString(entities[i + 4][2]), ConfigReader::Instance()->GetFloatFromString(entities[i + 4][3]));
		}
	}
	GameLogger::log("could not find Scale for Obj:" + objName);
	cout << "check log" << endl;
	return glm::vec3();
}

string SaveLogger::GetComponentName(int objNum, int componentNum)
{
	return componentNames[objNum][componentNum];
}
