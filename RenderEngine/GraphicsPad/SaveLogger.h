#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include "glm.hpp"
#include "gtx/quaternion.hpp"
#include "EntityData.h"
#include <list>
class ImgnComponent;

namespace Imgn
{
	struct DisplayData;
	const int MAXDATALENGTH = 4;
	enum EntityDataTypes
	{
		Name,
		SceneName,
		MAXENTITYDATA
	};
}
using std::string;
using std::ofstream;

class SaveLogger
{
	SaveLogger();
	~SaveLogger();
public:
	static SaveLogger* Instance() { if (!saveLogger) { saveLogger = new SaveLogger(); } return saveLogger; }
	
	void Open(const char* filename = "..\\Data\\SaveLogger.txt");
	bool shutdownLog();


	int GetNumObjs();
	string GetName(int);
	string GetSceneName(int objId);
	void AddObj(string, string ObjName = " ");
	void SetComponent(int ObjNum, int componentNum, ImgnComponent* component);
	void AddComponent(string ObjName, string ComponentName, ImgnComponent* Component);
	void AddComponent(int ObjNum, string ComponentName, ImgnComponent* Component);
	//Can be used to Add Component data for the first time or to update the already existing data.
	void AddComponentData(int ObjNum, string ComponentName, Imgn::DisplayData* DisplayData);
	string GetComponentName(int objNum, int componentNum);

	glm::vec3 GetSpatialData(int curEntity, int CurDataNum);
	string GetMeshData(int curEntity, int CurDataNum);
	glm::vec3 GetVec3FromString(string vec);
private:
	void LoadEntityData(string &word);
	void LoadComponents(string &word);
	//Get Components Data if it exist.
	void LoadComponentData(int currentComponent);
	void DeleteData();
	void GenerateUniqueComponents();
	bool WriteToSaveFile();
	void WriteComponents(ofstream* out, int i);
	void WriteToEntityManager();
	void WriteComponentData(std::ofstream* meOutput);

private:
	static SaveLogger* saveLogger;
	string currentFilename;
	bool autoSave;

	string entities[Imgn::MAX_ENTITIES * Imgn::MAXENTITYDATA][2];
	string componentNames[Imgn::MAX_ENTITIES][Imgn::MAX_COMPONENTS_PERENTITY + 1];
	ImgnComponent* components[Imgn::MAX_ENTITIES][Imgn::MAX_COMPONENTS_PERENTITY + 1];
	string componentsData[Imgn::MAX_ENTITIES][Imgn::MAX_COMPONENTS_PERENTITY + 1][Imgn::MAX_VARIABLES];
	std::list<string> uniqueComponentNames;

	int curNumEntities;
	int currentEntityDataType;
	int entityData;
	int numUniqueComponents;

	std::stringstream buffer;
};