#include "BackgroundLayer.h"
#include "CCFunctionAction.h"
#include "UiLayout.h"
USING_NS_CC;
using namespace std;

bool BackgroundLayer::init()
{
	m_bkLayout = UiLayout::create("layout/common_background.xml");
	m_bkLayout->setAnchorPoint(ccp(0.5f, 0.5f));
	initLayout();
	auto size = m_bkLayout->getContentSize();
	m_bkLayout->setPosition(ccpMult(size, 0.5f));
	addChild(m_bkLayout);

	setContentSize(size);
	setAnchorPoint(ccp(0.5, 0.5));
	return true;
}

void BackgroundLayer::doMoveAction(CCNode *node, float speed, CCPoint sourcePos, CCPoint targetPos)
{
	node->setPosition(sourcePos);

	float duration = fabs((targetPos.x - sourcePos.x) / speed);
	CCMoveTo *moveTo = CCMoveTo::create(duration, targetPos);

	function<void()> func = bind(&BackgroundLayer::doMoveAction, this, node, speed, sourcePos, targetPos);
	node->runAction(CCSequence::create(moveTo, CCFunctionAction::create(func), NULL));
}

void BackgroundLayer::initLayout()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint sourcePos;
	CCPoint targetPos;
	float speed = 0;

	auto *clound1 = dynamic_cast<CCSprite *>(m_bkLayout->getChildById(2));
	sourcePos = ccp(winSize.width * 1.3f, clound1->getPositionY());
	targetPos = ccp(winSize.width * -0.3f, clound1->getPositionY());
	speed = (int)(CCRANDOM_0_1() * 100) + 50;
	doMoveAction(clound1, speed, sourcePos, targetPos);

	auto *clound2 = dynamic_cast<CCSprite *>(m_bkLayout->getChildById(3));
	sourcePos = ccp(winSize.width * -0.3f, clound2->getPositionY());
	targetPos = ccp(winSize.width * 1.3f, clound2->getPositionY());
	speed = (int)(CCRANDOM_0_1() * 100) + 50;
	doMoveAction(clound2, speed, sourcePos, targetPos);


}