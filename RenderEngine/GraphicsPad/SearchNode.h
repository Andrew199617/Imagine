#pragma once
#include "Node.h"

struct SearchNode
{
	Node node;
	SearchNode* parent;
	float G;
	float H;

	SearchNode() : parent(0) {}
	SearchNode(Node _node, SearchNode* _parent = 0) : node(_node),
		parent(_parent), G(0), H(0) {}

	float getF() { return G + H; }
	float ManHattanDistance(SearchNode* nodeEnd) 
	{
		float x = glm::length(node.position - nodeEnd->node.position);
		return x;
	}
};
