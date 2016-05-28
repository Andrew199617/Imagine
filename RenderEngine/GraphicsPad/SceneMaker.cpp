#include "SceneMaker.h"
#include <GL\glew.h>
#include "VertexFormats.h"
#include <string>
#include "OpenFileDialog.h"
#include <stdio.h>
#include "BinaryOutput.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ConfigReader.h"
#include "GameLogger.h"
#include <direct.h>
#include "Scene.h"
#pragma warning(push)
#pragma warning(disable : 4201)
#include <glm.hpp>
#pragma warning(pop)

using namespace glm;
using namespace std;

int SIZEOFINDICIES;


vec3* vertsNotOrdered;
vec3* verts;
vec3* colorsNotOrdered;
vec3* colors;
vec2* textureNotOrdered;
vec2* texture;
vec3* normalsNotOrdered;
vec3* normals;
GLuint* positionIndicies;
GLuint* textureIndicies;
GLuint* normalIndicies;
GLuint* indices;
stringstream buffer;
string word;
bool collectNormals;
int j;
int SceneOutputFormat;
string outputColor;
string outputTexture;
string outputNormal;
BinaryOutput writer;
ConfigReader con;

float randomFloat()
{
	return (float)rand() / RAND_MAX;
}

string readTextFile(string filename)
{
	stringstream m_buffer;
	ifstream meInput(filename);

	if (!meInput.good())
	{
		cout << "file failed to load..." << filename;
		cin.get();
	}
	m_buffer << meInput.rdbuf();
	return m_buffer.str();

}

void parseIndicie(int indiciesIndex)
{
	buffer >> word;
	int numOfBackSlash = 0;
	stringstream position;
	stringstream m_texture;
	stringstream m_normals;
	for (uint i = 0; i < word.length(); i++)
	{
		if (word[i] == '/')
		{
			numOfBackSlash++;
		}
		else if (numOfBackSlash == 0)
		{
			position << word[i];
		}
		else if (numOfBackSlash == 1)
		{
			m_texture << word[i];
		}
		else if (numOfBackSlash == 2)
		{
			m_normals << word[i];
		}
	}

	position >> positionIndicies[indiciesIndex];
	m_texture >> textureIndicies[indiciesIndex];
	m_normals >> normalIndicies[indiciesIndex];
	positionIndicies[indiciesIndex] -= 1;
	textureIndicies[indiciesIndex] -= 1;
	normalIndicies[indiciesIndex] -= 1;

}

void orderIndicies(int lengthOfIndicies)
{
	for (int i = 0; i < lengthOfIndicies; i++)
	{
		indices[i] = positionIndicies[i];
	}
}

int makeVerts(int positionIndex)
{
	float value1;
	float value2;
	float value3;
	buffer >> value1;
	buffer >> value2;
	buffer >> value3;
	//cout << value1 << " " << value2 << " " << value3 << endl;
	vertsNotOrdered[positionIndex] = vec3(value1, value2, value3);
	if ((SceneOutputFormat & HasColor) && outputColor == "random")
	{
		colorsNotOrdered[positionIndex] = vec3(randomFloat(), randomFloat(), randomFloat());
	}
	else if (SceneOutputFormat & HasColor)
	{
		colorsNotOrdered[positionIndex] = ConfigReader::findVec3ForKey("OutputColor");
	}
	positionIndex++;
	return positionIndex;
}

int makeNormals(int normalsIndex)
{
	float value1;
	float value2;
	float value3;
	buffer >> value1;
	buffer >> value2;
	buffer >> value3;
	normalsNotOrdered[normalsIndex] = vec3(value1, value2, value3);
	normalsIndex++;

	return normalsIndex;
}

int makeNormalsDefault(int normalsIndex)
{
	if (outputNormal == "random")
	{
		normalsNotOrdered[normalsIndex] = vec3(randomFloat(), randomFloat(), randomFloat());
	}
	else
	{
		normalsNotOrdered[normalsIndex] = ConfigReader::findVec3ForKey("OutputNormal");
	}
	normalsIndex++;

	return normalsIndex;
}

int generatNormals(int normalsIndex)
{
	vec3 V = verts[(normalsIndex + 1)] - verts[normalsIndex];
	vec3 W = verts[(normalsIndex + 2)] - verts[(normalsIndex + 1)];
	normals[normalsIndex] = normalize(cross(V, W));
	normalsIndex++;
	normals[normalsIndex] = normalize(cross(V, W));
	normalsIndex++;
	normals[normalsIndex] = normalize(cross(V, W));
	normalsIndex++;

	return normalsIndex;
}

int makeIndicies(int indiciesIndex)
{

	parseIndicie(indiciesIndex);
	indiciesIndex++;
	parseIndicie(indiciesIndex);
	indiciesIndex++;
	parseIndicie(indiciesIndex);
	indiciesIndex++;

	return indiciesIndex;
}

int makeTextures(int textureIndex)
{
	float value1;
	float value2;
	buffer >> value1;
	buffer >> value2;
	textureNotOrdered[textureIndex] = vec2(value1, value2);
	textureIndex++;

	return textureIndex;
}

