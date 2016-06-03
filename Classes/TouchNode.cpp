#include "TouchNode.h"
using namespace std;
USING_NS_CC; 
//子类设置了contentsize 之后调用即可
bool TouchNode::init()
{
	return true;
}

void TouchNode::onEnter(){
	CCNode::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void TouchNode::onExit(){
	CCNode::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool TouchNode::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	auto pos = convertToNodeSpace(pTouch->getLocation());
	auto size = getContentSize();
	CCRect rect(0, 0, size.width, size.height);
	if (rect.containsPoint(pos))
	{
		onTouchBegan();
		return true;
	}
	return false;
}