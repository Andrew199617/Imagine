#include "FbxFileReader.h"
#include <algorithm>
#include "gtc\matrix_transform.hpp"
#include "gtx\transform.hpp"
#include "gtc\quaternion.hpp"
#include "gtx\quaternion.hpp"
# define PI 3.14159265358979323846f

using glm::vec3;
using glm::vec2;
using glm::mat4;
using glm::quat;

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
		fbxScene->Destroy();
		fbxManager->Destroy();
		delete[] fbxData.verts;
		delete[] fbxData.normals;
		delete[] fbxData.texture;
		if (fbxData.hasAnimation)
		{
			delete[] fbxData.keys;
			delete[] fbxData.animationData;
		}
	}
}

void FbxFileReader::Initialize(string fileName)
{
	fbxData.hasAnimation = false;
	GetName(fileName);
	ReadTextFile(fileName);

	fbxManager = FbxManager::Create();
	FbxIOSettings *ios = FbxIOSettings::Create(fbxManager, IOSROOT);
	fbxManager->SetIOSettings(ios);
	fbxScene = FbxScene::Create(fbxManager, fbxData.name.c_str());

	LoadScene(fileName);
	ProcessSkeletonHierarchy(fbxScene->GetRootNode());
	GetGeometryData();
	GetCenterOfMass();

	fbxData.SceneOutputFormat = 13;
	binaryOutput.WriteCustomBinaryFile(fbxData);
	deleteMemory = true;
}

