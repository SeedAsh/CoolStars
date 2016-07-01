#include "PetSceneMoveHelper.h"
#include "CCFunctionAction.h"
USING_NS_CC;
using namespace std;

const float PetSceneMoveHelper::kFirstMoveDuation = 0.2f;
const float PetSceneMoveHelper::kSecondMoveDuation = 0.5f;

PetSceneMoveHelper::PetSceneMoveHelper()
: m_curNode(NULL)
{

}

void PetSceneMoveHelper::init(const cocos2d::CCPoint &leftmost, const cocos2d::CCPoint &center, const cocos2d::CCPoint &rightmost)
{
	m_leftmostPos = leftmost;
	m_centerPos = center;
	m_rightmostPos = rightmost;
}

void PetSceneMoveHelper::setCenterNode(cocos2d::CCNode *centerNode)
{
	centerNode->setAnchorPoint(ccp(0.5f, 0.5f));
	centerNode->setPosition(m_centerPos);
	m_curNode = centerNode;
}

void PetSceneMoveHelper::moveLeft(cocos2d::CCNode *newNode)
{
	if (m_curNode)
	{
		auto removeFunc = CCFunctionAction::create([=]()
		{
			m_curNode->removeFromParent();
		});
		m_curNode->runAction(CCSequence::create(CCMoveTo::create(kFirstMoveDuation, m_leftmostPos), removeFunc, NULL));
		m_curNode = NULL;
	}

	newNode->setAnchorPoint(ccp(0.5f, 0.5f));
	newNode->setPosition(m_rightmostPos);
	auto curNodeFunc = CCFunctionAction::create([&]()
	{
		m_curNode = newNode;
	});
	newNode->runAction(CCSequence::create(CCMoveTo::create(kSecondMoveDuation, m_centerPos), curNodeFunc, NULL));
}

void PetSceneMoveHelper::moveRight(cocos2d::CCNode *newNode)
{
	if (m_curNode)
	{
		auto removeFunc = CCFunctionAction::create([=]()
		{
			m_curNode->removeFromParent();
		});
		m_curNode->runAction(CCSequence::create(CCMoveTo::create(kFirstMoveDuation, m_rightmostPos), removeFunc, NULL));
		m_curNode = NULL;
	}

	newNode->setAnchorPoint(ccp(0.5f, 0.5f));
	newNode->setPosition(m_leftmostPos);
	auto curNodeFunc = CCFunctionAction::create([&]()
	{
		m_curNode = newNode;
	});
	newNode->runAction(CCSequence::create(CCMoveTo::create(kSecondMoveDuation, m_centerPos), curNodeFunc, NULL));
}

void PetSceneMoveHelper::clearNodes()
{
	if (m_curNode)
	{
		m_curNode->removeFromParentAndCleanup(true);
		m_curNode = NULL;
	}
}

