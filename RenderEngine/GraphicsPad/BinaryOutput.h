#pragma once
#include <GL\glew.h>
#include <fstream>
#include <string>

#pragma warning(push)
#pragma warning(disable : 4201)
#include <glm.hpp>
#pragma warning(pop)

using namespace std;

class BinaryOutput
{
public:
	BinaryOutput();
	void WriteCustomBinaryFile(string filename, int numVerts, int numIndices, glm::vec3* vertices, glm::vec3* colors, glm::vec3* normals, glm::vec2* texture, GLuint* indices, int SceneOutputFormat);
	int WriteHeader(std::ofstream& out, int numVerts, int numIndices, int sizeVerts, int sizeIndices, int SceneOutputFormat);
	int WriteInt(std::ofstream& out, int value);
	int WritePointer(std::ofstream& out, int count);
	int WriteVertexData(std::ofstream& out, int numVerts, glm::vec3* verts, glm::vec3* colors,
		glm::vec3* normals, glm::vec2* texture, int SceneOutputFormat);
	int WriteVec3(std::ofstream& out, glm::vec3 vec);
	int WriteVec2(std::ofstream& out, glm::vec2 vec);
	int WriteGLuint(std::ofstream& out, GLuint value);
	int WriteIndices(std::ofstream& out, int numIndices, GLuint* indices);
};

