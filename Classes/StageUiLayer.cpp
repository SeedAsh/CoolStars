﻿#include "StageUiLayer.h"
#include "VisibleRect.h"
#include "UserInfo.h"
#include "GameData.h"
#include "SoundMgr.h"
#include "MenuScene.h"
#include "PauseDialog.h"
#include "PetManager.h"
#include "StageOperator.h"
#include "CommonUtil.h"
#include "GameResultLayer.h"
#include "PropManager.h"
#include "PropItemView.h"
#include "UiLayout.h"
#include "EmptyBox.h"
#include "StagePetNode.h"
#include "StagePanelUtil.h"
#include "MainScene.h"
#include "StageSceneState.h"
#include "StageTarget.h"
#include "StageTargetView.h"
#include "CommonMacros.h"
#include "StageDataMgr.h"

#define Z_ORDER_PROPS_BG 0
#define Z_ORDER_PROPS (Z_ORDER_PROPS_BG + 1)
#define Z_ORDER_TITLE_BG (Z_ORDER_PROPS + 1)
#define Z_ORDER_TITLE (Z_ORDER_TITLE_BG + 1)
#define Z_ORDER_REWARD (Z_ORDER_TITLE + 1)
#define Z_ORDER_PAUSE (Z_ORDER_REWARD + 1)

#define SELECTED_SKILL_OFFSET 20
USING_NS_CC;
using namespace std;
using namespace CommonUtil;
StageUiLayer::StageUiLayer(StageStateOwner *stateOwner)
: m_stateOwner(stateOwner)
{
}

StageUiLayer::~StageUiLayer(void)
{
}

StageUiLayer *StageUiLayer::create(StageStateOwner *stateOwner)
{
	StageUiLayer* layer = new StageUiLayer(stateOwner);
	layer->init();
	layer->autorelease();
	return layer;
}

void StageUiLayer::onEnter()
{
	CCLayer::onEnter();
	StageDataMgr::theMgr()->addView(this);
	StarsController::theModel()->addView(this);
	StageLayersMgr::theMgr()->addLayers(this);
}

void StageUiLayer::onExit()
{
	CCLayer::onExit();
	StageDataMgr::theMgr()->removeView(this);
	StarsController::theModel()->removeView(this);
	StageLayersMgr::theMgr()->removeLayers(this);
}

bool StageUiLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	auto winSize = CCDirector::sharedDirector()->getWinSize();

	m_bottomUi = UiLayout::create("layout/stage_bottom.xml");
	m_bottomUi->setAnchorPoint(ccp(0, 0));
	m_bottomUi->setPosition(ccp(0, 0));
	m_bottomUi->setMenuTouchPriority(kStageUiTouchPriority);
	addChild(m_bottomUi);

	m_topUi = UiLayout::create("layout/stage_top.xml");
	m_topUi->setAnchorPoint(ccp(0, 1));
	m_topUi->setPosition(ccp(0, winSize.height));
	m_topUi->setMenuTouchPriority(kStageUiTouchPriority);
	addChild(m_topUi);


	initTopUi();
	initPets();
	initBottomUi();

    return true;
}

void StageUiLayer::initTopUi()
{
	int targetBoxIds[] = { 18, 19, 20 };
	auto target = StarsController::theModel()->getStageTarget();
	auto leftTarget = target->getEraseStarsLeft();
	assert(leftTarget.size() <= 3);
	for (size_t i = 0; i < leftTarget.size(); ++i)
	{
		StageTargetView *view = StageTargetView::create(leftTarget[i]);
		auto node = dynamic_cast<EmptyBox *>((m_topUi->getChildById(targetBoxIds[i])));
		node->setNode(view);
	}
	
	onStepsChanged();
	onScoreChanged();
}

void StageUiLayer::initPets()
{
	int uiIds[] = { 10, 11, 12, 13};
	auto ids = PetManager::petMgr()->getCurPetIds();
	assert(ids.size() <= 4);
	for (size_t i = 0; i < ids.size(); ++i)
	{
		StagePetNode *petNode = StagePetNode::create(ids[i], kStageUiTouchPriority);
		petNode->setTouchHandle(bind(&StageUiLayer::handlePetClicked, this, placeholders::_1));
		auto node = dynamic_cast<EmptyBox *>((m_topUi->getChildById(uiIds[i])));
		node->setNode(petNode);
		node->setAnchorPoint(ccp(0.5f, 0.5f));
	}
}

