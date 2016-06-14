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

	m_mainLayout = UiLayout::create("layout/pet_ui.xml");
	addChild(m_mainLayout);

	auto titlePanel = TitlePanel::create();
	addChild(titlePanel);

	initMainLayout();
	return true;
}

void ShopScene::initMainLayout()
{
	CCMenuItem *leftPetBtn = dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(6)));
	leftPetBtn->setTarget(this, menu_selector(ShopScene::onLeftPetBtnClicked));

	CCMenuItem *rightPetBtn = dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(5)));
	rightPetBtn->setTarget(this, menu_selector(ShopScene::onRigthPetBtnClicked));

	CCMenuItem *upgradeBtn = dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(8)));
	upgradeBtn->setTarget(this, menu_selector(ShopScene::onUpgradeBtnClicked));
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
