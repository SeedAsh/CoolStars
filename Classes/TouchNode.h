#ifndef __TOUCHNODE_H__
#define __TOUCHNODE_H__
#include "cocos2d.h"

class TouchNode
	: public cocos2d::CCNode
	, public cocos2d::CCTouchDelegate
{
public:
	virtual ~TouchNode(){}
	virtual bool init();
protected:
	TouchNode(int touchPriority = 0){}
	virtual void onTouchBegan(){}
private:
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
private:
	int m_touchPriority;
};
#endif