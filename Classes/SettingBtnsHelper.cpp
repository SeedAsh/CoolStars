#include "SettingBtnsHelper.h"
#include "UiLayout.h"
#include "CCFunctionAction.h"
USING_NS_CC;
using namespace std;

void SettingBtnsHelper::toggle()
{
	const float kDuration = 0.2f;
	if (m_isVisible)
	{
		for (auto iter = m_nodes.begin(); iter != m_nodes.end(); ++iter)
		{
			auto moveTo = CCMoveTo::create(kDuration, m_targetPos);
			auto func = bind(&SettingBtnsHelper::setAllNodesVisible, this, false);
			iter->first->runAction(CCSequence::create(CCEaseBackInOut::create(moveTo), CCFunctionAction::create(func), NULL));
		}
	}
	else
	{
		for (auto iter = m_nodes.begin(); iter != m_nodes.end(); ++iter)
		{
			setAllNodesVisible(true);
			auto moveTo = CCMoveTo::create(kDuration, iter->second);
			iter->first->runAction(CCEaseBackInOut::create(moveTo));
		}
	}
	

	m_isVisible = !m_isVisible;
}

void SettingBtnsHelper::addPopupNodes(cocos2d::CCNode *node)
{
	m_nodes.insert(make_pair(node, node->getPosition()));
}

void SettingBtnsHelper::setTargetPos(cocos2d::CCPoint pt)
{ 
	m_targetPos = pt;

	for (auto iter = m_nodes.begin(); iter != m_nodes.end(); ++iter)
	{
		iter->first->setPosition(pt);
		iter->first->setVisible(false);
	}
}

void SettingBtnsHelper::setAllNodesVisible(bool isVisible)
{
	for (auto iter = m_nodes.begin(); iter != m_nodes.end(); ++iter)
	{
		iter->first->setVisible(isVisible);
	}
}