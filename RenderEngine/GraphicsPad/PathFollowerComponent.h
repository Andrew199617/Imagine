#pragma once
#include "ImgnComponent.h"
#include "NodeMap.h"
#include "PathFinding.h"
class SeekBehaviorComponent;

class PathFollowerComponent :
	public ImgnComponent
{
public:
	PathFollowerComponent();
	~PathFollowerComponent();

	bool Initialize() override;
	bool Update(float dt) override;
	void setNodeMap(NodeMap nodemap) { m_pathFinder.setNodeMap(nodemap); }
	void setStartAndGoal(Node start, Node goal) { m_start = start; m_goal = goal; }
	void Done(SeekBehaviorComponent* seek);

private:
	Node m_start;
	Node m_goal;
	PathFinding m_pathFinder;
};

