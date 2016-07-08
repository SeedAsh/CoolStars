#include "StageMaskLayer.h"
#include "CommonMacros.h"
#include "DataManager.h"
#include "StarNode.h"
#include "StarViewNode.h"
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
	CCNode *node = CCNode::create();
	auto nodes = StageModel::theModel()->getStarNodes();
	for (size_t i = 0; i < nodes.size(); ++i)
	{
		auto attr = nodes[i]->getAttr();
		if (attr.type == kColorStar && attr.color == color)
		{
			auto view = nodes[i]->getView();
			auto resPath = nodes[i]->getResPath();
			auto pos = view->getParent()->convertToWorldSpace(view->getPosition());
			CCSprite *starSpr = CCSprite::create(resPath.c_str());
			starSpr->setPosition(pos);
			starSpr->setAnchorPoint(ccp(0, 0));
			node->addChild(starSpr);
		}
	}
	addChild(node);
}