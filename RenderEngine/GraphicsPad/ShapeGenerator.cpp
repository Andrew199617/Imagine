#pragma warning(push)
#pragma warning (disable:4201)
#pragma warning(disable:4244)
#pragma warning(disable:4018)
#include "ShapeGenerator.h"
#include <glm.hpp>
#include "Vertex.h"
#include "VertexFormats.h"
#include "Scene.h"
#include <iostream>
#include "SceneReader.h"
#include "GameLogger.h"
#include "SaveLogger.h"
#include "RenderEngine\RenderEngine.h"
#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a)
int byteOffset = 0;
#define MAXGEO 300
Geometry geoArray[MAXGEO];
int numGeos = 0;

float ranFloat()
{
	return rand() / (float)RAND_MAX;
}

Geometry * ShapeGenerator::makeLine(glm::vec3 point1, glm::vec3 point2)
{
	vec3 color = glm::vec3(0.0f,0.0f,0.5f);
	float scale = .125f;
	vPositionColor verts[] = 
	{
		glm::vec3(point1.x + scale, point1.y, point1.z + scale),
		color, 
		glm::vec3(point1.x - scale, point1.y, point1.z + scale),
		color,
		glm::vec3(point1.x - scale, point1.y, point1.z - scale),
		color,
		glm::vec3(point1.x + scale, point1.y, point1.z - scale),
		color,

		glm::vec3(point2.x + scale, point2.y, point2.z + scale),
		color,
		glm::vec3(point2.x - scale, point2.y, point2.z + scale),
		color,
		glm::vec3(point2.x - scale, point2.y, point2.z - scale),
		color,
		glm::vec3(point2.x + scale, point2.y, point2.z - scale),
		color,
	};


	GLuint indicies[] = {
		0,1,3,1,2,3,
		0,7,4,0,3,7,
		1,4,5,1,0,4,
		2,7,6,2,3,7,
		1,6,5,1,2,6,
		4,5,7,5,6,7
	};

	geoArray[numGeos].texturePath = "0";
	geoArray[numGeos].objName = "Line";
	geoArray[numGeos].m_vertexCount = NUM_ARRAY_ELEMENTS(verts);
	geoArray[numGeos].vertices = &verts[0];
	geoArray[numGeos].m_vertexStride = sizeof(vPositionColor);
	geoArray[numGeos].m_vertexByteOffset = byteOffset;
	byteOffset += geoArray[numGeos].m_vertexCount * geoArray[numGeos].m_vertexStride;

	geoArray[numGeos].m_indexCount = NUM_ARRAY_ELEMENTS(indicies);
	geoArray[numGeos].indices = &indicies[0];
	geoArray[numGeos].m_indexStride = sizeof(GLuint);
	geoArray[numGeos].m_indexByteOffset = byteOffset;
	byteOffset += geoArray[numGeos].m_indexCount * geoArray[numGeos].m_indexStride;
	geoArray[numGeos].VertexFormat = 3;

	RenderEngine::AddGeometry(geoArray[numGeos].vertices, geoArray[numGeos].m_vertexCount, geoArray[numGeos].m_vertexCount * geoArray[numGeos].m_vertexStride, geoArray[numGeos].indices,
		geoArray[numGeos].m_indexCount, geoArray[numGeos].m_indexCount * geoArray[numGeos].m_indexStride, geoArray[numGeos]);

	numGeos++;

	return &geoArray[numGeos - 1];
}

