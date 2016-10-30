#include "BinaryOutput.h"

enum VertexFormats
{
	HasPosition = 1,
	HasColor = 2,
	HasTexture = 4,
	HasNormal = 8,
	PositionOnly = HasPosition,
	PositionColor = HasPosition | HasColor,
	PositionTexture = HasPosition | HasTexture,
	PositionNormal = HasPosition | HasNormal,
	PositionColorNormal = HasPosition | HasColor | HasNormal,
	PositionTextureNormal = HasPosition | HasTexture | HasNormal,
	PositionColorTexture = HasPosition | HasColor | HasTexture,
	PositionColorTextureNormal = HasPosition | HasColor | HasTexture | HasNormal,
};

BinaryOutput::BinaryOutput()
{
}

void BinaryOutput::WriteCustomBinaryFile(FbxData data)
{
	fbxData = data;
	GLuint* indcies = new GLuint[data.numIndcies];
	for (int i = 0; i < data.numIndcies; i++)
	{
		indcies[i] = i;
	}
	WriteCustomBinaryFile(indcies);
	delete[] indcies;
}

void BinaryOutput::WriteCustomBinaryFile(GLuint* indices)
{
	string filename = "..\\..\\StaticData\\Scenes\\" + fbxData.name + ".imgnasset";

	int totalBytes = 0;
	std::ofstream outputStream(filename, std::ios::binary | std::ios::out);

	outputStream.seekp(0);
	WriteInt(outputStream, totalBytes);

	int vertexSize = 0;
	switch (fbxData.SceneOutputFormat)
	{
	case PositionOnly: vertexSize = sizeof(glm::vec3);
		break;
	case PositionColor: vertexSize = 2 * sizeof(glm::vec3);
		break;
	case PositionColorNormal: vertexSize = 3 * sizeof(glm::vec3);
		break;
	case PositionColorTexture: vertexSize = (2 * sizeof(glm::vec3)) + sizeof(glm::vec2);
		break;
	case PositionTexture: vertexSize = sizeof(glm::vec3) + sizeof(glm::vec2);
		break;
	case PositionNormal: vertexSize = 2 * sizeof(glm::vec3);
		break;
	case PositionTextureNormal: vertexSize = (2 * sizeof(glm::vec3)) + sizeof(glm::vec2);
		break;
	case PositionColorTextureNormal: vertexSize = (3 * sizeof(glm::vec3)) + sizeof(glm::vec2);
		break;

	}


	totalBytes += WriteHeader(outputStream, fbxData.numVerts, fbxData.numIndcies, vertexSize, sizeof(GLuint), fbxData.SceneOutputFormat);
	totalBytes += WriteVec3(outputStream, fbxData.centerOfMass);
	totalBytes += WriteVertexData(outputStream, fbxData.numVerts, fbxData.verts, fbxData.colors, fbxData.normals, fbxData.texture, fbxData.SceneOutputFormat);
	totalBytes += WriteIndices(outputStream, fbxData.numIndcies, indices);

	outputStream.seekp(0);
	WriteInt(outputStream, totalBytes);
	outputStream.close();
	printf("Scene : wrote %d bytes.\n", totalBytes);
	if (!fbxData.hasAnimation) { return; }

	totalBytes = 0;
	std::ofstream out("..\\..\\StaticData\\Scenes\\" + fbxData.name + ".animation", std::ios::binary | std::ios::out);
	out.seekp(0);
	WriteInt(out, totalBytes);

	totalBytes += WriteInt(out, fbxData.animationLength);
	//totalBytes += WriteInt(out, numKeys);
	//totalBytes += WriteBool(out, hasAnimation);
	totalBytes += WritePointer(out, 1);
	//totalBytes += WriteKeys(out, numKeys, keys);
	totalBytes += WriteAnimationData(out, fbxData.animationLength, fbxData.animationData);

	out.seekp(0);
	WriteInt(out, totalBytes);
	out.close();

	printf("AnimationScene : wrote %d bytes.\n", totalBytes);
}

