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
	GLuint* indcies = new GLuint[data.numIndcies];
	for (int i = 0; i < data.numIndcies; i++)
	{
		indcies[i] = i;
	}
	WriteCustomBinaryFile("..\\..\\StaticData\\Scenes\\" + data.name + ".scene", data.numVerts, data.numIndcies, data.verts, data.colors, data.normals, data.texture, indcies, data.SceneOutputFormat);
	delete[] indcies;
}

void BinaryOutput::WriteCustomBinaryFile(string filename, int numVerts, int numIndices, glm::vec3* vertices, glm::vec3* colors, glm::vec3* normals, glm::vec2* texture, GLuint* indices, int SceneOutputFormat)
{
	int totalBytes = 0;
	std::ofstream outputStream(filename, std::ios::binary | std::ios::out);

	outputStream.seekp(0);
	WriteInt(outputStream, totalBytes);

	int VertexSize = 0;
	switch (SceneOutputFormat)
	{
	case PositionOnly: VertexSize = sizeof(glm::vec3);
		break;
	case PositionColor: VertexSize = 2 * sizeof(glm::vec3);
		break;
	case PositionColorNormal: VertexSize = 3 * sizeof(glm::vec3);
		break;
	case PositionColorTexture: VertexSize = (2 * sizeof(glm::vec3)) + sizeof(glm::vec2);
		break;
	case PositionTexture: VertexSize = sizeof(glm::vec3) + sizeof(glm::vec2);
		break;
	case PositionNormal: VertexSize = 2 * sizeof(glm::vec3);
		break;
	case PositionTextureNormal: VertexSize = (2 * sizeof(glm::vec3)) + sizeof(glm::vec2);
		break;
	case PositionColorTextureNormal: VertexSize = (3 * sizeof(glm::vec3)) + sizeof(glm::vec2);
		break;

	}


	totalBytes += WriteHeader(outputStream, numVerts, numIndices, VertexSize, sizeof(GLuint), SceneOutputFormat);
	totalBytes += WriteVertexData(outputStream, numVerts, vertices, colors, normals, texture, SceneOutputFormat);
	totalBytes += WriteIndices(outputStream, numIndices, indices);

	outputStream.seekp(0);
	WriteInt(outputStream, totalBytes);
	outputStream.close();
	printf("Total : wrote %d bytes.\n", totalBytes);
}

int BinaryOutput::WriteHeader(std::ofstream& out, int numVerts, int numIndices, int sizeVerts, int sizeIndices, int SceneOutputFormat)
{
	int totalBytes = 0;
	totalBytes += WriteInt(out, numVerts);
	totalBytes += WriteInt(out, numIndices);
	totalBytes += WriteInt(out, sizeVerts);
	totalBytes += WriteInt(out, sizeIndices);
	totalBytes += WriteInt(out, SceneOutputFormat);
	totalBytes += WritePointer(out, 2);
	return totalBytes;
}

int BinaryOutput::WriteInt(std::ofstream& out, int value)
{
	int size = sizeof(int);
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