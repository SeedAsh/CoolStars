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
	m_container = CCNode::create();
	addChild(m_container);
	
	setVisible(false);
	return true;
}

void StageMaskLayer::onEnter()
{
	CCNode::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kStageMaskTouchPriority, true);
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
	if (!isVisible()) return false;

	setVisible(false);
	auto pos = convertToNodeSpace(pTouch->getLocation());
	for (size_t i = 0; i < m_stars.size(); ++i)
	{
		auto node = m_stars[i];
		if (node->boundingBox().containsPoint(pos))
		{
			return false;
		}
	}

	StageModel::theModel()->toNormalState();
	return true;
}

void StageMaskLayer::onHighLightStars(int color)
{
	m_container->removeAllChildren();
	m_stars.clear();

	setVisible(true);
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
			m_container->addChild(starSpr);
			m_stars.push_back(starSpr);
		}
	}
}