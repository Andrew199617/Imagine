#include "FbxFileReader.h"
#include "FbxFileReader.h"
#include "FbxFileReader.h"
#include "glm.hpp"
#include <algorithm>
#include <fbxsdk.h>

using glm::vec3;

FbxFileReader::FbxFileReader()
{
	deleteMemory = false;
}

FbxFileReader::FbxFileReader(string fileName)
{
	Initialize(fileName);
	
}

FbxFileReader::~FbxFileReader()
{
	if (deleteMemory)
	{
		delete[] fbxData.verts;
		delete[] fbxData.texture;
		//delete[] fbxDataUnordered.verts;
		delete[] fbxDataUnordered.texture;
	}
}

void FbxFileReader::Initialize(string fileName)
{
	GetName(fileName);
	ReadTextFile(fileName);

	FbxManager* fbxManager = FbxManager::Create();
	FbxIOSettings *ios = FbxIOSettings::Create(fbxManager, IOSROOT);
	fbxManager->SetIOSettings(ios);

	// Create an importer using the SDK manager.
	FbxImporter* lImporter = FbxImporter::Create(fbxManager, "");
	FbxScene* lScene = FbxScene::Create(fbxManager, fbxData.name.c_str());

	lImporter->Initialize(fileName.c_str(),-1,fbxManager->GetIOSettings());


	// Import the contents of the file into the scene.
	lImporter->Import(lScene);
	lImporter->Destroy();

	FbxNode* lRootNode = lScene->GetRootNode();
	GetIndcies();

	int curVert = 0;
	if (lRootNode)
	{
		for (int i = 0; i < lRootNode->GetChildCount(); i++)
		{
			FbxNode* pFbxChildNode = lRootNode->GetChild(i);

			if (pFbxChildNode->GetNodeAttribute() == NULL)
				continue;

			FbxNodeAttribute::EType AttributeType = pFbxChildNode->GetNodeAttribute()->GetAttributeType();

			if (AttributeType != FbxNodeAttribute::eMesh)
				continue;

			FbxMesh* pMesh = (FbxMesh*)pFbxChildNode->GetNodeAttribute();

			FbxVector4* pVertices = pMesh->GetControlPoints();

			for (int j = 0; j < pMesh->GetPolygonCount(); j++)
			{
				int iNumVertices = pMesh->GetPolygonSize(j);
				assert(iNumVertices == 3);
				FbxLayerElementArrayTemplate<FbxVector2>* uvVertices = 0;
				pMesh->GetTextureUV(&uvVertices, FbxLayerElement::eTextureDiffuse);

				for (int k = 0; k < iNumVertices; k++)
				{
					int iControlPointIndex = pMesh->GetPolygonVertex(j, k);

					vec3 vec = glm::vec3((float)pVertices[iControlPointIndex].mData[0],
						(float)pVertices[iControlPointIndex].mData[1],
						(float)pVertices[iControlPointIndex].mData[2]);
					fbxData.verts[curVert] = vec;

					FbxVector2 uv = uvVertices->GetAt(pMesh->GetTextureUVIndex(j, k));
					fbxData.texture[curVert].x = uv[0];
					fbxData.texture[curVert].y = uv[1];
					
					curVert++;

				}
				
			}

		}
	}

	//GetVerticies();
	GetTextureUVs();
	fbxData.SceneOutputFormat = 5;
	binaryOutput.WriteCustomBinaryFile(fbxData);
	deleteMemory = true;
}

string FbxFileReader::GetName(string fileName)
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
	return name;
}

void FbxFileReader::GetVerticies()
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
	//fbxDataUnordered.verts = new glm::vec3[numVertsI / 3];
	string floatX;
	string floatY;
	string floatZ;
	int curFloat = 0;
	int curVert = 0;
	glm::vec3 vec;
	while (verts != "}")
	{

		for (glm::uint i = 0; i < verts.length(); i++)
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
					vec = glm::vec3(stof(floatX), stof(floatY), stof(floatZ));
					fbxDataUnordered.verts[curVert] = vec;
					curVert++;
					floatX = "";
					floatY = "";
					floatZ = "";
					curFloat = 0;
				}

			}
		}
		buffer >> verts;
	}
	vec = glm::vec3(stof(floatX), stof(floatY), stof(floatZ));
	fbxDataUnordered.verts[curVert] = vec;
}

void FbxFileReader::GetIndcies()
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
	fbxData.numVerts = numindciesI;
	fbxData.numIndcies = numindciesI;
	fbxData.verts = new vec3[numindciesI];
	/*string indcie = "";
	int curIndcie = 0;
	while (indcies != "}")
	{
		for (glm::uint i = 0; i < indcies.length(); i++)
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
		buffer >> indcies;
	}
	if (indcie != "")
	{
		int indcieCheck = stoi(indcie);
		if (indcieCheck < 0)
		{
			indcieCheck -= indcieCheck * 2;
			indcieCheck--;
		}
		fbxData.verts[curIndcie] = fbxDataUnordered.verts[indcieCheck];
	}*/
}

void FbxFileReader::GetTextureUVs()
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
	//fbxDataUnordered.texture = new glm::vec2[numUVsI / 2];
	string floatX;
	string floatY;
	int curFloat = 0;
	int curVert = 0;
	glm::vec2 vec;
	while (UVs != "}")
	{
		for (glm::uint i = 0; i < UVs.length(); i++)
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
					vec = glm::vec2(stof(floatX), stof(floatY));
					fbxDataUnordered.texture[curVert] = vec;
					curVert++;
					floatX = "";
					floatY = "";
					curFloat = 0;
				}

			}
		}
		buffer >> UVs;
	}
	vec = glm::vec2(stof(floatX), stof(floatY));
	fbxDataUnordered.texture[curVert] = vec;
	OrderTextureUVs();
}

void FbxFileReader::OrderTextureUVs()
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
	//fbxData.texture = new glm::vec2[numindciesI];
	string indcie = "";
	int curIndcie = 0;
	while (indcies != "}")
	{
		for (glm::uint i = 0; i < indcies.length(); i++)
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
		buffer >> indcies;
	}
	fbxData.texture[curIndcie] = fbxDataUnordered.texture[stoi(indcie)];
}

void FbxFileReader::ReadTextFile(string filename)
{
	ifstream meInput(filename);

	if (!meInput.good())
	{
		cout << "file failed to load..." << filename;
		cin.get();
	}
	buffer << meInput.rdbuf();
}


