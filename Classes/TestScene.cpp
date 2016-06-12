#include "TestScene.h"
#include "UiLayout.h"
#include "MenuScene.h"

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
	
	auto layout = UiLayout::create("layout/default.xml");
	addChild(layout);
	
	CCMenuItemImage *item = dynamic_cast<CCMenuItemImage *>((layout->getChildById(3)));
	item->setTarget(this, menu_selector(TestScene::testCallback));

	auto label = dynamic_cast<CCLabelTTF *>((layout->getChildById(2)));
	label->setString("changed");

	auto spr = dynamic_cast<CCSprite *>((layout->getChildById(1)));
	spr->initWithFile("fish_title.png");






	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"loginCancel.png",
		"loginCancel.png",
		this,
		menu_selector(TestScene::closeCallback));

	CCMenu *menu = CCMenu::create(pCloseItem, NULL);
	addChild(menu);
	auto size = CCDirector::sharedDirector()->getWinSize();
	auto closeItemSize = pCloseItem->getContentSize();
	menu->setPosition(size.width - closeItemSize.width  * 0.5f, size.height - closeItemSize.height  * 0.5f);

	return true;
}

void TestScene::closeCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, MenuScene::scene()));
}

void TestScene::testCallback(CCObject* pSender)
{
	CCMessageBox("haha", "haha");
}


