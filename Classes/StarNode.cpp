#include "StarNode.h"
#include "StageModel.h"
#include "StarViewNode.h"
#include "CommonUtil.h"

using namespace cocos2d;
using namespace std;

StarNode *StarNode::createNodeFatory(const StarAttr &attr)
{
	switch (attr.type)
	{
	case kColorStar:
		return new ColorStar(attr);
	case kBounceBall:
		return new BounceBallNode(attr);
	case kDeadVine:
		return new DeadVineNode(attr);
	case kLiveVine:
		return new LiveVineNode(attr);
	case kStone:
		return new StoneNode(attr);
	case kBomb:
		return new BombNode(attr);
	case kIron:
		return new IronNode(attr);
	case kDiamond:
		return new DiamondNode(attr);
	case kKey:
		return new KeyNode(attr);
	default:
		assert("no this node type!");
		return NULL;
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

bool StarNode::canLink(int type, int color)
{ 
	auto linkTypes = getConfig().linkStarTypes;
	if (find(linkTypes.begin(), linkTypes.end(), type) != linkTypes.end())
	{
		return m_attr.color == color;
	}
	return false;
}

string StarNode::getResPath()
{
	return getConfig().resPath;
}

string StarNode::getExplosionPath()
{
	return getConfig().explosionPath;
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
		for (size_t j = 0; j < count; ++j)
		{
			auto node = connectedNodes[j];
			node->removeNeighbours();
			node->doRemove();
		}
		StageModel::theModel()->moveOneStep();
	}
}

void StarNode::doRemove(bool withExplosion)
{
	if (m_view)
	{
		int myScore = getConfig().score;
		StageModel::theModel()->addScore(myScore);//±¬Õ¨Ôò¼Ó·Ö
		m_view->removeSelf(withExplosion);
	}
	onRemove();
	StageModel::theModel()->removeStarNode(this);
}

void StarNode::removeNeighbours()
{
	auto neightbours = getNeighbours();
	for (size_t i = 0; i < neightbours.size(); ++i)
	{
		auto node = neightbours[i];
		auto eraseTypes = node->getConfig().eraseTypes;
		if (find(eraseTypes.begin(), eraseTypes.end(), kNeightbourErase) != eraseTypes.end())
		{
			node->doRemove();
		}
	}
}

void StarNode::getConnectedStars(StarNode *node, std::vector<StarNode *> &connectedNodes)
{
     auto grid = node->getAttr().grid;
	if (find(connectedNodes.begin(), connectedNodes.end(), node) != connectedNodes.end())
	{
		return;
	}

	connectedNodes.push_back(node);
    
	auto neighbours = node->getLinkNeighbours();
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

vector<StarNode *> StarNode::getLinkNeighbours()
{
	vector<StarNode *> linkNodes;
	auto neighbours = getNeighbours();
	for (size_t i = 0; i < neighbours.size(); ++i)
	{

		StarNode *neighbour = neighbours[i];

		if (neighbour != NULL)
		{
			if (neighbour->canLink(m_attr.type, m_attr.color))
			{
				linkNodes.push_back(neighbour);
			}
		}
	}
	return linkNodes;
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
		if (neighbour)
		{
			neighbours.push_back(neighbour);
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

/////////////////////////////////////////////////////////////////////////////////
ColorStar::ColorStar(const StarAttr &attr)
: StarNode(attr)
{ 
	if (m_attr.color == kColorRandom)
	{
		m_attr.color = CommonUtil::getRandomValue(kColorRed, kColorPurple);
	}
}

ColorStar::~ColorStar()
{
}


std::string ColorStar::getResPath()
{
	auto config = DataManagerSelf->getStarsColorConfig(m_attr.color);
	return config.colorStarRes;
}

std::string ColorStar::getExplosionPath()
{
	auto config = DataManagerSelf->getStarsColorConfig(m_attr.color);
	return config.colorExplosionRes;
}

/////////////////////////////////////////////////////////////////////////////////
BounceBallNode::BounceBallNode(const StarAttr &attr)
: StarNode(attr)
{
	if (m_attr.color == kColorRandom)
	{
		m_attr.color = CommonUtil::getRandomValue(kColorRed, kColorPurple);
	}
}


std::string BounceBallNode::getResPath()
{
	auto config = DataManagerSelf->getStarsColorConfig(m_attr.color);
	return config.bounceBallRes;
}

std::string BounceBallNode::getExplosionPath()
{
	auto config = DataManagerSelf->getStarsColorConfig(m_attr.color);
	return config.bounceBallExplosionRes;
}
/////////////////////////////////////////////////////////////////////////////////
void DeadVineNode::onRemove()
{
	auto attr = m_attr;
	attr.type = kColorStar;
	StageModel::theModel()->replaceStar(attr);
}
/////////////////////////////////////////////////////////////////////////////////
void LiveVineNode::onRemove()
{
	auto attr = m_attr;
	attr.type = kColorStar;
	StageModel::theModel()->replaceStar(attr);
}
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