void FbxFileReader::LoadScene(string fileName)
{
	FbxImporter* fbxImporter = FbxImporter::Create(fbxManager, "myImporter");
	

	fbxImporter->Initialize(fileName.c_str(), -1, fbxManager->GetIOSettings());

	fbxImporter->Import(fbxScene);
	fbxImporter->Destroy();
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

void FbxFileReader::GetAnimation(FbxNode* lNode)
{
	int numStacks = fbxScene->GetSrcObjectCount<FbxAnimStack>();
	for (int i = 0; i < numStacks; i++)
	{
		FbxAnimStack* currAnimStack = fbxScene->GetSrcObject<FbxAnimStack>(i);
		FbxString animStackName = currAnimStack->GetName();
		mAnimationName = animStackName.Buffer();
		FbxTakeInfo* takeInfo = fbxScene->GetTakeInfo(animStackName);
		FbxTime start = takeInfo->mLocalTimeSpan.GetStart();
		FbxTime end = takeInfo->mLocalTimeSpan.GetStop();
		mAnimationLength = end.GetFrameCount(FbxTime::eFrames24) - start.GetFrameCount(FbxTime::eFrames24) + 1;

		FbxAnimEvaluator* fbxAnimEval = fbxScene->GetAnimationEvaluator();
		fbxData.hasAnimation = true;
		fbxData.animationLength = (int)mAnimationLength;
		//int layerCount = currAnimStack->GetMemberCount<FbxAnimLayer>();
		FbxTime* keys;
		FbxAnimCurve* lAnimCurve;
		
		FbxAnimLayer* lAnimLayer = currAnimStack->GetMember<FbxAnimLayer>(0);
		lAnimCurve = lNode->LclTranslation.GetCurve(lAnimLayer, FBXSDK_CURVENODE_COMPONENT_Y);

		keys = new FbxTime[lAnimCurve->KeyGetCount()];
		fbxData.numKeys = lAnimCurve->KeyGetCount();
		fbxData.animationData = new mat4[fbxData.animationLength];
		for (int j2 = 0; j2 < lAnimCurve->KeyGetCount(); j2++)
		{
			keys[j2] = lAnimCurve->KeyGetTime(j2);
		}
		fbxData.keys = keys;
		for (int j = 0; j < fbxData.animationLength; j++)
		{

			FbxAMatrix matrix = fbxAnimEval->GetNodeLocalTransform(lNode, j * start.Get());
			FbxVector4 transform = matrix.GetT();
			vec3 translate = vec3(transform.mData[0], transform.mData[1], transform.mData[2]);
			transform = matrix.GetR();
			vec3 rotate = vec3(transform.mData[0], transform.mData[1], transform.mData[2]);
			transform = matrix.GetS();
			vec3 scale = vec3(transform.mData[0], transform.mData[1], transform.mData[2]);
			//cout << "X: " << transform.mData[0] << "Y: " << transform.mData[1] << "Z: " << transform.mData[2] << endl;
			mat4 translateMat = glm::translate(translate);
			rotate.x *= PI / 180.0f;
			rotate.y *= PI / 180.0f;
			rotate.z *= PI / 180.0f;
			quat myQuat = quat(rotate);
			mat4 rotateMat = glm::mat4_cast(myQuat);
			mat4 scaleMat = glm::scale(scale);
			fbxData.animationData[j] = translateMat * rotateMat * scaleMat;
		}
	}
}

void FbxFileReader::ProcessSkeletonHierarchy(FbxNode* inRootNode)
{

	for (int childIndex = 0; childIndex < inRootNode->GetChildCount(); ++childIndex)
	{
		FbxNode* currNode = inRootNode->GetChild(childIndex);
		ProcessSkeletonHierarchyRecursively(currNode, 0, 0, -1);
	}
}

void FbxFileReader::ProcessSkeletonHierarchyRecursively(FbxNode* inNode, int inDepth, int myIndex, int inParentIndex)
{
	if (inNode->GetNodeAttribute() && inNode->GetNodeAttribute()->GetAttributeType() && inNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
	{
		Joint currJoint;
		currJoint.mParentIndex = inParentIndex;
		currJoint.mName = inNode->GetName();
		mSkeleton.mJoints.push_back(currJoint);
	}
	for (int i = 0; i < inNode->GetChildCount(); i++)
	{
		ProcessSkeletonHierarchyRecursively(inNode->GetChild(i), inDepth + 1, mSkeleton.mJoints.size(), myIndex);
	}
}

void FbxFileReader::ProcessJointsAndAnimations(FbxNode* inNode)
{
	FbxMesh* currMesh = (FbxMesh*)inNode->GetNodeAttribute();
	unsigned int numOfDeformers = currMesh->GetDeformerCount();
	// This geometry transform is something I cannot understand
	// I think it is from MotionBuilder
	// If you are using Maya for your models, 99% this is just an
	// identity matrix
	// But I am taking it into account anyways......
	FbxAMatrix geometryTransform = Utilities::GetGeometryTransformation(inNode);

	// A deformer is a FBX thing, which contains some clusters
	// A cluster contains a link, which is basically a joint
	// Normally, there is only one deformer in a mesh
	for (unsigned int deformerIndex = 0; deformerIndex < numOfDeformers; ++deformerIndex)
	{
		// There are many types of deformers in Maya,
		// We are using only skins, so we see if this is a skin
		FbxSkin* currSkin = reinterpret_cast<FbxSkin*>(currMesh->GetDeformer(deformerIndex, FbxDeformer::eSkin));
		if (!currSkin)
		{
			continue;
		}

		unsigned int numOfClusters = currSkin->GetClusterCount();
		for (unsigned int clusterIndex = 0; clusterIndex < numOfClusters; ++clusterIndex)
		{
			FbxCluster* currCluster = currSkin->GetCluster(clusterIndex);
			std::string currJointName = currCluster->GetLink()->GetName();
			unsigned int currJointIndex = FindJointIndexUsingName(currJointName);
			FbxAMatrix transformMatrix;
			FbxAMatrix transformLinkMatrix;
			FbxAMatrix globalBindposeInverseMatrix;

			currCluster->GetTransformMatrix(transformMatrix);	// The transformation of the mesh at binding time
			currCluster->GetTransformLinkMatrix(transformLinkMatrix);	// The transformation of the cluster(joint) at binding time from joint space to world space
			globalBindposeInverseMatrix = transformLinkMatrix.Inverse() * transformMatrix * geometryTransform;

			// Update the information in mSkeleton 
			mSkeleton.mJoints[currJointIndex].mGlobalBindposeInverse = globalBindposeInverseMatrix;
			mSkeleton.mJoints[currJointIndex].mNode = currCluster->GetLink();

			// Associate each joint with the control points it affects
			unsigned int numOfIndices = currCluster->GetControlPointIndicesCount();
			for (unsigned int i = 0; i < numOfIndices; ++i)
			{
				BlendingIndexWeightPair currBlendingIndexWeightPair;
				currBlendingIndexWeightPair.mBlendingIndex = currJointIndex;
				currBlendingIndexWeightPair.mBlendingWeight = currCluster->GetControlPointWeights()[i];
				mControlPoints[currCluster->GetControlPointIndices()[i]]->mBlendingInfo.push_back(currBlendingIndexWeightPair);
			}

			// Get animation information
			// Now only supports one take
			FbxAnimStack* currAnimStack = fbxScene->GetSrcObject<FbxAnimStack>(0);
			FbxString animStackName = currAnimStack->GetName();
			mAnimationName = animStackName.Buffer();
			FbxTakeInfo* takeInfo = fbxScene->GetTakeInfo(animStackName);
			FbxTime start = takeInfo->mLocalTimeSpan.GetStart();
			FbxTime end = takeInfo->mLocalTimeSpan.GetStop();
			mAnimationLength = end.GetFrameCount(FbxTime::eFrames24) - start.GetFrameCount(FbxTime::eFrames24) + 1;
			Keyframe** currAnim = &mSkeleton.mJoints[currJointIndex].mAnimation;

			for (FbxLongLong i = start.GetFrameCount(FbxTime::eFrames24); i <= end.GetFrameCount(FbxTime::eFrames24); ++i)
			{
				FbxTime currTime;
				currTime.SetFrame(i, FbxTime::eFrames24);
				*currAnim = new Keyframe();
				(*currAnim)->mFrameNum = i;
				FbxAMatrix currentTransformOffset = inNode->EvaluateGlobalTransform(currTime) * geometryTransform;
				(*currAnim)->mGlobalTransform = currentTransformOffset.Inverse() * currCluster->GetLink()->EvaluateGlobalTransform(currTime);
				currAnim = &((*currAnim)->mNext);
			}
		}
	}

	// Some of the control points only have less than 4 joints
	// affecting them.
	// For a normal renderer, there are usually 4 joints
	// I am adding more dummy joints if there isn't enough
	BlendingIndexWeightPair currBlendingIndexWeightPair;
	currBlendingIndexWeightPair.mBlendingIndex = 0;
	currBlendingIndexWeightPair.mBlendingWeight = 0;
	for (auto itr = mControlPoints.begin(); itr != mControlPoints.end(); ++itr)
	{
		for (unsigned int i = itr->second->mBlendingInfo.size(); i <= 4; ++i)
		{
			itr->second->mBlendingInfo.push_back(currBlendingIndexWeightPair);
		}
	}
}

unsigned int FbxFileReader::FindJointIndexUsingName(const std::string& inJointName)
{
	for (unsigned int i = 0; i < mSkeleton.mJoints.size(); ++i)
	{
		if (mSkeleton.mJoints[i].mName == inJointName)
		{
			return i;
		}
	}
	throw std::exception("Skeleton information in FBX file is corrupted.");
}

void FbxFileReader::GetGeometryData()
{
	FbxNode* lRootNode = fbxScene->GetRootNode();
	GetIndcies();

	int curVert = 0;
	int vertexCounter = 0;
	if (lRootNode)
	{
		for (int i = 0; i < lRootNode->GetChildCount(); i++)
		{
			FbxNode* pFbxChildNode = lRootNode->GetChild(i);
			GetAnimation(pFbxChildNode);
			//ProcessJointsAndAnimations(pFbxChildNode);
			if (pFbxChildNode->GetNodeAttribute() == NULL)
				continue;

			FbxNodeAttribute::EType AttributeType = pFbxChildNode->GetNodeAttribute()->GetAttributeType();

			if (AttributeType != FbxNodeAttribute::eMesh)
				continue;

			FbxMesh* pMesh = (FbxMesh*)pFbxChildNode->GetNodeAttribute();

			FbxVector4* pVertices = pMesh->GetControlPoints();
			FbxGeometryElementNormal* normalEl = pMesh->GetElementNormal();
			FbxLayerElementArrayTemplate<FbxVector2>* uvVertices = 0;

			for (int j = 0; j < pMesh->GetPolygonCount(); j++)
			{
				int iNumVertices = pMesh->GetPolygonSize(j);
				assert(iNumVertices == 3);
				pMesh->GetTextureUV(&uvVertices, FbxLayerElement::eTextureDiffuse);

				for (int k = 0; k < iNumVertices; k++)
				{
					int iControlPointIndex = pMesh->GetPolygonVertex(j, k);

					//get Verts
					vec3 vec = glm::vec3((float)pVertices[iControlPointIndex].mData[0],
						(float)pVertices[iControlPointIndex].mData[1],
						(float)pVertices[iControlPointIndex].mData[2]);
					fbxData.verts[curVert] = vec;
					
					

					//get uvs
					FbxVector2 uv = uvVertices->GetAt(pMesh->GetTextureUVIndex(j, k));
					fbxData.texture[curVert].x = (float)uv[0];
					fbxData.texture[curVert].y = (float)uv[1];
					//cout << "\n" << uv[0] << " " << uv[1];
					curVert++;

				}
			}

			//get normals
			if (normalEl)
			{
				int numNormals = pMesh->GetPolygonCount();
				for (int j = 0; j < numNormals * 3; j++)
				{
					FbxVector4 normal = normalEl->GetDirectArray().GetAt(j);
					fbxData.normals[vertexCounter].x = (float)normal[0];
					fbxData.normals[vertexCounter].y = (float)normal[1];
					fbxData.normals[vertexCounter].z = (float)normal[2];
					//cout << "\n" << normal[0] << " " << normal[1] << " " << normal[2];
					vertexCounter++;
				}

			}

		}
	}
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
	fbxData.texture = new vec2[numindciesI];
	fbxData.normals = new vec3[numindciesI];
	
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

void FbxFileReader::GetCenterOfMass()
{
	float minX = FLT_MAX;
	float minY = FLT_MAX;
	float minZ = FLT_MAX;
	float maxX = FLT_MIN;
	float maxY = FLT_MIN;
	float maxZ = FLT_MIN;
	
	for (int i = 0; i < fbxData.numVerts; ++i)
	{
		vec3 vec = fbxData.verts[i];

		if (vec.x < minX)
		{
			minX = vec.x;
		}
		else if (vec.x > maxX)
		{
			maxX = vec.x;
		}
		
		if (vec.y < minY)
		{
			minY = vec.y;
		}
		else if (vec.y > maxY)
		{
			maxY = vec.y;
		}

		if (vec.z < minZ)
		{
			minZ = vec.z;
		}		
		else if (vec.z > maxZ)
		{
			maxZ = vec.z;
		}
	}
	
	fbxData.centerOfMass = glm::vec3((maxX + minX)/2 , (maxY + minY) / 2 , (maxZ + minZ) / 2);

}

