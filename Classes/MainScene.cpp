#include "MainScene.h"
#include "BackgroundLayer.h"
#include "TitlePanel.h"
#include "BasePanel.h"
#include "CommonMacros.h"
#include "MenuScene.h"
#include "PetScene.h"
#include "ShopScene.h"
#include "LotteryScene.h"
#include "RankingScene.h"
#include "PackageScene.h"
#include "PreStageScene.h"
#include "StageScene.h"
#include "ScaleDialog.h"

USING_NS_CC;
using namespace std;

MainScene *MainScene::s_scene = NULL;

bool MainScene::init()
{
	CCScene::init();

	m_bkLayer = CCNode::create();
	m_uiLayer = CCNode::create();
	m_dialogLayer = CCNode::create();
	addChild(m_bkLayer);
	addChild(m_uiLayer);
	addChild(m_dialogLayer);

	auto winSize = CCDirector::sharedDirector()->getWinSize();
	auto bk = BackgroundLayer::create();
	bk->setPosition(ccpMult(winSize, 0.5f));
	m_bkLayer->addChild(bk);
	
	showPanel(kMainMenu);
	return true;
}

MainScene* MainScene::theScene()
{
	if (!s_scene)
	{
		s_scene = new MainScene;
		s_scene->init();
		s_scene->autorelease();
	}
	return s_scene;
}

void MainScene::addUiPanel(BasePanel *panel, bool closeBehind)
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	if (panel != NULL)
	{
		if (closeBehind)
		{
			m_uiLayer->removeAllChildrenWithCleanup(true);
		}

		panel->setAnchorPoint(ccp(0.5f, 0.5f));
		panel->setPosition(ccpMult(winSize, 0.5f));
		m_uiLayer->addChild(panel);
	}
}

void MainScene::showPanel(int panelId, bool closeBehind)
{
	BasePanel *panel = NULL;
	switch (panelId)
	{
	case kMainMenu:
		panel = MenuScene::create();
		break;
	case kPetPanel:
		panel = PetScene::create();
		break;
	case kShopPanel:
		panel = ShopScene::create();
		break;
	case kLotteryPanel:
		panel = LotteryScene::create();
		break;
	case kRankingPanel:
		panel = RankingScene::create();
		break;
	case kPackagePanel:
		panel = PackageScene::create();
		break;
	case kPreStagePanel:
		panel = PreStageScene::create();
		break;
	case kStageView:
		panel = StageScene::create();
		break;
	default:
		assert(false && "no this panelId");
		break;
	}

	addUiPanel(panel, closeBehind);
}

void MainScene::addDialog(ScaleDialog *dialog)
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	dialog->setAnchorPoint(ccp(0.5f, 0.5f));
	dialog->setPosition(ccpMult(winSize, 0.5f));
	m_dialogLayer->addChild(dialog);
}

void MainScene::backPanel()
{

}