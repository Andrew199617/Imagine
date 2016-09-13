#pragma once
#include <string>
#include "FbxData.h"
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;


class FileReader
{
public:
	FileReader(string fileName);
	~FileReader();

	void GetName(string fileName);
	void GetVerticies();
	void GetIndcies();
	void GetTextureUVs();
	void OrderTextureUVs();

	void ReadTextFile(string filename);

	stringstream buffer;
	FbxData fbxData;
private:
	FbxData fbxDataUnordered;
};

