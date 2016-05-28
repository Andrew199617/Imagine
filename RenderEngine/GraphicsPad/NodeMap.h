#pragma once
#include "Node.h"
#include "NodeLink.h"
#include "PathingNodes.h"
#include <string.h>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm.hpp>
#pragma warning(pop)

using namespace std;

class NodeMap
{
public:
	NodeMap() : m_nodes(0), m_links(0), m_nodeData(0) {  }
	~NodeMap()
	{
		//char* p = reinterpret_cast<char*>(m_nodeData);
		//delete[] p;
	}
	bool ReadPathingFile(string filename);
	void Dump(string filename);
public:
	Node* m_nodes;
	NodeLink* m_links;
	PathingNodes* m_nodeData;
};