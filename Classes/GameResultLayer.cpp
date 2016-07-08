#include "GameResultLayer.h"
#include "StageScene.h"
#include "MenuScene.h"
#include "StarsController.h"
#include "MainScene.h"
#include "UiLayout.h"
#include "StageDataMgr.h"
using namespace std;
USING_NS_CC;

bool GameWinLayer::init()
{
	setPanelId(kStageWinPanel);

	m_layout = UiLayout::create("layout/game_win.xml");
	initLayout();

	addChild(m_layout);
	setContentSize(m_layout->getContentSize());
	return true;
}

void GameWinLayer::initLayout()
{
	CCMenuItem *confirmBtn = dynamic_cast<CCMenuItem *>((m_layout->getChildById(26)));
	confirmBtn->setTarget(this, menu_selector(GameWinLayer::onConfirmBtnClicked));
}

void GameWinLayer::onConfirmBtnClicked(CCObject *pSender)
{
	MainScene::theScene()->showPanel(kMainMenu);

	return;
	auto info = StageDataMgr::theMgr();
	info->toNextStage();
	MainScene::theScene()->showPanel(kStageView);
}

///////////////////////////////////////////////////////////////////////////
bool GameFailLayer::init()
{
	setPanelId(kStageFailPanel);

	m_layout = UiLayout::create("layout/game_fail.xml");
	initLayout();

	addChild(m_layout);
	setContentSize(m_layout->getContentSize());
	return true;
}

void GameFailLayer::initLayout()
{
	CCMenuItem *buyPetBtn = dynamic_cast<CCMenuItem *>((m_layout->getChildById(19)));
	buyPetBtn->setTarget(this, menu_selector(GameFailLayer::onBuyPetBtnClicked));

	CCMenuItem *confirmBtn = dynamic_cast<CCMenuItem *>((m_layout->getChildById(18)));
	confirmBtn->setTarget(this, menu_selector(GameFailLayer::onConfirmBtnClicked));
}

void GameFailLayer::onConfirmBtnClicked(CCObject *pSender)
{
	MainScene::theScene()->showPanel(kMainMenu);
}

void GameFailLayer::onBuyPetBtnClicked(CCObject *pSender)
{

}
