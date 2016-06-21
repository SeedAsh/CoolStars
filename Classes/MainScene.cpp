#include "MainScene.h"
#include "BackgroundLayer.h"
#include "TitlePanel.h"
#include "BasePanel.h"
#include "CommonMacros.h"
#include "MenuScene.h"

USING_NS_CC;
using namespace std;

CCScene *MainScene::s_scene = NULL;

bool MainScene::init()
{
	CCScene::init();

	auto winSize = CCDirector::sharedDirector()->getWinSize();
	auto bk = BackgroundLayer::create();
	bk->setPosition(ccpMult(winSize, 0.5f));
	addChild(bk);

	auto titlePanel = TitlePanel::create();
	addChild(titlePanel);

	showPanel(kMainMenu);
	return true;
}

CCScene* MainScene::theScene()
{
	if (!s_scene)
	{
		s_scene = MainScene::create();
		s_scene->init();
		s_scene->autorelease();
	}
	return s_scene;
}

void MainScene::addUiPanel(BasePanel *panel)
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	if (panel != NULL)
	{
		panel->setAnchorPoint(ccp(0.5f, 0.5f));
		panel->setPosition(ccpMult(winSize, 0.5f));
		addChild(panel);
	}
}

void MainScene::showPanel(int panelId)
{
	BasePanel *panel = NULL;
	switch (panelId)
	{
	case kMainMenu:
		panel = MenuScene::create();
		break;
	case kPetPanel:
		panel = MenuScene::create();
		break;
	case kShopPanel:
		panel = MenuScene::create();
		break;
	case kLotteryPanel:
		panel = MenuScene::create();
		break;
	case kRankingPanel:
		panel = MenuScene::create();
		break;
	case kPackagePanel:
		panel = MenuScene::create();
		break;
	case kPreStagePanel:
		panel = MenuScene::create();
		break;
	case kStageView:
		panel = MenuScene::create();
		break;
	default:
		assert(false && "no this panelId");
		break;
	}

	addUiPanel(panel);
}

void MainScene::backPanel()
{

}