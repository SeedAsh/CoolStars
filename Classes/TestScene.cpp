#include "TestScene.h"
#include "UiLayout.h"
#include "MenuScene.h"
#include "ConfData.h"
#include "ListView.h"
#include "ListPetView.h"

USING_NS_CC;

CCScene* TestScene::scene()
{
	CCScene *scene = CCScene::create();
	TestScene *layer = TestScene::create();
	scene->addChild(layer);
	return scene;
}

bool TestScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	initPanel();
	test();
	return true;
}

void TestScene::test()
{
	/*
	m_spr = CCSprite::create("shop/sd_goumai.png");
	addChild(m_spr);
	m_spr->setPosition(ccp(200, 200));
	return;
	*/
	auto size = CCSize(350, 500);
	ListPetView *listView = ListPetView::create(CCSize(350, 500));
	addChild(listView);
	listView->setPosition(ccp(30, 100));
	listView->setSpacing(20);

	for (int i = 0; i < 30; i++)
	{
		CCSprite *spr = CCSprite::create("shop/sd_di2.png");
		spr->ignoreAnchorPointForPosition(false);
		spr->setAnchorPoint(ccp(0, 0));
		listView->addNode(spr);
		
		char str[100] = { 0 };
		sprintf(str, "%d", i + 1);
		CCLabelTTF *label = CCLabelTTF::create(str, "Arial", 24);
		label->setPosition(ccp(50, 50));
		spr->addChild(label);
		
	}
	listView->setCurItem(29);
}

void TestScene::initPanel()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"main_menu/zcd_anniu5.png",
		"main_menu/zcd_anniu5.png",
		this,
		menu_selector(TestScene::testCallback));

	pCloseItem->setPosition(ccp(50, 50));
	CCMenu *menu = CCMenu::create(pCloseItem, NULL);
	menu->setPosition(ccp(0, 0));
	addChild(menu);
}

void TestScene::addClippingNode()
{
	/*
	CCLayerColor *back = CCLayerColor::create(ccc4(125, 0, 0, 255));
	CCSize size = CCSize(ccp(200, 200));
	back->setContentSize(size);
	//addChild(back);

	m_clippingNode = CCClippingNode::create();
	m_clippingNode->setInverted(false);
	m_clippingNode->setAlphaThreshold(0.0f);

	CCSprite *sp = CCSprite::create("shop/sd_zuanshi2.png");
	sp->setAnchorPoint(ccp(0, 0));
	m_clippingNode->setStencil(back);
	addChild(m_clippingNode);

	auto spr = CCSprite::create("shop/sd_di.png");
	//spr->ignoreAnchorPointForPosition(true);
	spr->setAnchorPoint(ccp(0, 0));
	m_clippingNode->addChild(spr);

	*/
}

void TestScene::closeCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, MenuScene::scene()));
}

void TestScene::testCallback(CCObject* pSender)
{
	m_spr->stopAllActions();
	m_spr->runAction(CCEaseExponentialOut::create(CCMoveTo::create(1.0f, ccp(200, 600))));
	//m_spr->runAction(CCMoveTo::create(0.5, ccp(300, 200)));
}


