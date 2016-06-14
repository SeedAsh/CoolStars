#include "PackageScene.h"
#include "UiLayout.h"
#include "MenuScene.h"
#include "TitlePanel.h"

USING_NS_CC;
using namespace std;

CCScene* PackageScene::scene()
{
	CCScene *scene = CCScene::create();
	PackageScene *layer = PackageScene::create();
	scene->addChild(layer);
	return scene;
}

bool PackageScene::init()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();

	m_mainLayout = UiLayout::create("layout/pet_ui.xml");
	//addChild(m_mainLayout);

	auto titlePanel = TitlePanel::create();
	addChild(titlePanel);

	//initMainLayout();
	return true;
}

void PackageScene::initMainLayout()
{
	CCMenuItem *leftPetBtn = dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(6)));
	leftPetBtn->setTarget(this, menu_selector(PackageScene::onLeftPetBtnClicked));

	CCMenuItem *rightPetBtn = dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(5)));
	rightPetBtn->setTarget(this, menu_selector(PackageScene::onRigthPetBtnClicked));

	CCMenuItem *upgradeBtn = dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(8)));
	upgradeBtn->setTarget(this, menu_selector(PackageScene::onUpgradeBtnClicked));
}

void PackageScene::onLeftPetBtnClicked(cocos2d::CCObject* pSender)
{

}

void PackageScene::onRigthPetBtnClicked(cocos2d::CCObject* pSender)
{

}

void PackageScene::onUpgradeBtnClicked(cocos2d::CCObject* pSender)
{

}
