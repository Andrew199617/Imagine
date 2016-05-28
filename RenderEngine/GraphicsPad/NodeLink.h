#pragma once
#include <fstream>
class NodeLink
{
public:
	NodeLink() : to((unsigned)-1), from((unsigned)-1), cost(FLT_MAX) {}
public:
	unsigned to;
	unsigned from;
	float cost;
};