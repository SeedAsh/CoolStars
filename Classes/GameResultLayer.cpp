#include "GameResultLayer.h"
#include "StageScene.h"
#include "MenuScene.h"
#include "StageModel.h"
using namespace std;
USING_NS_CC;

bool GameWinLayer::init()
{
	auto bg = CCSprite::create("stage/game_over/game_win.png");
	CCSize size = bg->getContentSize();
	setContentSize(size);
	bg->setPosition(ccp(size.width * 0.5f, size.height * 0.5f));
	initDialog();
	addChild(bg);

	CCMenuItemImage *pToMainMenu = CCMenuItemImage::create(
		"common/back_home.png",
		"common/back_home.png",
		this,
		menu_selector(GameWinLayer::toMainMenu));
	pToMainMenu->setPosition(size.width * 0.5f, size.height * 0.1f);

	/*
	CCMenuItemImage *pToNextStage = CCMenuItemImage::create(
		"btn_nextStage.png",
		"btn_nextStage.png",
		this,
		menu_selector(GameWinLayer::toNextStage));
	pToNextStage->setPosition(size.width * 0.75f, size.height * 0.1f);

	

	auto info = StageModel::theModel()->getStageInfo();
	bool isLastStage = info->isTheLastStage();
	if (!isLastStage)
	{
		pToMainMenu->setPosition(size.width * 0.25f, size.height * 0.1f);
		menu->addChild(pToNextStage);
	}
	*/
	CCMenu *menu = CCMenu::create();
	menu->addChild(pToMainMenu);
	menu->setPosition(ccp(0, 0));

	addChild(menu);

	
	return true;
}

void GameWinLayer::toNextStage(CCObject *pSender)
{
	auto info = StageModel::theModel()->getStageInfo();
	info->toNextStage();
	CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(0.5f, StageScene::scene()));
}

void GameWinLayer::toMainMenu(CCObject *pSender)
{
	//CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(0.5f, MenuScene::scene()));
}


///////////////////////////////////////////////////////////////////////////
bool GameFailLayer::init()
{
	auto bg = CCSprite::create("game_fail.png");
	CCSize size = bg->getContentSize();
	setContentSize(size);
	bg->setPosition(ccp(size.width * 0.5f, size.height * 0.5f));
	initDialog();
	addChild(bg);

	CCMenuItemImage *pToMainMenu = CCMenuItemImage::create(
		"btn_mainMenu.png",
		"btn_mainMenu.png",
		this,
		menu_selector(GameFailLayer::toMainMenu));
	pToMainMenu->setPosition(size.width * 0.25f, size.height * 0.1f);

	CCMenuItemImage *pReplay = CCMenuItemImage::create(
		"btn_rePlayer.png",
		"btn_rePlayer.png",
		this,
		menu_selector(GameFailLayer::replay));
	pReplay->setPosition(size.width * 0.75f, size.height * 0.1f);

	CCMenu *menu = CCMenu::create();
	menu->addChild(pToMainMenu);
	menu->addChild(pReplay);
	menu->setPosition(ccp(0, 0));

	addChild(menu);

	return true;
}

void GameFailLayer::replay(CCObject *pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(0.5f, StageScene::scene()));
}

void GameFailLayer::toMainMenu(CCObject *pSender)
{
	//CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(0.5f, MenuScene::scene()));
}