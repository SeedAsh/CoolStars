#include "MenuScene.h"
#include "UiLayout.h"
#include "StageModel.h"
#include "SoundMgr.h"
#include "StageScene.h"
#include "PetScene.h"
#include "RankingScene.h"
#include "PackageScene.h"
#include "ShopScene.h"
#include "HelpPanel.h"
#include "CommonMacros.h"
#include "PreStageScene.h"
#include "LotteryScene.h"
#include "MainScene.h"
#include "RankingPanelUtil.h"
#include "GuideMacros.h"
#include "GuideMgr.h"
#include "RankingModel.h"

USING_NS_CC;
using namespace std;

bool MenuScene::init()
{
	setPanelId(kMainMenu);
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	setContentSize(winSize);

	m_mainLayout = UiLayout::create("layout/main_menu.xml");
	m_mainLayout->setAnchorPoint(ccp(0.5f, 0.5f));
	m_mainLayout->setPosition(ccpMult(winSize, 0.5f));
	m_mainLayout->setMenuTouchPriority(m_touchPriority);
	addChild(m_mainLayout);

	m_bottomLayout = UiLayout::create("layout/main_menu_bottom.xml");
	m_bottomLayout->setAnchorPoint(ccp(0, 0));
	m_bottomLayout->setPosition(ccp(0, 0));
	m_bottomLayout->setMenuTouchPriority(m_touchPriority);
	addChild(m_bottomLayout);

	initMainLayout();
	initBottomLayout();

	GuideMgr::theMgr()->startGuide(kGuideStart_mainMenu_in, bind(&MenuScene::justShowNormalGameBtn, this));
	GuideMgr::theMgr()->endGuide(kGuideEnd_mainMenu_in);

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

	CCMenuItem *packageBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(5)));
	packageBtn->setTarget(this, menu_selector(MenuScene::toPackagePanel));

	CCMenuItem *shopBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(6)));
	shopBtn->setTarget(this, menu_selector(MenuScene::toShopPanel));

	toSoundBtn->setVisible(false);
	m_settingBtnsHelper.addPopupNodes(toMuteBtn);
	m_settingBtnsHelper.addPopupNodes(helpBtn);
	m_settingBtnsHelper.init(settingBtn->getPosition());
}

void MenuScene::toNormalGame(CCObject* pSender)
{
	SoundMgr::playEffect(SoundMgr::EFFECT_CLICK);
	StageModel::theModel()->resetStage(kNormalType);
	MainScene::theScene()->showPanel(kPreStagePanel);
}

void MenuScene::toTreasureGame(CCObject* pSender)
{
	SoundMgr::playEffect(SoundMgr::EFFECT_CLICK);
	StageModel::theModel()->resetStage(kTreasureType);
	MainScene::theScene()->showPanel(kPreStagePanel);;
}

void MenuScene::drawLottery(cocos2d::CCObject* pSender)
{
	SoundMgr::playEffect(SoundMgr::EFFECT_CLICK);
	MainScene::theScene()->showPanel(kLotteryPanel);
}

void MenuScene::toPetPanel(cocos2d::CCObject* pSender)
{
	SoundMgr::playEffect(SoundMgr::EFFECT_CLICK);
	MainScene::theScene()->showPanel(kPetPanel);
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
	MainScene::theScene()->showDialog(panel);
}

void MenuScene::toRankPanel(cocos2d::CCObject* pSender)
{
	SoundMgr::playEffect(SoundMgr::EFFECT_CLICK);

	if (RankingModel::theModel()->alreadyOpenRanking())
	{
		MainScene::theScene()->showPanel(kRankingPanel);
	}
	else
	{
		auto panel = RankingNameInputPanel::create();
		MainScene::theScene()->showDialog(panel);
	}
}

void MenuScene::toPackagePanel(cocos2d::CCObject* pSender)
{
	SoundMgr::playEffect(SoundMgr::EFFECT_CLICK);
	MainScene::theScene()->showPanel(kPackagePanel);
}

void MenuScene::toShopPanel(cocos2d::CCObject* pSender)
{
	SoundMgr::playEffect(SoundMgr::EFFECT_CLICK);
	MainScene::theScene()->showPanel(kShopPanel);
}

void MenuScene::justShowNormalGameBtn()
{
	m_bottomLayout->setVisible(false);
	m_mainLayout->getChildById(7)->setVisible(false);
	m_mainLayout->getChildById(8)->setVisible(false);
	m_mainLayout->getChildById(9)->setVisible(false);
}
