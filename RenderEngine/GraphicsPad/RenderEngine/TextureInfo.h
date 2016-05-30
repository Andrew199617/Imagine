#pragma once
#include "GL\glew.h"
#include <string>

using namespace std;

class TextureInfo
{
public:
	TextureInfo(){};
	TextureInfo(string FileLocation,string BumpLocation);
	~TextureInfo();
	void loadBMP_customFile(string texpath);
	void loadBMP_customFileBumpMap(string texpath);
	void bindTexture(GLint tex,GLint);
	void SendData(GLint tex, GLint);
	string objName;

	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int texWidth, texHeight;
	unsigned int imageSize;   // = width*height*3
	// Actual RGB data
	unsigned char * texData;
	float texCoordOffsets[18];

	unsigned int bumpWidth, bumpHeight;
	unsigned char * bumpData;
};