int makeTexturesDefaultUV(int textureIndex)
{
	if (outputTexture == "random")
	{
		textureNotOrdered[textureIndex] = vec2(randomFloat(), randomFloat());
	}
	else
	{
		textureNotOrdered[textureIndex] = ConfigReader::findVec2ForKey("OutputTexture");
	}
	textureIndex++;

	return textureIndex;
}

void orderVerts(int numIndicies)
{
	for (int i = 0; i < numIndicies; i++)
	{
		verts[i] = vertsNotOrdered[positionIndicies[i]];
		if (SceneOutputFormat & HasColor)
			colors[i] = colorsNotOrdered[positionIndicies[i]];
		if (SceneOutputFormat & HasTexture)
			texture[i] = textureNotOrdered[textureIndicies[i]];
		if (SceneOutputFormat & HasNormal)
			normals[i] = normalsNotOrdered[normalIndicies[i]];

		positionIndicies[i] = (GLuint)i;
	}
}


void Configure(ConfigReader* config, string objName)
{
	config;
	vertsNotOrdered = new vec3[SIZEOFINDICIES];
	verts = new vec3[SIZEOFINDICIES];
	colorsNotOrdered = new vec3[SIZEOFINDICIES];
	colors = new vec3[SIZEOFINDICIES];
	textureNotOrdered = new vec2[SIZEOFINDICIES];
	texture = new vec2[SIZEOFINDICIES];
	normalsNotOrdered = new vec3[SIZEOFINDICIES];
	normals = new vec3[SIZEOFINDICIES];
	positionIndicies = new GLuint[SIZEOFINDICIES];
	textureIndicies = new GLuint[SIZEOFINDICIES];
	normalIndicies = new GLuint[SIZEOFINDICIES];
	indices = new GLuint[SIZEOFINDICIES];
	string objText = readTextFile(objName);
	outputColor = "random";//config->findValueForKey("OutputColor");
	outputTexture = "random";//config->findValueForKey("OutputTexture");
	outputNormal = "generate";//config->findValueForKey("OutputNormal");
	int numIndicies = SIZEOFINDICIES;
	if (SceneOutputFormat & HasNormal)
	{
		collectNormals = true;
	}
	buffer = stringstream(objText);
	int positionIndex = 0;
	int textureIndex = 0;
	int normalsIndex = 0;
	int indiciesIndex = 0;
	GameLogger::log("setting up values for" + objName);
	while (buffer.good())
	{
		buffer >> word;
		if (word == "v")
		{
			positionIndex = makeVerts(positionIndex);
		}
		else if (word == "vt" && (SceneOutputFormat & HasTexture))
		{
			textureIndex = makeTextures(textureIndex);
		}
		else if (word == "vn" && (SceneOutputFormat & HasNormal) && collectNormals)
		{
			normalsIndex = makeNormals(normalsIndex);
		}
		else if (word == "f")
		{
			indiciesIndex = makeIndicies(indiciesIndex);
		}
	}
	if (textureIndex == 0 && (SceneOutputFormat & HasTexture))
	{
		for (int i = 0; i < numIndicies; i++)
		{
			textureIndex = makeTextures(textureIndex);
		}
		GameLogger::log("Used OutputTexture in configFile for Texture");
	}
	if (normalsIndex == 0 && (SceneOutputFormat & HasNormal) && outputNormal != "generate")
	{
		for (int i = 0; i < numIndicies; i++)
		{
			normalsIndex = makeNormals(normalsIndex);
		}
		GameLogger::log("Used OutputNormal in configFile for Normals");
	}
	orderVerts(numIndicies);
	if (normalsIndex == 0 && (SceneOutputFormat & HasNormal) && outputNormal == "generate")
	{
		for (int i = 0; i < numIndicies; i += 3)
		{
			normalsIndex = generatNormals(normalsIndex);
		}
		GameLogger::log("Used OutputNormal in configFile for Normals");
	}
	orderIndicies(numIndicies);
	cout << positionIndex << endl;
	cout << normalsIndex << endl;
	cout << indiciesIndex << endl;
}

int findOutNumberOfIndicies(string obj)
{
	string objText = readTextFile(obj);
	stringstream buffer2 = stringstream(objText);
	int i = 0;
	while (buffer2.good())
	{
		buffer2 >> word;

		if (word == "f")
		{
			i += 3;
		}
	}
	return i;
}

SceneMaker::SceneMaker()
{
}


SceneMaker::~SceneMaker()
{
}

void SceneMaker::makeScene(string filename, string objName,int sceneVertexFormat)
{
	SceneOutputFormat = sceneVertexFormat;
	ConfigReader::Initialize("..\\..\\StaticData\\config.txt");
	SIZEOFINDICIES = findOutNumberOfIndicies(filename);
	Configure(&con, filename);

	writer.WriteCustomBinaryFile("..\\..\\StaticData\\Scenes\\" + objName, SIZEOFINDICIES, SIZEOFINDICIES,
		verts, colors, normals, texture, indices, sceneVertexFormat);

}