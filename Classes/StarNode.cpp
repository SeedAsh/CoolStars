#include "StarNode.h"
#include "StageModel.h"
#include "StarViewNode.h"

using namespace cocos2d;
using namespace std;

StarNode *StarNode::createNodeFatory(StarAttr &attr)
{
	switch (attr.type)
	{
	case kColorStar:
		return new ColorStar(attr);
		break;
	case kStone:
		return new StoneNode();
		break;
	case kDeadVine:
		return new DeadVineNode();
		break;
	case kLiveVine:
		return new LiveVineNode();
		break;
	case kIron:
		return new IronNode();
		break;
	case kBounceBall:
		return new BounceBallNode();
		break;
	case kdiamant:
		return new diamantNode();
		break;
	case kKey:
		return new KeyNode();
		break;
	case kBomb:
		return new BombNode();
		break;
	default:
		return NULL;
		break;
	}
}

void StarNode::handleClick()
{
	std::vector<StarNode *> connectedNodes;
	getConnectedStars(this, connectedNodes);
	size_t count = connectedNodes.size();
	if (count >= CONNECT_COUNT)
	{
		for (size_t i = 0; i < count; ++i)
		{
			connectedNodes[i]->runExplosion();
		}
	}
}

void StarNode::runExplosion()
{
	m_view->runExplosion();
}

void StarNode::getConnectedStars(StarNode *node, std::vector<StarNode *> &connectedNodes)
{
	if (find(connectedNodes.begin(), connectedNodes.end(), node) != connectedNodes.end())
	{
		return;
	}

	connectedNodes.push_back(node);
	auto neighbours = getNeighbours();
	if (!neighbours.empty())
	{
		for (size_t i = 0; i < neighbours.size(); ++i)
		{
			getConnectedStars(neighbours[i], connectedNodes);
		}
	}
}

vector<StarNode *> StarNode::getNeighbours()
{
	vector<StarNode *> neighbours;
	LogicGrid grid = m_attr.grid;
	int arr[4][2] = { { 1, 0 }, { -1, 0 }, { 0, -1 }, { 0, 1 } };
	for (int i = 0; i < 4; ++i)
	{
		StarNode *neighbour = StageModel::theModel()->getStarData(LogicGrid(grid.x + arr[i][0], grid.y + arr[i][1]));
		
		if (neighbour != NULL)
		{
			if (neighbour->getAttr().color == m_attr.color)
			{
				neighbours.push_back(neighbour);
			}
		}
	}
	return neighbours;
}