#include "PauseLayer.h"
#include "VisibleRect.h"
#include "StageModel.h"
#include "MenuScene.h"
#include "StageSavingHelper.h"

PauseLayer::PauseLayer(void)
{
}


PauseLayer::~PauseLayer(void)
{
}

bool PauseLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
    return true;
}

bool PauseLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if (!CCLayer::init()){
        return false;
    }


    CCSprite *pItemNormal = CCSprite::create("menu_continue.png");
    CCSprite *pItemSelected = CCSprite::create("menu_continue.png");
    CCMenuItem *pItemResume = CCMenuItemSprite::create(pItemNormal, pItemSelected, this, menu_selector(PauseLayer::menuResumeCallback));
    pItemSelected->setScale(1.1f);
    pItemSelected->setAnchorPoint(ccp(0.05f, 0.05f));
    pItemResume->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y + pItemResume->getContentSize().height - 50));

    pItemNormal = CCSprite::create("save.png");
    pItemSelected = CCSprite::create("save.png");
    CCMenuItem *pItemSave = CCMenuItemSprite::create(pItemNormal, pItemSelected, this, menu_selector(PauseLayer::menuSaveCallback));
    pItemSelected->setScale(1.1f);
    pItemSelected->setAnchorPoint(ccp(0.05f, 0.05f));
    pItemSave->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y - pItemSave->getContentSize().height - 50));

    CCMenu *pMenu = CCMenu::create(pItemResume, pItemSave, NULL);
    pMenu->setPosition(CCPointZero);
    addChild(pMenu);

    return true;
}

void PauseLayer::menuResumeCallback(CCObject* pSender)
{
    CCPoint from = getPosition();
    CCPoint to = CCPoint(from.x, from.y + getContentSize().height / 2);
    setPosition(from);
    runAction(CCSequence::create(
        CCMoveTo::create(0.1f, to),
        CCCallFunc::create(this, callfunc_selector(PauseLayer::removeFromParent)),
        NULL));
}

void PauseLayer::menuSaveCallback(CCObject* pSender){
	StageSavingHelper::saveCurStars();
	StageSavingHelper::saveCurStageData();

	//CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, MenuScene::scene()));
}

void PauseLayer::onEnter(){
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

    CCPoint to = getPosition();
    CCPoint from = CCPoint(to.x, to.y + getContentSize().height / 2);
    setPosition(from);
    runAction(CCEaseElasticOut::create(CCMoveTo::create(0.7f, to), 0.5f));
}

void PauseLayer::onExit(){
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);    
}
