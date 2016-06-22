#include "ShopScene.h"
#include "UiLayout.h"
#include "MenuScene.h"
#include "TitlePanel.h"
#include "ListView.h"
#include "ListSlideView.h"

USING_NS_CC;
using namespace std;

bool ShopNode::init()
{
	m_layout = UiLayout::create("layout/shop_node.xml");
	addChild(m_layout);
	setContentSize(m_layout->getContentSize());

	CCMenuItem *buyBtn = dynamic_cast<CCMenuItem *>((m_layout->getChildById(3)));
	buyBtn->setTarget(this, menu_selector(ShopNode::onBtnClicked));

	return true;
}

void ShopNode::onBtnClicked(cocos2d::CCObject* pSender)
{
	CCMessageBox("clicked", "title");
}

bool ShopScene::init()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	setContentSize(winSize);

	m_layout = UiLayout::create("layout/shop_panel.xml");
	m_layout->setMenuTouchPriority(m_touchPriority);
	m_layout->setAnchorPoint(ccp(0.5f, 0.5f));
	m_layout->setPosition(ccpMult(winSize, 0.5f));
	addChild(m_layout);

	auto titlePanel = TitlePanel::create(m_touchPriority);
	addChild(titlePanel);

	initPanel();
	return true;
}

void ShopScene::initPanel()
{
	auto pos = m_layout->getChildById(3)->getPosition();
	ListSlideView *rankList = ListSlideView::create(ccp(350, 400));
	addChild(rankList);
	rankList->setAnchorPoint(ccp(0, 1));
	rankList->setPosition(pos);
	rankList->setSpacing(10);

	for (int i = 0; i < 10; ++i)
	{
		rankList->addNode(ShopNode::create());
	}
}
