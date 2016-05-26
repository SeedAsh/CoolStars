#include "StarNode.h"
using namespace cocos2d;
StarNode *StarNode::create()
{
	StarNode *node = new StarNode();
	node->autorelease();
	node->init();
	return node;
}

bool StarNode::init()
{
	return true;
}