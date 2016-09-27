#pragma once
#include <sstream>
#include <iostream>
#include "BinaryOutput.h"

using namespace std;


class FbxFileReader
{
public:
	FbxFileReader();
	FbxFileReader(string fileName);
	~FbxFileReader();

	void Initialize(string fileName);
	string GetName(string fileName);
	void GetVerticies();
	void GetIndcies();
	void GetTextureUVs();
	void OrderTextureUVs();

	void ReadTextFile(string filename);

	bool deleteMemory = false;
	stringstream buffer;
	FbxData fbxData;
private:
	FbxData fbxDataUnordered;
	BinaryOutput binaryOutput;
};

