#include "StarNode.h"
#include "StageModel.h"
#include "StarViewNode.h"

using namespace cocos2d;
using namespace std;

StarNode *StarNode::createNodeFatory(const StarAttr &attr)
{
	switch (attr.type)
	{
	case kRedStar:
		return new ColorStar(attr ,kColorRed);
	case kYellowStar:
		return new ColorStar(attr, kColorYellow);
	case kBlueStar:
		return new ColorStar(attr, kColorBlue);
	case kGreenStar:
		return new ColorStar(attr, kColorGreen);
	case kPurpleStar :
		return new ColorStar(attr, kColorPurple);
	case kStone:
		return new StoneNode();
	case kDeadVine:
		return new DeadVineNode();
	case kLiveVine:
		return new LiveVineNode();
	case kIron:
		return new IronNode();
	case kdiamond:
		return new diamondNode();
	case kKey:
		return new KeyNode();
	case kBomb:
		return new BombNode();
	case kBounceRedBall:
		return new BounceBallNode();
	case kBounceYellowBall:
		return new BounceBallNode();
	case kBounceBlueBall:
		return new BounceBallNode();
	case kBounceGreenBall:
		return new BounceBallNode();
	case kBouncePurpleBall:
		return new BounceBallNode();
	case kRandomColorStar:
		return new ColorStar(attr, kColorRandom);
	case kRandomBounceBall:
		return new BounceBallNode();
	default:
		return NULL;
		assert("no this node type!");
		break;
	}
}
StarNode::StarNode(const StarAttr &attr)
    : m_attr(attr)
	, m_view(NULL)
{
}

const StarsConfig &StarNode::getConfig()
{
	return DataManagerSelf->getStarsConfig(m_attr.type);
}

void StarNode::handleClick()
{
	std::vector<StarNode *> connectedNodes;
	getConnectedStars(this, connectedNodes);
	size_t count = connectedNodes.size();
    for(size_t i = 0; i < count; ++i)
    {
        auto grid = connectedNodes[i]->getAttr().grid;
        
    }
	if (count >= CONNECT_COUNT)
	{
		StageModel::theModel()->moveOneStep();
		for (size_t j = 0; j < count; ++j)
		{
			connectedNodes[j]->removeSelf();
		}
	}
}

void StarNode::removeSelf(bool withExplosion)
{
	if (m_view)
	{
		m_view->removeSelf(withExplosion);
	}
	StageModel::theModel()->removeStarNode(this);
}

void StarNode::getConnectedStars(StarNode *node, std::vector<StarNode *> &connectedNodes)
{
     auto grid = node->getAttr().grid;
	if (find(connectedNodes.begin(), connectedNodes.end(), node) != connectedNodes.end())
	{
		return;
	}

	connectedNodes.push_back(node);
    
	auto neighbours = node->getNeighbours();
	if (!neighbours.empty())
	{
        for (size_t i = 0; i < neighbours.size(); ++i)
        {
            auto temp = neighbours[i]->getAttr().grid;
        }
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
        auto temp = LogicGrid(grid.x + arr[i][0], grid.y + arr[i][1]);
		StarNode *neighbour = StageModel::theModel()->getStarNode(temp);
		
		if (neighbour != NULL)
		{
			if (neighbour->isNeighbour(m_attr.type))
			{
				neighbours.push_back(neighbour);
			}
		}
	}
	return neighbours;
}


void StarNode::moveTo(LogicGrid grid)
{
	if (m_view)
	{
		m_view->doMove(grid);
	}
}



bool ColorStar::isNeighbour(int type)
{
	return m_attr.type == type;
}
