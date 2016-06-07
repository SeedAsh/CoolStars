﻿#include "StageUiLayer.h"
#include "VisibleRect.h"
#include "UserInfo.h"
#include "GameData.h"
#include "SoundMgr.h"
#include "MenuScene.h"
#include "PauseLayer.h"
#include "PetManager.h"
#include "PetView.h"
#include "StageOperator.h"
#include "CommonUtil.h"
#include "GameResultLayer.h"

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
      :m_pScoreLabel(NULL),
	  m_pStepLabel(NULL),
      m_pScoreHint(NULL),
	  m_pBombLabel(NULL),
	  m_pPaintLabel(NULL),
	  m_pReflashLabel(NULL)
{
}

StageUiLayer::~StageUiLayer(void)
{
}

void StageUiLayer::onEnter()
{
	CCLayer::onEnter();
	StageModel::theModel()->addView(this);
}

void StageUiLayer::onExit()
{
	CCLayer::onExit();
	StageModel::theModel()->removeView(this);
}

StageUiLayer * StageUiLayer::create(){
    StageUiLayer *pRet = new StageUiLayer();
    if (pRet && pRet->init()){
        pRet->autorelease();
        return pRet;
    }else{
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool StageUiLayer::init(){
	if (!CCLayer::init()){
		return false;
	}

	this->setTouchEnabled(true);

	initTopUi();
	initPets();
	initBottomUi();

    return true;
}


void StageUiLayer::initTopUi()
{
	auto stageInfo = StageModel::theModel()->getStageInfo();
	char str[100] = { 0 };
	CCPoint top = VisibleRect::top();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//hight score
	CCDictionary *text = CCDictionary::createWithContentsOfFile(XML_DATA);
	CCString *msg = (CCString*)text->objectForKey("hight");
	CCLabelTTF* hightScore = CCLabelTTF::create(msg->getCString(), "Arial", 21);
	hightScore->setColor(ccWHITE);
	CCSize size = hightScore->getContentSize();
	hightScore->setPosition(ccp(visibleSize.width * 0.6f, visibleSize.height - size.height));
	this->addChild(hightScore, Z_ORDER_TITLE);

	sprintf(str, "%d", UserInfo::getBestScore());
	CCLabelTTF* bestSocre = CCLabelTTF::create(str, "Arial", 21);
	bestSocre->setColor(ccWHITE);
	bestSocre->setPosition(ccp(hightScore->getPositionX() + size.width / 2 + bestSocre->getContentSize().width,
		hightScore->getPositionY()));
	this->addChild(bestSocre, Z_ORDER_TITLE);
	bestSocre->setString(CommonUtil::intToStr(stageInfo->getTopScore()));

	//stage num
	msg = (CCString*)text->objectForKey("lev");
	CCLabelTTF* pStage = CCLabelTTF::create(msg->getCString(), "Arial", 21);
	pStage->setColor(ccWHITE);
	size = pStage->getContentSize();
	pStage->setPosition(ccp(size.width / 2 + 10, hightScore->getPositionY() - hightScore->getContentSize().height - pStage->getContentSize().height));
	this->addChild(pStage, Z_ORDER_TITLE);

	CCLabelTTF *pStageLabel = CCLabelTTF::create("1", "Arial", 21);
	pStageLabel->setColor((ccc3(255, 255, 255)));
	pStageLabel->setPosition(ccp(pStage->getPositionX() + size.width + 10, pStage->getPositionY()));
	this->addChild(pStageLabel, Z_ORDER_TITLE);
	pStageLabel->setString(CommonUtil::intToStr(stageInfo->getCurStage()));

	//taget
	msg = (CCString*)text->objectForKey("tar");
	CCLabelTTF *pTarget = CCLabelTTF::create(msg->getCString(), "Arial", 21);
	pTarget->setColor(ccWHITE);
	size = pTarget->getContentSize();
	pTarget->setPosition(ccp(visibleSize.width * 2 / 5, pStage->getPositionY()));
	this->addChild(pTarget, Z_ORDER_TITLE);

	CCLabelTTF *pTargetLabel = CCLabelTTF::create("1000", "Arial", 21);
	pTargetLabel->setColor(ccWHITE);
	pTargetLabel->setPosition(ccp(pTarget->getPositionX() + size.width, pStage->getPositionY()));
	this->addChild(pTargetLabel, Z_ORDER_TITLE);
	//在onstepchaged 里面修改

	//steps
	msg = (CCString*)text->objectForKey("step");
	CCLabelTTF *pStep = CCLabelTTF::create(msg->getCString(), "Arial", 21);
	pStep->setColor(ccWHITE);
	size = pStep->getContentSize();
	pStep->setPosition(ccp(visibleSize.width * 0.15f, hightScore->getPositionY()));
	this->addChild(pStep, Z_ORDER_TITLE);

	m_pStepLabel = CCLabelTTF::create("10", "Arial", 21);
	m_pStepLabel->setColor(ccWHITE);
	m_pStepLabel->setPosition(ccp(pStep->getPositionX() + size.width, hightScore->getPositionY()));
	this->addChild(m_pStepLabel, Z_ORDER_TITLE);
	onStepsChanged();

	//coins 
	CCSprite* currentCoinBg = CCSprite::create("dialog_item.png");
	currentCoinBg->setPosition(ccp(VisibleRect::right().x - currentCoinBg->getContentSize().width / 2 - 10, pTarget->getPositionY()));
	this->addChild(currentCoinBg, Z_ORDER_PROPS_BG);
	CCSprite* diamondSp = CCSprite::create("diamond.png");
	diamondSp->setPosition(ccp(diamondSp->getContentSize().width / 4, currentCoinBg->getContentSize().height / 2));
	currentCoinBg->addChild(diamondSp);

	CCLabelTTF *m_pCoins = CCLabelTTF::create("0", "Arial", 21);
	m_pCoins->setColor(ccWHITE);
	m_pCoins->setPosition(currentCoinBg->getPosition());
	addChild(m_pCoins, Z_ORDER_TITLE);

	CCSprite *pBuyItemNormal = CCSprite::create("coin_add.png");
	CCSprite *pBuyItemSelected = CCSprite::create("coin_add.png");
	pBuyItemSelected->setScale(1.1f);
	pBuyItemSelected->setAnchorPoint(ccp(0.05f, 0.05f));
	CCMenuItem *pBuy = CCMenuItemSprite::create(pBuyItemNormal, pBuyItemSelected, this, menu_selector(StageUiLayer::menuCallback));
	pBuy->setPosition(ccp(currentCoinBg->getPositionX() + currentCoinBg->getContentSize().width / 2 - pBuy->getContentSize().width / 2,
		currentCoinBg->getPositionY()));

	CCMenu *pMenu = CCMenu::create();
	pMenu->setTouchPriority(1);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu, Z_ORDER_PROPS);
	pMenu->addChild(pBuy);

}

CCMenuItemSprite *StageUiLayer::getItemSprite(string fileName, SEL_MenuHandler selector)
{
	auto pItemNormal = CCSprite::create(fileName.c_str());
	auto pItemSelected = CCSprite::create(fileName.c_str());
	pItemSelected->setScale(1.2f);
	pItemSelected->setAnchorPoint(ccp(0.5f, 0.5f));
	return CCMenuItemSprite::create(pItemNormal, pItemSelected, this, selector);
}

void StageUiLayer::initPets()
{
	auto ids = PetManager::petMgr()->getCurPetIds();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	for (size_t i = 0; i < ids.size(); ++i)
	{
		PetView *view = PetView::create(ids[i]);
		addChild(view, kZorder_Pet);
		
		CCSize size = view->getContentSize();
		view->setPosition(ccp(winSize.width * 0.25f + size.width * i * 1.2f, winSize.height * 0.8f));
	}
}

void StageUiLayer::initBottomUi()
{
	char str[100] = { 0 };
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	//pause
	CCSprite *pItemNormal = CCSprite::create("Item_pause.png");
	CCSprite *pItemSelected = CCSprite::create("Item_pause.png");
	CCMenuItem *pPause = CCMenuItemSprite::create(pItemNormal, pItemSelected, this, menu_selector(StageUiLayer::onPauseBtnClicked));
	pItemSelected->setScale(1.1f);
	pItemSelected->setAnchorPoint(ccp(0.05f, 0.05f));
	CCSize size = pPause->getContentSize();
	pPause->setPosition(ccp(size.width * 0.5f, size.height *0.5f));

	//menu for ui buttons 
	CCMenu *pMenu = CCMenu::create();
	pMenu->setTouchPriority(1);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu, Z_ORDER_PROPS);
	pMenu->addChild(pPause);

	//current score
	m_pScoreLabel = CCLabelTTF::create("0", "Arial", 32);
	m_pScoreLabel->setColor(ccWHITE);
	m_pScoreLabel->setPosition(ccp(VisibleRect::center().x - 16 * 3, pPause->getPositionY()));
	this->addChild(m_pScoreLabel, Z_ORDER_TITLE);
	onScoreChanged();
	/*
	m_pScoreHint = CCLabelTTF::create("", "Arial", 21);
	m_pScoreHint->setPosition(ccp(VisibleRect::center().x,
		pTargetLabel->getPositionY() - size.height - m_pScoreHint->getContentSize().height - 80));
	m_pScoreHint->setColor(ccWHITE);
	this->addChild(m_pScoreHint, Z_ORDER_TITLE);
	*/

	//props
	float leftX = VisibleRect::center().x;
	float propsY = VisibleRect::rightBottom().y + 10;
	float propsX = VisibleRect::rightBottom().x - 10;
	//bomb btn
	pItemNormal = CCSprite::create("Props_Bomb.png");
	pItemSelected = CCSprite::create("Props_Bomb.png");
	pItemSelected->setScale(1.2f);
	pItemSelected->setAnchorPoint(ccp(0.05f, 0.05f));
	CCMenuItemSprite* pMagic = CCMenuItemSprite::create(pItemNormal, pItemSelected, this, menu_selector(StageUiLayer::menuCallback));
	pMagic->setAnchorPoint(ccp(1, 0));
	pMagic->setPosition(ccp(propsX, propsY));
	propsX -= pMagic->getContentSize().width * 1.2f;
	pMenu->addChild(pMagic);
	if (GameData::getInstance()->m_nUseProType != USE_PRO_TYPE_COINONLY){
		m_pBombLabel = CCLabelTTF::create(CCString::createWithFormat("%d", UserInfo::getProCount(USERINFO_PRO_TYPE_BOMB))->getCString(), "Arial", 18);
		m_pBombLabel->setPosition(ccp(pMagic->getContentSize().width - m_pBombLabel->getContentSize().width / 2, 0));
		pMagic->addChild(m_pBombLabel);
	}

	//panit btn
	leftX = pMagic->getPositionX();
	pItemNormal = CCSprite::create("Props_Paint.png");
	pItemSelected = CCSprite::create("Props_Paint.png");
	pMagic = CCMenuItemSprite::create(pItemNormal, pItemSelected, this, menu_selector(StageUiLayer::menuCallback));
	pItemSelected->setScale(1.2f);
	pItemSelected->setAnchorPoint(ccp(0.05f, 0.05f));
	pMagic->setAnchorPoint(ccp(1, 0));
	pMagic->setPosition(ccp(propsX, propsY));
	propsX -= pMagic->getContentSize().width * 1.2f;;
	pMenu->addChild(pMagic);
	if (GameData::getInstance()->m_nUseProType != USE_PRO_TYPE_COINONLY){
		m_pPaintLabel = CCLabelTTF::create(CCString::createWithFormat("%d", UserInfo::getProCount(USERINFO_PRO_TYPE_PAINT))->getCString(), "Arial", 18);
		m_pPaintLabel->setPosition(ccp(pMagic->getContentSize().width - m_pPaintLabel->getContentSize().width / 2, 0));
		pMagic->addChild(m_pPaintLabel);
	}

	//rainbow btn
	leftX = pMagic->getPositionX();
	pItemNormal = CCSprite::create("Props_Rainbow.png");
	pItemSelected = CCSprite::create("Props_Rainbow.png");
	pMagic = CCMenuItemSprite::create(pItemNormal, pItemSelected, this, menu_selector(StageUiLayer::menuCallback));
	pItemSelected->setScale(1.2f);
	pItemSelected->setAnchorPoint(ccp(0.05f, 0.05f));
	pMagic->setAnchorPoint(ccp(1, 0));
	pMagic->setPosition(ccp(propsX, propsY));
	propsX -= pMagic->getContentSize().width * 1.2f;
	pMenu->addChild(pMagic);
	if (GameData::getInstance()->m_nUseProType != USE_PRO_TYPE_COINONLY){
		m_pReflashLabel = CCLabelTTF::create(CCString::createWithFormat("%d", UserInfo::getProCount(USERINFO_PRO_TYPE_REFLASH))->getCString(), "Arial", 18);
		m_pReflashLabel->setPosition(ccp(pMagic->getContentSize().width - m_pReflashLabel->getContentSize().width / 2, 0));
		pMagic->addChild(m_pReflashLabel);
	}

}

void StageUiLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){

}

void StageUiLayer::onQuitGame()
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, MenuScene::scene()));
}

void StageUiLayer::showGameOverHint()
{
	//game over hint
	CCSprite *sp = CCSprite::create("stage_clear.png");
	this->addChild(sp);
}

void StageUiLayer::deliveryScore( const CCPoint &from, int totalScore, int count ){
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
}

void StageUiLayer::setStageClear( bool clear ){
	/*
    if (clear){
        m_pStageClear->setScale(0.8f);
        m_pStageClear->setPosition(VisibleRect::center());
        m_pStageClear->setVisible(true);
        m_pStageClear->runAction(CCSequence::create(
            CCScaleTo::create(0.2f, 1.0, 1.0),
            CCDelayTime::create(0.6f),
            CCSpawn::create(
                CCMoveTo::create(1.0f, m_obStageClearPosition),
                CCScaleTo::create(1.0f, 0.25f, 0.25f),
                NULL
                ),
            NULL));
    }else{
        m_pStageClear->setVisible(false);
    }
	*/
}

void StageUiLayer::menuCallback( CCObject *pSender )
{
	StageOperator obj;
	obj.reOrderStars();
}

void StageUiLayer::onStepsChanged()
{
	auto stageInfo = StageModel::theModel()->getStageInfo();
	int leftStep = stageInfo->getLeftStep();
	m_pStepLabel->setString(CommonUtil::intToStr(leftStep));


}

void StageUiLayer::onScoreChanged()
{
	auto stageInfo = StageModel::theModel()->getStageInfo();
	int curScore = stageInfo->getCurScore();
	m_pScoreLabel->setString(CommonUtil::intToStr(curScore));
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
	addChild(PauseLayer::create(), Z_ORDER_PAUSE);
	//onQuitGame();
}
