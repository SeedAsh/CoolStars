#include "ShopScene.h"
#include "UiLayout.h"
#include "MenuScene.h"
#include "TitlePanel.h"
#include "ListView.h"

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


CCScene* ShopScene::scene()
{
	CCScene *scene = CCScene::create();
	ShopScene *layer = ShopScene::create();
	scene->addChild(layer);
	return scene;
}

bool ShopScene::init()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();

	auto titlePanel = TitlePanel::create();
	addChild(titlePanel);

	m_layout = UiLayout::create("layout/shop_panel.xml");
	m_layout->setAnchorPoint(ccp(0.5f, 0.5f));
	m_layout->setPosition(ccpMult(winSize, 0.5f));
	addChild(m_layout);

	initPanel();
	return true;
}

void ShopScene::initPanel()
{
	auto pos = m_layout->getChildById(3)->getPosition();
	ListView *rankList = ListView::create(ccp(350, 400));
	addChild(rankList);
	rankList->setAnchorPoint(ccp(0, 1));
	rankList->setPosition(pos);
	rankList->setSpacing(10);

	for (int i = 0; i < 10; ++i)
	{
		rankList->addNode(ShopNode::create());
	}
}
