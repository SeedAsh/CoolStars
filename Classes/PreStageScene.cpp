#include "PreStageScene.h"
#include "UiLayout.h"
#include "TitlePanel.h"
#include "SoundMgr.h"
#include "StageScene.h"
USING_NS_CC;
using namespace std;

cocos2d::CCScene* PreStageScene::scene()
{
	CCScene *scene = CCScene::create();
	PreStageScene *layer = PreStageScene::create();
	scene->addChild(layer);
	return scene;
}

bool PreStageScene::init()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();

	TitlePanel * titilPanel = TitlePanel::create();
	addChild(titilPanel);

	m_mainLayout = UiLayout::create("layout/pre_stage.xml");
	m_mainLayout->setAnchorPoint(ccp(0.5f, 0.5f));
	m_mainLayout->setPosition(ccpMult(winSize, 0.5f));
	addChild(m_mainLayout);

	m_bottomLayout = UiLayout::create("layout/pre_stage_bottom.xml");
	addChild(m_bottomLayout);

	initMainLayout();
	initBottomLayout();
	return true;
}

void PreStageScene::initMainLayout()
{
	
}

void PreStageScene::initBottomLayout()
{
	CCMenuItem *startGameBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(1)));
	startGameBtn->setTarget(this, menu_selector(PreStageScene::toStartGame));
}

void PreStageScene::toStartGame(cocos2d::CCObject* pSender)
{
	SoundMgr::playEffect(SoundMgr::EFFECT_CLICK);
	CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(0.5f, StageScene::scene()));
}
