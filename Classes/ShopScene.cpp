#include "ShopScene.h"
#include "UiLayout.h"
#include "MenuScene.h"
#include "TitlePanel.h"

USING_NS_CC;
using namespace std;

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

	m_layout = UiLayout::create("layout/shop.xml");
	addChild(m_layout);

	initPanel();
	return true;
}

void ShopScene::initPanel()
{
	/*
	CCMenuItem *leftPetBtn = dynamic_cast<CCMenuItem *>((m_layout->getChildById(6)));
	leftPetBtn->setTarget(this, menu_selector(ShopScene::onLeftPetBtnClicked));

	CCMenuItem *rightPetBtn = dynamic_cast<CCMenuItem *>((m_layout->getChildById(5)));
	rightPetBtn->setTarget(this, menu_selector(ShopScene::onRigthPetBtnClicked));

	CCMenuItem *upgradeBtn = dynamic_cast<CCMenuItem *>((m_layout->getChildById(8)));
	upgradeBtn->setTarget(this, menu_selector(ShopScene::onUpgradeBtnClicked));
	*/
}

void ShopScene::onLeftPetBtnClicked(cocos2d::CCObject* pSender)
{

}

void ShopScene::onRigthPetBtnClicked(cocos2d::CCObject* pSender)
{

}

void ShopScene::onUpgradeBtnClicked(cocos2d::CCObject* pSender)
{

}
