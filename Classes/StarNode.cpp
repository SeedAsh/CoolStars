#include "StarNode.h"

using namespace cocos2d;
using namespace std;

static StarAttr _getStarAttrByIndex(int starIndex)
{
	StarAttr attr;
	attr.type = kColorStar;
	attr.color = (starIndex - 1) % 5 + 1;
	return attr;
}

StarNode *StarNode::createNodeFatory(int starIndex)
{
	StarAttr attr = _getStarAttrByIndex(starIndex);
	
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

