#pragma once
#include "NodeMap.h"
#include "GameLogger.h"
#include "Component.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm.hpp>
#pragma warning(pop)
#include <unordered_map>
#include "SearchNode.h"
#include "SpatialComponent.h"


class PathFinding
{
public:
	PathFinding();
	~PathFinding();

public:
	bool Initialize();
	void FindPath(Node start, Node goal);
	glm::vec3 NextPathPos(SpatialComponent*,float);
	void ClearOpenList() { m_openList.clear(); }
	void ClearClosedList() { m_closedList.clear(); }
	void ClearPathToGoal() { m_pathToGoal.clear(); }
	void setOwner(Component* owner) { m_owner = owner; }
	void setNodeMap(NodeMap node) { m_nodeMap = node; }

private:
	void SetStartAndGoal(SearchNode start,SearchNode goal);
	void PathOpened(Node node, float newCost, SearchNode* parent);
	SearchNode* getNextNode();
	void ContinuePath();

public:
	bool m_intializedStartGoal;
	bool m_foundGoal;
	bool m_atTarget;
	bool m_noPathPossible;
	unsigned index;

private:
	NodeMap m_nodeMap;
	Component* m_owner;
	SearchNode* m_startCell;
	SearchNode* m_goalCell;
	std::vector<SearchNode*> m_openList;
	std::vector<SearchNode*> m_closedList;
	std::vector<glm::vec3*> m_pathToGoal;

};

