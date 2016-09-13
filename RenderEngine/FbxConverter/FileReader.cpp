#include "FileReader.h"
#include "glm.hpp"
#include <algorithm>

FileReader::FileReader(string fileName)
{
	GetName(fileName);
	ReadTextFile(fileName);
	GetVerticies();
	GetIndcies();
	GetTextureUVs();
	string wordtest;
	buffer >> wordtest;
}

FileReader::~FileReader()
{
	delete[] fbxData.verts;
	delete[] fbxDataUnordered.verts;
}

void FileReader::GetName(string fileName)
{
	string name = "";
	for (int i = fileName.length(); i > 0; i--)
	{
		if (fileName[i] == '.')
		{
			for (int j = i - 1; j > 0; j--)
			{
				if (fileName[j] == '\\')
				{
					break;
				}
				else
				{
					name += fileName[j];
				}
			}
			break;
		}
	}
	reverse(name.begin(), name.end());
	fbxData.name = name;
}

void FileReader::GetVerticies()
{
	string verts = "";
	string numVerts = "";
	int numVertsI;
	while (buffer.good())
	{
		buffer >> verts;
		if (verts == "Vertices:")
		{
			buffer >> numVerts;
			buffer >> verts;
			buffer >> verts;
			buffer >> verts;
			break;
		}
	}
	numVerts.erase(0,1);
	numVertsI = stoi(numVerts);
	fbxDataUnordered.verts = new vec3[numVertsI / 3];
	string floatX;
	string floatY;
	string floatZ;
	int curFloat = 0;
	int curVert = 0;
	vec3 vec;
	for (uint i = 0; i < verts.length(); i++)
	{
		if (verts[i] != ',')
		{
			switch (curFloat)
			{
			case 0:
				floatX += verts[i];
				break;
			case 1:
				floatY += verts[i];
				break;
			case 2:
				floatZ += verts[i];
				break;
			}
		}
		else
		{
			curFloat++;
			if (curFloat == 3)
			{
				vec = vec3(stof(floatX), stof(floatY), stof(floatZ));
				fbxDataUnordered.verts[curVert] = vec;
				curVert++;
				floatX = "";
				floatY = "";
				floatZ = "";
				curFloat = 0;
			}
			
		}
	}
	vec = vec3(stof(floatX), stof(floatY), stof(floatZ));
	fbxDataUnordered.verts[curVert] = vec;
}

void FileReader::GetIndcies()
{
	string indcies = "";
	string numindcies = "";
	int numindciesI;
	while (buffer.good())
	{
		buffer >> indcies;
		if (indcies == "PolygonVertexIndex:")
		{
			buffer >> numindcies;
			buffer >> indcies;
			buffer >> indcies;
			buffer >> indcies;
			break;
		}
	}
	numindcies.erase(0, 1);
	numindciesI = stoi(numindcies);
	//fbxData.positionIndicies = new GLuint[numindciesI];
	fbxData.verts = new vec3[numindciesI];
	string indcie = "";
	int curIndcie = 0;
	for (uint i = 0; i < indcies.length(); i++)
	{
		if (indcies[i] != ',')
		{
			indcie += indcies[i];
		}
		else
		{
			int indcieCheck = stoi(indcie);
			if (indcieCheck < 0)
			{
				indcieCheck -= indcieCheck * 2;
				indcieCheck--;
			}
			fbxData.verts[curIndcie] = fbxDataUnordered.verts[indcieCheck];
			curIndcie++;
			indcie = "";
		}
	}
	int indcieCheck = stoi(indcie);
	if (indcieCheck < 0)
	{
		indcieCheck -= indcieCheck * 2;
		indcieCheck--;
	}
	fbxData.verts[curIndcie] = fbxDataUnordered.verts[indcieCheck];
}

void FileReader::GetTextureUVs()
{
	string UVs = "";
	string numUVs = "";
	int numUVsI;
	while (buffer.good())
	{
		buffer >> UVs;
		if (UVs == "UV:")
		{
			buffer >> numUVs;
			buffer >> UVs;
			buffer >> UVs;
			buffer >> UVs;
			break;
		}
	}
	numUVs.erase(0, 1);
	numUVsI = stoi(numUVs);
	//fbxDataUnordered.texture = new vec2[numUVsI / 2];
	string floatX;
	string floatY;
	int curFloat = 0;
	int curVert = 0;
	vec2 vec;
	for (uint i = 0; i < UVs.length(); i++)
	{
		if (UVs[i] != ',')
		{
			switch (curFloat)
			{
			case 0:
				floatX += UVs[i];
				break;
			case 1:
				floatY += UVs[i];
				break;
			}
		}
		else
		{
			curFloat++;
			if (curFloat == 2)
			{
				vec = vec2(stof(floatX), stof(floatY));
				fbxDataUnordered.texture[curVert] = vec;
				curVert++;
				floatX = "";
				floatY = "";
				curFloat = 0;
			}

		}
	}
	vec = vec2(stof(floatX), stof(floatY));
	fbxDataUnordered.texture[curVert] = vec;
	OrderTextureUVs();
}

void FileReader::OrderTextureUVs()
{
	string indcies = "";
	string numindcies = "";
	int numindciesI;
	while (buffer.good())
	{
		buffer >> indcies;
		if (indcies == "UVIndex:")
		{
			buffer >> numindcies;
			buffer >> indcies;
			buffer >> indcies;
			buffer >> indcies;
			break;
		}
	}
	numindcies.erase(0, 1);
	numindciesI = stoi(numindcies);
	//fbxData.texture = new vec3[numindciesI];
	string indcie = "";
	int curIndcie = 0;
	for (uint i = 0; i < indcies.length(); i++)
	{
		if (indcies[i] != ',')
		{
			indcie += indcies[i];
		}
		else
		{
			fbxData.texture[curIndcie] = fbxDataUnordered.texture[stoi(indcie)];
			curIndcie++;
			indcie = "";
		}
	}
	fbxData.texture[curIndcie] = fbxDataUnordered.texture[stoi(indcie)];
}

void FileReader::ReadTextFile(string filename)
{
	ifstream meInput(filename);

	if (!meInput.good())
	{
		cout << "file failed to load..." << filename;
		cin.get();
	}
	buffer << meInput.rdbuf();
}


