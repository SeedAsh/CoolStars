#include "StageMaskLayer.h"
#include "CommonMacros.h"
#include "DataManager.h"
USING_NS_CC;
using namespace std;

bool StageMaskLayer::init()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	setContentSize(winSize);

	CCLayerColor *mask = CCLayerColor::create(ccc4(0, 0, 0, 175));
	mask->setContentSize(winSize);
	addChild(mask);
	
	setVisible(false);
	return true;
}

void StageMaskLayer::onEnter()
{
	CCNode::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kStageMaskTouchPriority, false);
	StageModel::theModel()->addView(this);
}

void StageMaskLayer::onExit()
{
	CCNode::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	StageModel::theModel()->removeView(this);

}

bool StageMaskLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	setVisible(false);
	return true;
}

void StageMaskLayer::onHighLightStars(int color)
{
	for (int i = 0; i < COLOR_AMOUNT; ++i)
	{
		int color = i + kColorRed;
		auto config = DataManagerSelf->getStarsColorConfig(color);
		auto resPath = config.colorStarRes;

		CCSprite *starSpr = CCSprite::create(resPath.c_str());
	}
}