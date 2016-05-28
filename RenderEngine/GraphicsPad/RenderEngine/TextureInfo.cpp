#include "TextureInfo.h"
#include <stdio.h>
#include "..\ConfigReader.h"
#include "VertexShaderInfo.h"

TextureInfo::TextureInfo(string FileLocation, string objName)
{
	if(FileLocation != "0")
	loadBMP_customFile(FileLocation);
	string bumpPath = ConfigReader::findValueForKey(objName + "BumpMap");
	if(bumpPath != "0")
	loadBMP_customFileBumpMap(bumpPath);
}

TextureInfo::~TextureInfo()
{
}

void TextureInfo::loadBMP_custom(string m_objName)
{
	ConfigReader::Initialize();
	string texpath = ConfigReader::findValueForKey(m_objName + "Texture");
	const char* imagepath = texpath.c_str();
#pragma warning(push)
#pragma warning (disable:4996)
	FILE * file = fopen(imagepath, "rb");
#pragma warning(pop)
	if (!file)                             
	{ printf("Image could not be opened\n"); return; }

	if (fread(header, 1, 54, file) != 54){ // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return;
	}

	if (header[0] != 'B' || header[1] != 'M'){
		printf("Not a correct BMP file\n");
		return;
	}

	this->dataPos = *(int*)&(header[0x0A]);
	this->imageSize = *(int*)&(header[0x22]);
	this->texWidth = *(int*)&(header[0x12]);
	this->texHeight = *(int*)&(header[0x16]);

	if (imageSize == 0)    this->imageSize = texWidth*texHeight * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      this->dataPos = 54;

	this->texData = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(texData, 1, imageSize, file);

	//Everything is in memory now, the file can be closed
	fclose(file);
}

void TextureInfo::loadBMP_customFile(string texpath)
{
	
	const char* imagepath = texpath.c_str();
#pragma warning(push)
#pragma warning (disable:4996)
	FILE * file = fopen(imagepath, "rb");
#pragma warning(pop)
	if (!file)
	{
		printf("Image could not be opened\n"); return;
	}

	if (fread(header, 1, 54, file) != 54){ // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return;
	}

	if (header[0] != 'B' || header[1] != 'M'){
		printf("Not a correct BMP file\n");
		return;
	}

	this->dataPos = *(int*)&(header[0x0A]);
	this->imageSize = *(int*)&(header[0x22]);
	this->texWidth = *(int*)&(header[0x12]);
	this->texHeight = *(int*)&(header[0x16]);

	if (imageSize == 0)    this->imageSize = texWidth*texHeight * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      this->dataPos = 54;

	this->texData = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(texData, 1, imageSize, file);

	//Everything is in memory now, the file can be closed
	fclose(file);
}

void TextureInfo::loadBMP_customFileBumpMap(string bumpPath)
{
	const char* imagepath = bumpPath.c_str();
#pragma warning(push)
#pragma warning (disable:4996)
	FILE * file = fopen(imagepath, "rb");
#pragma warning(pop)
	if (!file)
	{
		printf("Image could not be opened\n"); return;
	}

	if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return;
	}

	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return;
	}

	this->dataPos = *(int*)&(header[0x0A]);
	this->imageSize = *(int*)&(header[0x22]);
	this->bumpWidth = *(int*)&(header[0x12]);
	this->bumpHeight = *(int*)&(header[0x16]);

	if (imageSize == 0)    this->imageSize = bumpWidth*bumpHeight * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      this->dataPos = 54;

	this->bumpData = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(bumpData, 1, imageSize, file);

	//Everything is in memory now, the file can be closed
	fclose(file);
}

void TextureInfo::bindTexture(GLint tex,GLint bumpMap,GLint texCoord)
{
	float xInc = 1.0f / float(texWidth);
	float yInc = 1.0f / float(texHeight);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			texCoordOffsets[(((i * 3) + j) * 2) + 0] = (-1.0f * xInc) + (float(i) * xInc);
			texCoordOffsets[(((i * 3) + j) * 2) + 1] = (-1.0f * yInc) + (float(j) * yInc);
		}
	}

	glUniform2fv(texCoord, 9, &texCoordOffsets[0]);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, tex);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, texData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	if (bumpMap != -1)
	{
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, bumpMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bumpWidth, bumpHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, bumpData);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
}