Geometry* ShapeGenerator::readScene(string ObjName)
{
	Geometry ret;
	SceneReader scenereader;

	string key = ObjName + "Scene";
	Scene* scene = scenereader.ReadSceneFile(ConfigReader::findValueForKey(key));

	if (!scene)
	{
		GameLogger::log("unable to open scene for :" + key);
		GameLogger::shutdownLog();
		exit(1);
	}

	if(scene->SceneOutputFormat & HasTexture)
	{

		geoArray[numGeos].texturePath = ConfigReader::findValueForKey(ObjName + "Texture");
	}
	else
	{
		geoArray[numGeos].texturePath = "0";
	}
	geoArray[numGeos].objName = ObjName;
	geoArray[numGeos].m_vertexCount = scene->numVertices;
	geoArray[numGeos].vertices = scene->vertices;
	switch (scene->SceneOutputFormat)
	{
	case PositionOnly: geoArray[numGeos].Verts = reinterpret_cast<vPosition*> (scene->vertices);
		break;
	case PositionColor: geoArray[numGeos].Verts = reinterpret_cast<vPositionColor*> (scene->vertices);
		break;
	case PositionColorNormal: geoArray[numGeos].Verts = reinterpret_cast<vPositionColorNormal*> (scene->vertices);
		break;
	case PositionColorTexture: geoArray[numGeos].Verts = reinterpret_cast<vPositionColorTexture*> (scene->vertices);
		break;
	case PositionTexture: geoArray[numGeos].Verts = reinterpret_cast<vPositionTexture*> (scene->vertices);
		break;
	case PositionNormal: geoArray[numGeos].Verts = reinterpret_cast<vPositionNormal*> (scene->vertices);
		break;
	case PositionTextureNormal: geoArray[numGeos].Verts = reinterpret_cast<vPositionTextureNormal*> (scene->vertices);
		break;
	case PositionColorTextureNormal: geoArray[numGeos].Verts = reinterpret_cast<vPositionColorTextureNormal*> (scene->vertices);
		break;
	}
	geoArray[numGeos].m_vertexStride = scene->sizeVertex;
	geoArray[numGeos].m_vertexByteOffset = byteOffset;
	byteOffset += geoArray[numGeos].m_vertexCount * geoArray[numGeos].m_vertexStride;
	
	geoArray[numGeos].m_indexCount = scene->numIndices;
	geoArray[numGeos].indices = scene->indices;
	geoArray[numGeos].indicesShort = reinterpret_cast<GLuint*>(scene->indices);
	geoArray[numGeos].m_indexStride = scene->sizeIndex;
	geoArray[numGeos].m_indexByteOffset = byteOffset;
	byteOffset += geoArray[numGeos].m_indexCount * geoArray[numGeos].m_indexStride;
	geoArray[numGeos].VertexFormat = scene->SceneOutputFormat;

	RenderEngine::AddGeometry(geoArray[numGeos].vertices, geoArray[numGeos].m_vertexCount, geoArray[numGeos].m_vertexCount * geoArray[numGeos].m_vertexStride, geoArray[numGeos].indices,
		geoArray[numGeos].m_indexCount, geoArray[numGeos].m_indexCount * geoArray[numGeos].m_indexStride, geoArray[numGeos]);

	numGeos++;

	return &geoArray[numGeos - 1];
}

Geometry* ShapeGenerator::readScene(string File,string ObjName)
{
	Geometry ret;
	/*if (!configRead.Initialize())
	{
	GameLogger::log("Config file did not intialize");
	}*/
	SceneReader scenereader;

	
	Scene* scene = scenereader.ReadSceneFile(File);

	//geoArray[numGeos].texturePath = SaveLogger::getTextureWithKey(ObjName);
	geoArray[numGeos].objName = " ";
	geoArray[numGeos].m_vertexCount = scene->numVertices;
	geoArray[numGeos].vertices = scene->vertices;
	geoArray[numGeos].Verts = (vPositionTextureNormal*)scene->vertices;
	geoArray[numGeos].m_vertexStride = scene->sizeVertex;
	geoArray[numGeos].m_vertexByteOffset = byteOffset;
	byteOffset += geoArray[numGeos].m_vertexCount * geoArray[numGeos].m_vertexStride;

	geoArray[numGeos].m_indexCount = scene->numIndices;
	geoArray[numGeos].indices = scene->indices;
	geoArray[numGeos].m_indexStride = scene->sizeIndex;
	geoArray[numGeos].m_indexByteOffset = byteOffset;
	byteOffset += geoArray[numGeos].m_indexCount * geoArray[numGeos].m_indexStride;
	geoArray[numGeos].VertexFormat = scene->SceneOutputFormat;

	RenderEngine::AddGeometry(geoArray[numGeos].vertices, geoArray[numGeos].m_vertexCount, geoArray[numGeos].m_vertexCount * geoArray[numGeos].m_vertexStride, geoArray[numGeos].indices,
		geoArray[numGeos].m_indexCount, geoArray[numGeos].m_indexCount * geoArray[numGeos].m_indexStride, geoArray[numGeos]);

	numGeos++;

	return &geoArray[numGeos - 1];
}


#pragma warning(pop)
