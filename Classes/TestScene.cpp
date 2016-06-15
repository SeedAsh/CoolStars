#include "TestScene.h"
#include "UiLayout.h"
#include "MenuScene.h"
#include "ConfData.h"

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
	addClippingNode();
	return true;
}

void TestScene::layoutTest()
{
	auto layout = UiLayout::create("layout/default.xml");
	addChild(layout);

	CCMenuItemImage *item = dynamic_cast<CCMenuItemImage *>((layout->getChildById(3)));
	item->setTarget(this, menu_selector(TestScene::testCallback));

	auto label = dynamic_cast<CCLabelTTF *>((layout->getChildById(2)));
	label->setString("changed");

	auto spr = dynamic_cast<CCSprite *>((layout->getChildById(1)));
	spr->initWithFile("fish_title.png");
	//*/






	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"main_menu/zcd_anniu5.png",
		"main_menu/zcd_anniu5.png",
		this,
		menu_selector(TestScene::closeCallback));

	CCMenu *menu = CCMenu::create(pCloseItem, NULL);
	menu->setPosition(ccp(0, 0));
	addChild(menu);
	auto size = CCDirector::sharedDirector()->getWinSize();
	auto closeItemSize = pCloseItem->getContentSize();
	//menu->setPosition(size.width - closeItemSize.width  * 0.5f, size.height - closeItemSize.height  * 0.5f);

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

	///*
	
	
	///*
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	//auto spr = CCSprite::create("background/beij_di.png");

	auto spr = CCSprite::create("stage/stars/yxjm_fangkuai1.png");
	//spr->setPosition(ccpMult(winSize, 0.5f));
	spr->setPosition(ccpMult(winSize, 0.2f));
	addChild(spr);
	//*/
	

	CCLayerColor *aa = CCLayerColor::create(ccc4(255, 255, 255, 255));
	//size = CCSize(200, 200);
	aa->setContentSize(winSize);
	//addChild(aa);

	CCLayerColor *back = CCLayerColor::create(ccc4(255, 255, 255, 255));
	CCSize size = CCSize(200, 200);
	back->setContentSize(size);

	m_clippingNode = CCClippingNode::create();
	m_clippingNode->setInverted(false);
	m_clippingNode->setAlphaThreshold(1.0f);
	addChild(m_clippingNode);

	auto clound = CCSprite::create("test.png");
	clound->setPosition(ccp(200, 200));
	m_clippingNode->setStencil(back);

	auto board = CCSprite::create("shop/sd_di.png");
	board->setPosition(ccp(200, 200));
	m_clippingNode->addChild(board);


	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"main_menu/zcd_anniu5.png",
		"main_menu/zcd_anniu5.png",
		this,
		menu_selector(TestScene::testCallback));

	pCloseItem->setPosition(ccp(50, 50));
	CCMenu *menu = CCMenu::create(pCloseItem, NULL);
	menu->setPosition(ccp(0, 0));
	addChild(menu);
	//*/

}

void TestScene::closeCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, MenuScene::scene()));
}

void TestScene::testCallback(CCObject* pSender)
{
	auto spr = CCSprite::create("shop/sd_zuanshi4.png");
	m_clippingNode->addChild(spr);
	spr->setPosition(ccp(200, 200));

}


