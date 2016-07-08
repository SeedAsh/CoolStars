#ifndef __STAGEMASKLAYER_H__
#define __STAGEMASKLAYER_H__

#include "cocos2d.h"
#include "StarsController.h"

class StageMaskLayer
	: public cocos2d::CCNode
	, public cocos2d::CCTouchDelegate
	, public IStarsControlView
{
public:
	CREATE_FUNC(StageMaskLayer);
	virtual ~StageMaskLayer(){}
private:
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	virtual void onHighLightStars(int color);

private:
	std::vector<cocos2d::CCNode *> m_stars;
	cocos2d::CCNode *m_container;
};
#endif