int BinaryOutput::WriteHeader(std::ofstream& out, int numVerts, int numIndices, int sizeVerts, int sizeIndices, int SceneOutputFormat)
{
	int totalBytes = 0;
	totalBytes += WriteInt(out, numVerts);
	totalBytes += WriteInt(out, numIndices);
	totalBytes += WriteInt(out, sizeVerts);
	totalBytes += WriteInt(out, sizeIndices);
	totalBytes += WriteInt(out, SceneOutputFormat);
	totalBytes += WriteInt(out, (int)fbxData.hasAnimation);
	totalBytes += WritePointer(out, 3);
	return totalBytes;
}

int BinaryOutput::WriteInt(std::ofstream& out, int value)
{
	int size = sizeof(int);
	out.write(reinterpret_cast<char*> (&value), size);
	return size;
}

int BinaryOutput::WriteBool(std::ofstream & out, bool value)
{
	int size = sizeof(bool);
	out.write(reinterpret_cast<char*> (&value), size);
	return size;
}

int BinaryOutput::WritePointer(std::ofstream& out, int count)
{
	int size = sizeof(void*);
	void* pointer = 0;
	for (int j = 0; j < count; ++j)
	{
		out.write(reinterpret_cast<char*> (&pointer), size);
	}
	return count * size;
}

int BinaryOutput::WriteVertexData(std::ofstream& out, int numVerts, glm::vec3* verts, glm::vec3* colors,
	glm::vec3* normals, glm::vec2* texture, int SceneOutputFormat)
{
	int totalBytes = 0;
	for (int j = 0; j < numVerts; ++j)
	{
		totalBytes += WriteVec3(out, verts[j]);
		if (SceneOutputFormat & HasColor)
			totalBytes += WriteVec3(out, colors[j]);
		if (SceneOutputFormat & HasTexture)
			totalBytes += WriteVec2(out, texture[j]);
		if (SceneOutputFormat & HasNormal)
			totalBytes += WriteVec3(out, normals[j]);
	}
	return totalBytes;
}

int BinaryOutput::WriteKeys(std::ofstream & out, int numKeys, FbxTime* data)
{
	int totalBytes = 0;
	for (int i = 0; i < numKeys; i++)
	{
		totalBytes += WriteFbxTime(out, data[i]);
	}
	return totalBytes;
}

int BinaryOutput::WriteAnimationData(std::ofstream& out,int numKeys,glm::mat4* data)
{
	int totalBytes = 0;
	for (int i = 0; i < numKeys; i++)
	{
		totalBytes += WriteMat4(out,data[i]);
	}
	return totalBytes;
}

int BinaryOutput::WriteFbxTime(std::ofstream & out, FbxTime time)
{
	int size = sizeof(time);
	out.write(reinterpret_cast<char*> (&time), size);
	return size;
}

int BinaryOutput::WriteMat4(std::ofstream & out, glm::mat4 mat)
{
	int size = sizeof(mat);
	out.write(reinterpret_cast<char*> (&mat), size);
	return size;
}

int BinaryOutput::WriteVec3(std::ofstream& out, glm::vec3 vec)
{
	int size = sizeof(vec);
	out.write(reinterpret_cast<char*> (&vec), size);
	return size;
}

int BinaryOutput::WriteVec2(std::ofstream& out, glm::vec2 vec)
{
	int size = sizeof(vec);
	out.write(reinterpret_cast<char*> (&vec), size);
	return size;
}

int BinaryOutput::WriteGLuint(std::ofstream& out, GLuint value)
{
	int size = sizeof(GLuint);
	out.write(reinterpret_cast<char*> (&value), size);
	return size;
}

int BinaryOutput::WriteIndices(std::ofstream& out, int numIndices, GLuint* indices)
{
	int totalBytes = 0;
	for (int j = 0; j < numIndices; ++j)
	{
		totalBytes += WriteGLuint(out, indices[j]);
	}
	return totalBytes;
}