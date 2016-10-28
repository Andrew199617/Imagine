#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include "glm.hpp"
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
	void LoadComponent(int ObjNum, int componentNum, ImgnComponent* component);
	void AddNewComponent(string ObjName, string ComponentName, ImgnComponent* Component);
	void AddNewComponent(int ObjNum, string ComponentName, ImgnComponent* Component);
	void AddComponentData(int ObjNum, string ComponentName, Imgn::DisplayData* DisplayData);
	string GetComponentName(int objNum, int componentNum);
public:
	glm::vec3 GetPosition(string);
	glm::vec3 GetRotate(string);
	glm::vec3 GetScale(string);
	void SetPosition(int, glm::vec3);
	void SetRotate(int, glm::vec3);
	void SetScale(int, glm::vec3);

private:
	void AddEntityData(string &word, string &s);
	void AddComponentsForEntity(string &word);
	void DeleteData();
	void GenerateUniqueComponents();
	void WriteComponentData(std::ofstream* meOutput);

private:
	static SaveLogger* saveLogger;
	bool autoSave;

	string entities[Imgn::MAX_ENTITIES * Imgn::MAXENTITYDATA][5];
	string componentNames[Imgn::MAX_ENTITIES][Imgn::MAX_COMPONENTS + 1];
	ImgnComponent* components[Imgn::MAX_ENTITIES][Imgn::MAX_COMPONENTS + 1];
	string componentsData[Imgn::MAX_ENTITIES][Imgn::MAX_COMPONENTS + 1][Imgn::MAX_VARIABLES];
	string currentFilename;
	int curNumEntities;

	int numUniqueComponents;
	std::list<string> uniqueComponents;

	std::stringstream buffer;
	bool inQuotes = false;
	int currentEntityDataType;
	int entityData;
};