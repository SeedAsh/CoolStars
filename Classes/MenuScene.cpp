#include "MenuScene.h"
#include "UiLayout.h"
#include "StageModel.h"
#include "SoundMgr.h"
#include "StageScene.h"
#include "PetScene.h"
#include "RankingScene.h"
#include "PackageScene.h"
#include "ShopScene.h"
#include "BackgroundLayer.h"
#include "HelpPanel.h"
#include "CommonMacros.h"
#include "PreStageScene.h"

USING_NS_CC;
using namespace std;

CCScene *MenuScene::scene()
{
	CCScene *scene = CCScene::create();
	MenuScene *layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}

void MenuScene::onEnter()
{
	CCLayer::onEnter();
}

void MenuScene::onExit()
{
	CCLayer::onExit();
}

bool MenuScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	setContentSize(winSize);

	auto bk = BackgroundLayer::create();
	bk->setPosition(ccpMult(winSize, 0.5f));
	addChild(bk);

	m_mainLayout = UiLayout::create("layout/main_menu.xml");
	m_mainLayout->setAnchorPoint(ccp(0.5f, 0.5f));
	m_mainLayout->setPosition(ccpMult(winSize, 0.5f));
	m_mainLayout->setMenuTouchPriority(kMainMenuTouchPriority);
	addChild(m_mainLayout);

	m_bottomLayout = UiLayout::create("layout/main_menu_bottom.xml");
	m_bottomLayout->setAnchorPoint(ccp(0, 0));
	m_bottomLayout->setPosition(ccp(0, 0));
	m_bottomLayout->setMenuTouchPriority(kMainMenuTouchPriority);
	addChild(m_bottomLayout);

	initMainLayout();
	initBottomLayout();

	return true;
}

void MenuScene::initMainLayout()
{
	CCMenuItem * normalBtn= dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(6)));
	normalBtn->setTarget(this, menu_selector(MenuScene::toNormalGame));

	CCMenuItem *treasureBtn = dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(7)));
	treasureBtn->setTarget(this, menu_selector(MenuScene::toTreasureGame));

	CCMenuItem *drawLotteryBtn = dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(8)));
	drawLotteryBtn->setTarget(this, menu_selector(MenuScene::drawLottery));

	CCMenuItem *toPetBtn = dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(9)));
	toPetBtn->setTarget(this, menu_selector(MenuScene::toPetPanel));
}

void MenuScene::initBottomLayout()
{
	CCMenuItem *settingBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(1)));
	settingBtn->setTarget(this, menu_selector(MenuScene::toSetting));

	CCMenuItem *toMuteBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(2)));
	toMuteBtn->setTarget(this, menu_selector(MenuScene::toMute));

	CCMenuItem *toSoundBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(7)));
	toSoundBtn->setTarget(this, menu_selector(MenuScene::toSound));

	CCMenuItem *helpBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(3)));
	helpBtn->setTarget(this, menu_selector(MenuScene::toHelpPanel));
	
	CCMenuItem *rankBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(4)));
	rankBtn->setTarget(this, menu_selector(MenuScene::toRankPanel));

	CCMenuItem *packageBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(6)));
	packageBtn->setTarget(this, menu_selector(MenuScene::toPackagePanel));

	CCMenuItem *shopBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(5)));
	shopBtn->setTarget(this, menu_selector(MenuScene::toShopPanel));

	toSoundBtn->setVisible(false);
	m_settingBtnsHelper.addPopupNodes(toMuteBtn);
	m_settingBtnsHelper.addPopupNodes(helpBtn);
	m_settingBtnsHelper.init(settingBtn->getPosition());
}

void MenuScene::toNormalGame(CCObject* pSender)
{
	auto stageInfo = StageModel::theModel()->getStageInfo();
	stageInfo->newGame();
	SoundMgr::playEffect(SoundMgr::EFFECT_CLICK);
	CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(0.5f, PreStageScene::scene()));
}

void MenuScene::toTreasureGame(CCObject* pSender)
{
	CCMessageBox("toTreasureGame", "title");
}

void MenuScene::drawLottery(cocos2d::CCObject* pSender)
{
	CCMessageBox("drawLottery", "title");
}

void MenuScene::toPetPanel(cocos2d::CCObject* pSender)
{
	SoundMgr::playEffect(SoundMgr::EFFECT_CLICK);
	CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(0.5f, PetScene::scene()));
}

void MenuScene::toSetting(cocos2d::CCObject* pSender)
{
	m_settingBtnsHelper.toggle();
}

void MenuScene::toMute(cocos2d::CCObject* pSender)
{
	CCMenuItem *toMuteBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(2)));
	CCMenuItem *toSoundBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(7)));
	m_settingBtnsHelper.removePopupNodes(toMuteBtn);
	toMuteBtn->setVisible(false);
	m_settingBtnsHelper.addPopupNodes(toSoundBtn);
	toSoundBtn->setVisible(true);
}

void MenuScene::toSound(cocos2d::CCObject* pSender)
{
	CCMenuItem *toMuteBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(2)));
	CCMenuItem *toSoundBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(7)));
	m_settingBtnsHelper.removePopupNodes(toSoundBtn);
	toSoundBtn->setVisible(false);
	m_settingBtnsHelper.addPopupNodes(toMuteBtn);
	toMuteBtn->setVisible(true);
}

void MenuScene::toHelpPanel(cocos2d::CCObject* pSender)
{
	auto panel = HelpPanel::create();
	panel->setPosition(ccpMult(getContentSize(), 0.5f));
	addChild(panel);
}

void MenuScene::toRankPanel(cocos2d::CCObject* pSender)
{
	SoundMgr::playEffect(SoundMgr::EFFECT_CLICK);
	CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(0.5f, RankingScene::scene()));
}

void MenuScene::toPackagePanel(cocos2d::CCObject* pSender)
{
	SoundMgr::playEffect(SoundMgr::EFFECT_CLICK);
	CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(0.5f, PackageScene::scene()));
}

void MenuScene::toShopPanel(cocos2d::CCObject* pSender)
{
	SoundMgr::playEffect(SoundMgr::EFFECT_CLICK);
	CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(0.5f, ShopScene::scene()));
}
