#include "StageUiLayer.h"
#include "VisibleRect.h"
#include "UserInfo.h"
#include "GameData.h"
#include "SoundMgr.h"
#include "MenuScene.h"
#include "PauseLayer.h"
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

#define Z_ORDER_PROPS_BG 0
#define Z_ORDER_PROPS (Z_ORDER_PROPS_BG + 1)
#define Z_ORDER_TITLE_BG (Z_ORDER_PROPS + 1)
#define Z_ORDER_TITLE (Z_ORDER_TITLE_BG + 1)
#define Z_ORDER_REWARD (Z_ORDER_TITLE + 1)
#define Z_ORDER_PAUSE (Z_ORDER_REWARD + 1)

#define SELECTED_SKILL_OFFSET 20
USING_NS_CC;
using namespace std;
StageUiLayer::StageUiLayer(void)
{
}

StageUiLayer::~StageUiLayer(void)
{
}

void StageUiLayer::onEnter()
{
	CCLayer::onEnter();
	StageModel::theModel()->addView(this);
	StageLayersMgr::theMgr()->addLayers(this);
}

void StageUiLayer::onExit()
{
	CCLayer::onExit();
	StageModel::theModel()->removeView(this);
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
	auto node = dynamic_cast<EmptyBox *>((m_topUi->getChildById(4)));
}

void StageUiLayer::initPets()
{
	int uiIds[] = { 10, 11, 12, 13};
	auto ids = PetManager::petMgr()->getCurPetIds();
	assert(ids.size() <= 4);
	for (size_t i = 0; i < ids.size(); ++i)
	{
		StagePetNode *petNode = StagePetNode::create(ids[i]);
		petNode->setSkillScanHandle(bind(&StageUiLayer::showPetsSkillPanel, this));
		auto node = dynamic_cast<EmptyBox *>((m_topUi->getChildById(uiIds[i])));
		node->setNode(petNode);
		node->setAnchorPoint(ccp(0.5f, 0.5f));
	}
}

void StageUiLayer::initBottomUi()
{
	auto closeBtn = dynamic_cast<CCMenuItem *>((m_bottomUi->getChildById(2)));
	closeBtn->setTarget(this, menu_selector(StageUiLayer::onPauseBtnClicked));

	auto reOrderBtn = dynamic_cast<CCMenuItem *>((m_bottomUi->getChildById(11)));
	reOrderBtn->setTarget(this, menu_selector(StageUiLayer::onReOrderBtnClicked));

	auto changeColorBtn = dynamic_cast<CCMenuItem *>((m_bottomUi->getChildById(10)));
	changeColorBtn->setTarget(this, menu_selector(StageUiLayer::onChangeColorBtnClicked));

	auto bombBtn = dynamic_cast<CCMenuItem *>((m_bottomUi->getChildById(9)));
	bombBtn->setTarget(this, menu_selector(StageUiLayer::onBombBtnClicked));
}

void StageUiLayer::showGameOverHint()
{
	//game over hint
	CCSprite *sp = CCSprite::create("stage_clear.png");
	this->addChild(sp);
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
	auto stageInfo = StageModel::theModel()->getStageInfo();
	int leftStep = stageInfo->getLeftSteps();
	//m_pStepLabel->setString(CommonUtil::intToStr(leftStep));


}

void StageUiLayer::onScoreChanged()
{
	auto stageInfo = StageModel::theModel()->getStageInfo();
	int curScore = stageInfo->getCurScore();
	//m_pScoreLabel->setString(CommonUtil::intToStr(curScore));
}

void StageUiLayer::onCoinsChanged()
{

}

void StageUiLayer::onGameOver(int isWon)
{
	CCNode *node = NULL;
	if (isWon)
	{
		node = GameWinLayer::create();
	}
	else
	{
		//GameFailLayer
		node = GameWinLayer::create();
	}
	
	addChild(node, kZorder_Dialog);
}

void StageUiLayer::onPauseBtnClicked(CCObject *pSender)
{
	//addChild(PauseLayer::create(), Z_ORDER_PAUSE);
	//CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, MenuScene::scene()));

}

void StageUiLayer::onReOrderBtnClicked(CCObject *pSender)
{
	StageOp->reOrderStars();
}

void StageUiLayer::onChangeColorBtnClicked(CCObject *pSender)
{
	auto *panel = ChangeStarColorPanel::create(kStageUiTouchPriority - 1);
	panel->setAnchorPoint(ccp(0.5f, 1));
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	panel->setPosition(ccpMult(winSize, 0.5f));

	addChild(panel);
}

void StageUiLayer::onBombBtnClicked(CCObject *pSender)
{

}