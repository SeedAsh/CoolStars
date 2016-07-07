#include "ShopScene.h"
#include "UiLayout.h"
#include "MenuScene.h"
#include "TitlePanel.h"
#include "ListView.h"
#include "ListSlideView.h"
#include "DataManager.h"
#include "CommonUtil.h"
#include "CommonMacros.h"
#include "ShopManager.h"

USING_NS_CC;
using namespace std;
using namespace CommonUtil;

ShopNode *ShopNode::create(const ShopConfig &config)
{
	auto node = new ShopNode(config);
	node->init();
	node->autorelease();
	return node;
}

bool ShopNode::init()
{
	m_layout = UiLayout::create("layout/shop_node.xml");
	addChild(m_layout);
	setContentSize(m_layout->getContentSize());

	CCMenuItem *buyBtn = dynamic_cast<CCMenuItem *>((m_layout->getChildById(3)));
	buyBtn->setTarget(this, menu_selector(ShopNode::onBtnClicked));

	CCSprite *icon = dynamic_cast<CCSprite *>(m_layout->getChildById(2));
	icon->initWithFile(m_config.iconPath.c_str());

	CCLabelAtlas * diamond = dynamic_cast<CCLabelAtlas *>(m_layout->getChildById(6));
	diamond->setString(intToStr(m_config.diamond));

	CCLabelAtlas *cost = dynamic_cast<CCLabelAtlas *>(m_layout->getChildById(7));
	cost->setString(intToStr(m_config.cost));

	return true;
}

void ShopNode::onBtnClicked(cocos2d::CCObject* pSender)
{
	ShopManager::theMgr()->purchase(m_config.id);
}

bool ShopScene::init()
{
	setPanelId(kShopPanel);

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
	ListSlideView *shopList = ListSlideView::create(ccp(350, 500));
	addChild(shopList);
	shopList->setAnchorPoint(ccp(0, 1));
	shopList->setPosition(pos);
	shopList->setSpacing(5);

	auto configs = DataManagerSelf->getShopConfigs();
	sort(configs.begin(), configs.end(), [=](ShopConfig config1, ShopConfig config2)->bool
	{
		return config1.diamond > config2.diamond;
	});
	for (size_t i = 0; i < configs.size(); ++i)
	{
		shopList->addNode(ShopNode::create(configs[i]));
	}
}