void StageUiLayer::initBottomUi()
{
	auto closeBtn = dynamic_cast<CCMenuItem *>((m_bottomUi->getChildById(2)));
	closeBtn->setTarget(this, menu_selector(StageUiLayer::onPauseBtnClicked));

	for (int i = kPropReorder; i < kPorpTypeAmount; i++)
	{
		auto box = dynamic_cast<EmptyBox *>((m_bottomUi->getChildById(12 + i)));
		auto node = PropItemView::create(i, kStageUiTouchPriority);
		node->setTouchHandle(bind(&StageUiLayer::handlePropsItemClicked, this, placeholders::_1));
		node->setAnchorPoint(ccp(0.5f, 0.5f));
		box->setNode(node);
	}
}

void StageUiLayer::showGameOverHint()
{
	//game over hint
	CCSprite *sp = CCSprite::create("stage_clear.png");
	this->addChild(sp);
}

void StageUiLayer::handlePetClicked(int petId)
{
	m_stateOwner->clickPet(petId);
}

void StageUiLayer::showPetsSkillPanel()
{
	StagePetSkillPanel *panel = StagePetSkillPanel::create(kStageUiTouchPriority - 1);
	auto node = dynamic_cast<EmptyBox *>((m_topUi->getChildById(14)));
	node->setNode(panel);
	node->setAnchorPoint(ccp(0, 1));
}

void StageUiLayer::deliveryScore( const CCPoint &from, int totalScore, int count ){

	/*
    int delay = 0;
    int delta = totalScore / count;
    char *label = new char[16];
    CCLabelTTF *pScore = NULL;
    CCPoint to = m_pScoreLabel->getPosition();
    for (int i = 0; i < count; i++){
        sprintf(label, "%d", delta);
        pScore = CCLabelTTF::create(label,  "Arial", 21);
        pScore->setPosition(from);
		pScore->setColor(ccWHITE);
        addChild(pScore, 2);
        pScore->runAction(CCSequence::create(
            CCDelayTime::create(0.1 * delay),
            CCMoveTo::create(0.5f, to),
            CCCallFuncN::create(this, callfuncN_selector(StageUiLayer::removeChild)),
            NULL));
        delay++;
    }
	*/
}

void StageUiLayer::menuCallback( CCObject *pSender )
{

}

void StageUiLayer::onStepsChanged()
{
	auto stageInfo = StageDataMgr::theMgr();
	int leftStep = stageInfo->getLeftSteps();
	CCLabelAtlas *stepLabel = dynamic_cast<CCLabelAtlas *>(m_topUi->getChildById(17));
	stepLabel->setString(intToStr(leftStep));
}

void StageUiLayer::onScoreChanged()
{
	auto stageInfo = StageDataMgr::theMgr();
	int curScore = stageInfo->getCurScore();
	auto stageTarget = StarsController::theModel()->getStageTarget();
	int targetScore = stageTarget->getTargetScore();

	CCLabelAtlas * curScoreLabel = dynamic_cast<CCLabelAtlas *>(m_topUi->getChildById(15));
	string str = intToStr(curScore);
	str += ";";
	str += intToStr(targetScore);
	
	curScoreLabel->setString(str.c_str());
}

void StageUiLayer::onCoinsChanged()
{

}

void StageUiLayer::onGameOver(int isWon)
{
	CCNode *node = NULL;
	if (isWon)
	{
		MainScene::theScene()->showPanel(kStageWinPanel);
	}
	else
	{
		MainScene::theScene()->showPanel(kStageFailPanel);

	}
	
}

void StageUiLayer::onPauseBtnClicked(CCObject *pSender)
{
	MainScene::theScene()->showDialog(PauseDialog::create());
}

void StageUiLayer::showChangeColorPanel(const LogicGrid &grid)
{
	auto *panel = ChangeStarColorPanel::create(kStageUiTouchPriority - 1);
	panel->setCallback([=](int color)
	{
		PropManager::propMgr()->usePropBrush(grid, color);
		m_stateOwner->enterNormalState();
	});

	panel->setAnchorPoint(ccp(0.5f, 1));
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	panel->setPosition(ccpMult(winSize, 0.5f));

	addChild(panel);
}

void StageUiLayer::handlePropsItemClicked(int type)
{
	if (type == kPropReorder)
	{
		PropManager::propMgr()->usePropReorder();
	}
	else
	{
		m_stateOwner->enterPropsClickState(type);
	}
}