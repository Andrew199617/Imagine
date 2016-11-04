#pragma once
#include "GL\glew.h"
#include <string>

using namespace std;

class TextureInfo
{

public:
	TextureInfo(string FileLocation = "0",string BumpLocation = "0");

	void InitializeValues();

	~TextureInfo();
	void loadBMP_customFile(string texpath);
	void loadBMP_customFileBumpMap(string texpath);
	void bindTexture();
	void unBindTexture();
	void SendData();
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
	bool IsBumped() { return bumped; }
private:
	bool bumped;
	bool textured;
	int texLoc;
	int bumpLoc;
};

