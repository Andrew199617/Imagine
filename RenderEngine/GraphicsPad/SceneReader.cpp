#include "SceneReader.h"
#include <iostream>
#include <fstream>
#include <assert.h>
#include "Scene.h"
#include "VertexFormats.h"
#include <fbxsdk.h>

SceneReader::SceneReader()
{
}

SceneReader::~SceneReader()
{
}

AnimationScene* SceneReader::ReadAnimationSceneFile(string filename)
{
	std::ifstream inputStream(filename, std::ios::binary | std::ios::in);
	if (!inputStream.good())
	{
		printf("ERROR : Unable to open scene file %s.\n", filename.c_str());
		return 0;
	}

	int dataLen;
	inputStream.read(reinterpret_cast<char*> (&dataLen), sizeof(dataLen));
	printf("Reading %d bytes.\n", dataLen);

	char* data = new char[dataLen];
	assert(data);
	std::fill(data, data + dataLen - 1, 0);

	inputStream.read(data, dataLen);
	inputStream.close();

	AnimationScene* scene = reinterpret_cast<AnimationScene*> (data);
	char* p = data;
	p += sizeof(AnimationScene);
	//scene->keys = reinterpret_cast<FbxTime*>(p);
	//p += scene->numKeys * sizeof(FbxTime);
	scene->animationData = p;
	

	//DisplayScene(scene);
	return scene;
}

Scene* SceneReader::ReadSceneFile(string filename)
{
	std::ifstream inputStream(filename, std::ios::binary | std::ios::in);
	if (!inputStream.good())
	{
		printf("ERROR : Unable to open scene file %s.\n", filename.c_str());
		return 0;
	}

	int dataLen;
	inputStream.read(reinterpret_cast<char*> (&dataLen), sizeof(dataLen));
	printf("Reading %d bytes.\n", dataLen);

	char* data = new char[dataLen];
	assert(data);
	std::fill(data, data + dataLen - 1, 0);

	inputStream.read(data, dataLen);
	inputStream.close();

	Scene* scene = reinterpret_cast<Scene*> (data);
	char* p = data;
	p += sizeof(Scene);
	scene->vertices = p;
	p += scene->numVertices * scene->sizeVertex;
	scene->indices = reinterpret_cast<GLuint*> (p);
	

	//DisplayScene(scene);
	return scene;
}

void SceneReader::DisplayVec3(vec3* vec)
{
	printf("<%f, %f, %f>\n", vec->x, vec->y, vec->z);
}

//void SceneReader::DisplayScene(Scene* scene)
//{
//	printf("NumVerts : %d\n", scene->numVertices);
//	printf("NumIndices : %d\n", scene->numIndices);
//	printf("sizeVerts : %d\n", scene->sizeVertex);
//	printf("sizeIndices : %d\n", scene->sizeIndex);
//	for (int j = 0; j < scene->numVertices; ++j)
//	{
//		printf("Position[%d] = ", j); DisplayVec3(&scene->vertices[j].position);
//	}
//	for (int j = 0; j < scene->numVertices; ++j)
//	{
//		printf("Color[%d] = ", j); DisplayVec3(&scene->vertices[j].color);
//	}
//	for (int j = 0; j < scene->numVertices; ++j)
//	{
//		printf("Normal[%d] = ", j); DisplayVec3(&scene->vertices[j].normal);
//	}
//	for (int j = 0; j < scene->numIndices; ++j)
//	{
//		GLuint index = scene->indices[j];
//		std::cout << index << "\n";
//	}
//
//	glm::vec3* p = reinterpret_cast<glm::vec3*> (scene->vertices);
//	for (int j = 0; j < 3 * scene->numVertices; ++j)
//	{
//		printf("Vec[%d] = ", j); DisplayVec3(&p[j]);
//	}
//
//}
