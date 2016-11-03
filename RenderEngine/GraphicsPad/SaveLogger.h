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
		Position,
		Rotation,
		Scale,
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
	void AddComponentData(int ObjNum, string ComponentName, Imgn::DisplayData* DisplayData);
	string GetComponentName(int objNum, int componentNum);
public:
	glm::vec3 GetPosition(string);
	glm::quat GetRotate(string);
	glm::vec3 GetScale(string);
	void SetPosition(int, glm::vec3);
	void SetRotate(int, glm::vec3);
	void SetScale(int, glm::vec3);

private:
	void LoadEntityData(string &word, string &s);
	void LoadComponents(string &word);
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

	string entities[Imgn::MAX_ENTITIES * Imgn::MAXENTITYDATA][5];
	string componentNames[Imgn::MAX_ENTITIES][Imgn::MAX_COMPONENTS + 1];
	ImgnComponent* components[Imgn::MAX_ENTITIES][Imgn::MAX_COMPONENTS + 1];
	string componentsData[Imgn::MAX_ENTITIES][Imgn::MAX_COMPONENTS + 1][Imgn::MAX_VARIABLES];
	std::list<string> uniqueComponentNames;

	int curNumEntities;
	int currentEntityDataType;
	int entityData;
	int numUniqueComponents;

	std::stringstream buffer;
};