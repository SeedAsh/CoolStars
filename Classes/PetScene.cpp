#include "PetScene.h"
#include "UiLayout.h"
#include "MenuScene.h"
#include "TitlePanel.h"

USING_NS_CC;
using namespace std;

bool PetScene::init()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	setContentSize(winSize);

	m_mainLayout = UiLayout::create("layout/pet_ui.xml");
	m_mainLayout->setMenuTouchPriority(m_touchPriority);
	addChild(m_mainLayout);

	m_bottomLayout = UiLayout::create("layout/pet_ui_bottom.xml");
	m_bottomLayout->setMenuTouchPriority(m_touchPriority);
	m_bottomLayout->setAnchorPoint(ccp(0, 0));
	m_bottomLayout->setPosition(ccp(0, 0));
	addChild(m_bottomLayout);
	
	auto titlePanel = TitlePanel::create(m_touchPriority);
	addChild(titlePanel);

	initMainLayout();
	initBottomLayout();
	return true;
}

void PetScene::initMainLayout()
{
	CCMenuItem *leftPetBtn = dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(6)));
	leftPetBtn->setTarget(this, menu_selector(PetScene::onLeftPetBtnClicked));

	CCMenuItem *rightPetBtn = dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(5)));
	rightPetBtn->setTarget(this, menu_selector(PetScene::onRigthPetBtnClicked));

	CCMenuItem *upgradeBtn = dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(8)));
	upgradeBtn->setTarget(this, menu_selector(PetScene::onUpgradeBtnClicked));
}

void PetScene::initBottomLayout()
{
	CCMenuItem *backHomeBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(1)));
	backHomeBtn->setTarget(this, menu_selector(PetScene::onBackHomeBtnClicked));

	CCMenuItem *greenPetBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(2)));
	greenPetBtn->setTarget(this, menu_selector(PetScene::onGreenPetBtnClicked));

	CCMenuItem *purplePetBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(6)));
	purplePetBtn->setTarget(this, menu_selector(PetScene::onPurplePetBtnClicked));

	CCMenuItem *redPetBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(5)));
	redPetBtn->setTarget(this, menu_selector(PetScene::onRedPetBtnClicked));

	CCMenuItem *bluePetBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(3)));
	bluePetBtn->setTarget(this, menu_selector(PetScene::onBluePetBtnClicked));

	CCMenuItem *yellowPetBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(4)));
	yellowPetBtn->setTarget(this, menu_selector(PetScene::onYellowPetBtnClicked));
}

void PetScene::onLeftPetBtnClicked(cocos2d::CCObject* pSender)
{

}

void PetScene::onRigthPetBtnClicked(cocos2d::CCObject* pSender)
{

}

void PetScene::onUpgradeBtnClicked(cocos2d::CCObject* pSender)
{

}

void PetScene::onBackHomeBtnClicked(cocos2d::CCObject* pSender)
{
	//CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, MenuScene::scene()));
}

void PetScene::onGreenPetBtnClicked(cocos2d::CCObject* pSender)
{

}

void PetScene::onPurplePetBtnClicked(cocos2d::CCObject* pSender)
{

}

void PetScene::onRedPetBtnClicked(cocos2d::CCObject* pSender)
{

}

void PetScene::onBluePetBtnClicked(cocos2d::CCObject* pSender)
{

}

void PetScene::onYellowPetBtnClicked(cocos2d::CCObject* pSender)
{

}

