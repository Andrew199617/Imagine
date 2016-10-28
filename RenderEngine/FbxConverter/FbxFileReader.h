#pragma once
#include <sstream>
#include <iostream>
#include "BinaryOutput.h"
#include <unordered_map>
#include "Utilities.h"

using namespace std;

class FbxFileReader
{
public:
	FbxFileReader();
	FbxFileReader(string fileName);
	~FbxFileReader();

	void Initialize(string fileName);
	void LoadScene(string fileName);
	string GetName(string fileName);
	void GetAnimation(FbxNode* lNode);
	void ProcessSkeletonHierarchy(FbxNode * inRootNode);
	void ProcessSkeletonHierarchyRecursively(FbxNode * inNode, int inDepth, int myIndex, int inParentIndex);
	void ProcessJointsAndAnimations(FbxNode * inNode);
	unsigned int FindJointIndexUsingName(const std::string & inJointName);
	void GetGeometryData();
	void GetIndcies();
	void GetTextureUVs();
	void OrderTextureUVs();

	void ReadTextFile(string filename);

	
	FbxData fbxData;
private:
	FbxManager* fbxManager;
	FbxScene* fbxScene;
	BinaryOutput binaryOutput;
	Skeleton mSkeleton;

	unordered_map<unsigned int, CtrlPoint*> mControlPoints;
	FbxLongLong mAnimationLength;
	string mAnimationName;
	stringstream buffer;
	bool deleteMemory = false;
	void GetCenterOfMass();
};

