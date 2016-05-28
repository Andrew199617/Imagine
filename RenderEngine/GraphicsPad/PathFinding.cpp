#include "PathFinding.h"
#include <unordered_map>


PathFinding::PathFinding()
{
	Initialize();
}


PathFinding::~PathFinding()
{
}

bool PathFinding::Initialize()
{
	m_intializedStartGoal = false;
	m_foundGoal = false;
	m_atTarget = false;
	m_noPathPossible = false;
	index = 1;
	return true;
}

void PathFinding::FindPath(Node start, Node goal)
{
	if (m_nodeMap.m_links == 0)
	{
		string s = ": Path Finder's node map was never set";
		GameLogger::log(m_owner->GetName() + s);
		return;
	}
	if (!m_intializedStartGoal)
	{
		for (unsigned i = 0; i < m_openList.size(); i++)
		{
			delete m_openList[i];
		}
		ClearOpenList();
		for (unsigned i = 0; i < m_closedList.size(); i++)
		{
			delete m_closedList[i];
		}
		ClearClosedList();
		for (unsigned i = 0; i < m_pathToGoal.size(); i++)
		{
			delete m_pathToGoal[i];
		}
		ClearPathToGoal();

		SearchNode searchNodeStart;
		searchNodeStart.node = start;

		SearchNode searchNodeGoal;
		searchNodeGoal.node = goal;

		SetStartAndGoal(searchNodeStart, searchNodeGoal);
		m_intializedStartGoal = true;
	}
	if (m_intializedStartGoal)
	{
		ContinuePath();
	}
	

}

glm::vec3 PathFinding::NextPathPos(SpatialComponent*,float radius)
{
	
	glm::vec3 nextPos;
	nextPos.x = m_pathToGoal[m_pathToGoal.size() - index]->x;
	nextPos.y = m_pathToGoal[m_pathToGoal.size() - index]->y;
	nextPos.z = m_pathToGoal[m_pathToGoal.size() - index]->z;
	
	radius;
	
	/*if (index == m_pathToGoal.size())
	{
		if (distance.length() <= radius)
		{
			m_pathToGoal.erase(m_pathToGoal.end() - index);
		}
	}*/
	
	if (nextPos == m_goalCell->node.position)
	{
		m_atTarget = true;
	}


	return nextPos;
}

void PathFinding::SetStartAndGoal(SearchNode start, SearchNode goal)
{
	m_startCell = new SearchNode(start.node);
	m_goalCell = new SearchNode(goal.node);

	m_startCell->G = 0;
	m_startCell->H = m_startCell->ManHattanDistance(m_goalCell);
	m_startCell->parent = 0;

	m_openList.push_back(m_startCell);
}

void PathFinding::PathOpened(Node node, float newCost, SearchNode * parent)
{
	/*if (NODE_BLOCKED)
	{
		return;
	}*/
	
	for (unsigned i = 0; i < m_closedList.size(); i++)
	{
		if (node.id == m_closedList[i]->node.id)
		{
			return;
		}
	}

	SearchNode * child = new SearchNode(node,parent);
	child->G = newCost;
	//??
	child->H = child->ManHattanDistance(m_goalCell);

	for (unsigned i = 0; i < m_openList.size(); i++)
	{
		if (node.id == m_openList[i]->node.id)
		{
			float newF = newCost + m_openList[i]->H;
			
			if (m_openList[i]->getF() > newF)
			{
				m_openList[i]->G = newCost;
				//??
				m_openList[i]->parent = parent;
			}
			else
			{
				delete child;
				return;
			}
		}
	}

	m_openList.push_back(child);
}

SearchNode * PathFinding::getNextNode()
{
	float bestF = FLT_MAX;
	int nodeIndex = -1;
	SearchNode* nextNode = 0;

	for (unsigned i = 0; i < m_openList.size(); i++)
	{
		if (m_openList[i]->getF() < bestF)
		{
			bestF = m_openList[i]->getF();
			nodeIndex = i;
		}
	}

	if (nodeIndex >= 0)
	{
		nextNode = m_openList[nodeIndex];
		m_closedList.push_back(nextNode);
		m_openList.erase(m_openList.begin() + nodeIndex);
	}
	return nextNode;
}

void PathFinding::ContinuePath()
{
	if (m_openList.empty())
	{
		//GameLogger::log("Open list is empty");
		m_noPathPossible = true;
		return;
	}

	SearchNode* currentcell = getNextNode();

	if (currentcell->node.id == m_goalCell->node.id)
	{
		m_goalCell->parent = currentcell->parent;

		SearchNode* getPath;

		for (getPath = m_goalCell; getPath != 0; getPath = getPath->parent)
		{
			m_pathToGoal.push_back(new glm::vec3(getPath->node.position));
		}

		m_foundGoal = true;
		return;
	}
	else
	{
		for (unsigned i = 0; i < m_nodeMap.m_nodeData->numLinks; i++)
		{
			if (currentcell->node.id == m_nodeMap.m_links[i].from)
			{
				PathOpened(m_nodeMap.m_nodes[m_nodeMap.m_links[i].to]
					,currentcell->G + m_nodeMap.m_links[i].cost,currentcell);
			}
			
		}

		for (unsigned i = 0; i < m_openList.size(); i++)
		{
			if (currentcell->node.id == m_openList[i]->node.id)
			{
				m_openList.erase(m_openList.begin() + i);
			}
		}
	}

}