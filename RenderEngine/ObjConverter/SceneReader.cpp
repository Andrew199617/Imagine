#include "SceneReader.h"
#include <iostream>
#include <fstream>
#include <assert.h>

using namespace std;

SceneReader::SceneReader()
{
}


SceneReader::~SceneReader()
{
}

Scene* SceneReader::ReadSceneFile(const char* filename)
{
	std::ifstream inputStream(filename, std::ios::binary | std::ios::in);
	if (!inputStream.good())
	{
		printf("ERROR : Unable to open scene file %s.\n", filename);
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
	scene->vertices = reinterpret_cast<Vertex*> (p);
	p += scene->numVertices * scene->sizeVertex;
	scene->indices = reinterpret_cast<GLushort*> (p);

	return scene;
}