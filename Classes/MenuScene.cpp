#include "MenuScene.h"
#include "UiLayout.h"
#include "StageModel.h"
#include "SoundMgr.h"
#include "StageScene.h"
#include "PetScene.h"
#include "RankingScene.h"
#include "PackageScene.h"
#include "ShopScene.h"

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

	m_mainLayout = UiLayout::create("layout/main_menu.xml");
	addChild(m_mainLayout);

	m_bottomLayout = UiLayout::create("layout/main_menu_bottom.xml");
	m_bottomLayout->setAnchorPoint(ccp(0, 0));
	m_bottomLayout->setPosition(ccp(0, 0));
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

	CCMenuItem *muteBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(2)));
	muteBtn->setTarget(this, menu_selector(MenuScene::toMute));

	CCMenuItem *helpBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(3)));
	helpBtn->setTarget(this, menu_selector(MenuScene::toHelpPanel));
	
	CCMenuItem *rankBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(4)));
	rankBtn->setTarget(this, menu_selector(MenuScene::toRankPanel));

	CCMenuItem *packageBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(6)));
	packageBtn->setTarget(this, menu_selector(MenuScene::toPackagePanel));

	CCMenuItem *shopBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(5)));
	shopBtn->setTarget(this, menu_selector(MenuScene::toShopPanel));
}

void MenuScene::toNormalGame(CCObject* pSender)
{
	auto stageInfo = StageModel::theModel()->getStageInfo();
	stageInfo->newGame();
	SoundMgr::playEffect(SoundMgr::EFFECT_CLICK);
	CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(0.5f, StageScene::scene()));
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
	CCMessageBox("toSetting", "title");

}

void MenuScene::toMute(cocos2d::CCObject* pSender)
{
	CCMessageBox("toMute", "title");

}

void MenuScene::toHelpPanel(cocos2d::CCObject* pSender)
{
	CCMessageBox("toHelpPanel", "title");

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
