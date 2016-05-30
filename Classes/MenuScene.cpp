#include "MenuScene.h"
#include "StageScene.h"
#include "VisibleRect.h"
#include "UserInfo.h"
#include "SoundMgr.h"
#include "ShopLayer.h"
#include "HelpLayer.h"
#include "MyPurchase.h"
#include "ExitLayer.h"
#include "LoginLayer.h"
#include "PanelMacros.h"
#include "QuickBuyScene.h"
#include "StageUiLayer.h"
#include "StarUtil.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//#include "MyPurchaseIOS.h"
#endif
USING_NS_CC;
USING_NS_CC_EXT;

enum {
	TAG_LIGHT = 1,
	TAG_STAR,
	TAG_FIRE,
	TAG_FISH_CLOSE,
	TAG_FISH_BUY,
	TAG_DALIBAO
};

#define MENU_ITEM_HEIGHT 70

bool MenuScene::init()  
{  
	//////////////////////////////  
	// 1. super init first  
	if (!CCLayer::init()){  
		return false;  
	} 

	m_pMenuFishItem = NULL;
	m_pFishShop = NULL;
	setKeypadEnabled(true);

	//获取窗口大小  
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();  
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();  

	CCSprite *pMenuBg = CCSprite::create("bg_menuscene.jpg");
	pMenuBg->setPosition(VisibleRect::center());
	CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
	float scale = frameSize.width / DESIGN_WIDTH;
	if (scale > 0){
		float scaleY = frameSize.height / DESIGN_HEIGHT;
		if (scaleY > scale){
			float bgScale = scaleY / scale;
			pMenuBg->setScale(bgScale);
		}		
	}
	this->addChild(pMenuBg, Z_ORDER_BACKGROUND);

	CCSprite* soundSp = CCSprite::create("menu_sound_on.png");
	CCSprite* sound2Sp = CCSprite::create("menu_sound_off.png");

	CCMenuItemSprite* menuItemHelp = CreateMenuItemSprite("menu_help.png", menu_selector(MenuScene::helpClicked));
	menuItemHelp->setPosition(VisibleRect::center());
	CCSize size = menuItemHelp->getContentSize();
	menuItemHelp->setPosition(ccp(VisibleRect::left().x + size.width,VisibleRect::bottom().y + size.height));

	CCMenuItemToggle* menuItempSound = CCMenuItemToggle::createWithTarget(this, menu_selector(MenuScene::SwitchSound)
		,CCMenuItemSprite::create(soundSp, soundSp)
		,CCMenuItemSprite::create(sound2Sp, sound2Sp),NULL);
	menuItempSound->setSelectedIndex(SoundMgr::isMute() ? 1 : 0);	
	menuItempSound->setPosition(ccp(menuItemHelp->getPositionX(),
		menuItemHelp->getPositionY() + menuItemHelp->getContentSize().height / 2 + menuItempSound->getContentSize().height / 2 + 5));


	CCMenuItemSprite* menuItem1 = CreateMenuItemSprite("menu_start.png", menu_selector(MenuScene::NewGame));
#if (PAY_PLUGIN_TYPE_JIDI == 1)
	menuItem1->setPosition(VisibleRect::center() + ccp(0, menuItem1->getContentSize().height));
#else
	menuItem1->setPosition(VisibleRect::center());
#endif

	light1Pos = ccp(origin.x+visibleSize.width/2-menuItem1->getContentSize().width/2, 
		VisibleRect::center().y);
	light2Pos = ccp(origin.x+visibleSize.width/2+menuItem1->getContentSize().width/2-10, 
		VisibleRect::center().y - 25);
	light3Pos = ccp(origin.x+visibleSize.width/2+menuItem1->getContentSize().width/2-10, 
		VisibleRect::top().y - 30);

	CCMenuItemSprite* menuItem2 = CreateMenuItemSprite("menu_continue.png", menu_selector(MenuScene::ResumeGame));
	float y = menuItem1->getPositionY() - MENU_ITEM_HEIGHT;
	menuItem2->setPosition(ccp(origin.x + visibleSize.width / 2, y));

	CCSprite* sItem = CCSprite::create("menu_shop.png");
	CCSprite* sSelItem = CCSprite::create("menu_shop.png");
	CCSprite *newSp = CCSprite::create("new.png");
	CCSprite *newSp1 = CCSprite::create("new.png");
	newSp->setPosition(ccp(sItem->getContentSize().width - newSp->getContentSize().width / 2,sItem->getContentSize().height - newSp->getContentSize().height / 2));
	sItem->addChild(newSp);
	newSp1->setPosition(newSp->getPosition());
	sSelItem->setScale(MENU_ITEM_SEL_SCALE);
	sSelItem->addChild(newSp1);
	CCMenuItemSprite* menuItem3 = CCMenuItemSprite::create(sItem, sSelItem, this, menu_selector(MenuScene::shopClicked));
	sSelItem->setAnchorPoint(MENU_ITEM_SEL_ANCHOR);
	y = menuItem2->getPositionY() - MENU_ITEM_HEIGHT;
	menuItem3->setPosition(ccp(origin.x + visibleSize.width / 2, y));

	if (!StarUtil::hasSavedState()){
		menuItem2->setEnabled(false);
	}

	CCMenu* pMenu = CCMenu::create(menuItem1, menuItem2,menuItem3,menuItempSound, menuItemHelp, NULL);
	pMenu->setPosition(CCPointZero);
	pMenu->setTouchPriority(5);
	this->addChild(pMenu,Z_ORDER_PANEL);

#if (PAY_PLUGIN_TYPE_JIDI == 1)
	CCMenuItemSprite* menuItem4 = CreateMenuItemSprite("menu_moregame.png", menu_selector(MenuScene::moreGame));
	y = menuItem3->getPositionY() - MENU_ITEM_HEIGHT;
	menuItem4->setPosition(ccp(origin.x + visibleSize.width / 2, y));
	pMenu->addChild(menuItem4);
#endif
	//新手礼包
	
	if (UserInfo::getFishLiBao()){
		CCSprite* fishItem = CCSprite::create("fish_icon.png");
		m_pMenuFishItem = CCMenuItemSprite::create(fishItem, fishItem, this, menu_selector(MenuScene::showOrHideLiBao));
		m_pMenuFishItem->setPosition(ccp(VisibleRect::right().x - m_pMenuFishItem->getContentSize().width / 2 - 20,
			VisibleRect::center().y + m_pMenuFishItem->getContentSize().height * 2));
		m_pMenuFishItem->runAction(CCRepeatForever::create(
			CCSequence::create(
			CCScaleTo::create(0.75f,1.2f),
			CCScaleTo::create(0.75f,1),
			NULL)
			));
		pMenu->addChild(m_pMenuFishItem);
	}
	if (UserInfo::s_bShowLogin){
		LoginLayer* pLoginLayer = LoginLayer::create();
		addChild(pLoginLayer,Z_ORDER_BUY);
	}
	//礼包
	/*
	CCSprite* fishItem = CCSprite::create("fish_icon.png");
	CCMenuItemSprite* pDalibaoItem = CCMenuItemSprite::create(fishItem, fishItem, this, menu_selector(MenuScene::showDaLiBao));
	pDalibaoItem->setPosition(ccp(VisibleRect::right().x - pDalibaoItem->getContentSize().width / 2 - 20,
		VisibleRect::center().y + pDalibaoItem->getContentSize().height * 2));
	pDalibaoItem->runAction(CCRepeatForever::create(
		CCSequence::create(
		CCScaleTo::create(0.75f,1.2f),
		CCScaleTo::create(0.75f,1),
		NULL)
		));
	pMenu->addChild(pDalibaoItem);*/

	int i = 0;
	fadeNode[i++] = SoundMgr::isMute() ? sound2Sp : soundSp;
	fadeNode[i++] = menuItemHelp;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    menuItempSound->setVisible(false);
#endif
	i = 0;
	menuItem[i++] = menuItem1;
	menuItem[i++] = menuItem2;
	menuItem[i++] = menuItem3;
#if (PAY_PLUGIN_TYPE_JIDI == 1)
	menuItem[i++] = menuItem4;
#endif
	for (i = 0; i < MENU_COUNT; i++) {
		menuPos[i] = menuItem[i]->getPosition();
	}
	SoundMgr::playMusic(SoundMgr::MUSIC_BACKGROUND);
	return true;  
}  

void MenuScene::onEnter()
{
	CCLayer::onEnter();

	for (int i = 0; i < FADE_COUNT; i++) {
		dynamic_cast<CCRGBAProtocol*>(fadeNode[i])->setOpacity(0);
		fadeNode[i]->setVisible(false);
	}

	for (int i = 0; i < MENU_COUNT; i++) {
		menuItem[i]->setVisible(false);
	}
	runMenuAction(MENU_COUNT-1);
}

void MenuScene::moreGame(CCObject* sender){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID && PAY_PLUGIN_TYPE_JIDI == 1)
	MyPurchase::sharedPurchase()->moreGame();
#endif
}

void MenuScene::onExit(){
	CCLayer::onExit();
	unscheduleAllSelectors();
	removeAllChildByTag(TAG_LIGHT);
	removeAllChildByTag(TAG_STAR);
	removeAllChildByTag(TAG_FIRE);
}

cocos2d::CCMenuItemSprite* MenuScene::CreateMenuItemSprite( const char* frameName, SEL_MenuHandler selector ){
	CCSprite* sItem = CCSprite::create(frameName);
	CCSprite* sSelItem = CCSprite::create(frameName);
	sSelItem->setScale(MENU_ITEM_SEL_SCALE);
	CCMenuItemSprite* menuItem1 = CCMenuItemSprite::create(sItem, sSelItem, this, selector);
	sSelItem->setAnchorPoint(MENU_ITEM_SEL_ANCHOR);
	return menuItem1;
}


CCScene* MenuScene::scene(){
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	MenuScene *layer = MenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void MenuScene::NewGame( CCObject* sender ){
	if (m_pFishShop != NULL && m_pFishShop->isVisible()){
		return;
	}
	SoundMgr::playEffect(SoundMgr::EFFECT_CLICK);
    CCDirector::sharedDirector()->replaceScene(getTansitionScene(StageScene::scene()));
}

void MenuScene::ResumeGame( CCObject* sender ){
	if (m_pFishShop != NULL && m_pFishShop->isVisible()){
		return;
	}
	SoundMgr::playEffect(SoundMgr::EFFECT_CLICK);
    if (StarUtil::hasSavedState()){
        CCDirector::sharedDirector()->replaceScene(getTansitionScene(StageScene::scene()));
    }
}

void MenuScene::shopClicked( CCObject* sender ){
	if (m_pFishShop != NULL && m_pFishShop->isVisible()){
		return;
	}
	SoundMgr::playEffect(SoundMgr::EFFECT_CLICK);
	ShopLayer *pShop = ShopLayer::create();
	addChild(pShop, Z_ORDER_SHOP);
	UserInfo::s_nCurrentLevel = 0;
}

void MenuScene::helpClicked( CCObject* sender ){
	if (m_pFishShop != NULL && m_pFishShop->isVisible()){
		return;
	}
	SoundMgr::playEffect(SoundMgr::EFFECT_CLICK);
	HelpLayer *pHelp = HelpLayer::create();
	addChild(pHelp, Z_ORDER_SHOP);
}

void MenuScene::EndGame( CCObject* sender )
{	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID && PAY_PLUGIN_TYPE_JIDI == 1)
	if (MyPurchase::sharedPurchase()->exitGame()){
		CCDirector::sharedDirector()->end();
	}
#else
	CCDirector::sharedDirector()->end();
#endif
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void MenuScene::keyBackClicked(){
	
	EndGame(NULL);	
}


CCScene* MenuScene::getTansitionScene( CCScene* scene ){
	return CCTransitionTurnOffTiles::create(0.5f, scene);
}


void MenuScene::SwitchSound( CCObject* sender ){
	int sel =  dynamic_cast<CCMenuItemToggle*>(sender)->getSelectedIndex();
	SoundMgr::setMute(sel == 0 ? false : true);
	SoundMgr::playEffect(SoundMgr::EFFECT_CLICK);
}

void MenuScene::explodeFire( CCPoint position ){
	CCParticleExplosion *pEmitter = CCParticleExplosion::create();
	//CCParticleSnow *pEmitter = CCParticleSnow::create();
    pEmitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("particle/fire.png") );
	
	pEmitter->setAutoRemoveOnFinish(true);

	pEmitter->setPosition(position);

	//Size
	pEmitter->setStartSize(3.0);
	pEmitter->setStartSizeVar(5.0);

	//pEmitter->setTotalParticles(totalParticles);

	pEmitter->setRadialAccel(10.0);
	pEmitter->setRadialAccelVar(0.0);

	pEmitter->setLife(0.2f);
	pEmitter->setLifeVar(1.5f);

	pEmitter->setDuration(1.0f);

	addChild(pEmitter, Z_ORDER_EXPLOSION, TAG_FIRE);
	SoundMgr::playFire(SoundMgr::FIRE_MAX);
}

void MenuScene::startFire()
{
	srand(time(NULL));

	fireTime = 0;
	fire(0);
}

void MenuScene::fire( float dt )
{
	//CCLog("fire db %f",dt);
	float delay = 0.5f;
	if (fireTime == 0) {
		fireTime += 0.1f;		
	} else if (fireTime > 3.0f) {
		fireTime = 0;
		delay = 2.0f;
	} else {
		fireTime += dt;
	}
	if (fireTime != 0) {
		explodeFire(getRandomPosForFire());
	}
	unschedule(schedule_selector(MenuScene::fire));
	schedule(schedule_selector(MenuScene::fire), delay);
}

cocos2d::CCPoint MenuScene::getRandomPosForFire()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();  
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();  
	int x = rand()%((int)visibleSize.width) + origin.x;
	int y = rand()%((int)(visibleSize.height/2)) + origin.y+visibleSize.height/2;
	return ccp(x, y);
}

void MenuScene::runFadeInAction( CCNode* sprite )
{
	CCAction* showAction = CCFadeIn::create(2.0f);
	//sprite->setOpacity(0);
	sprite->runAction(showAction);
}

void MenuScene::nextMenu( CCNode* node, void* data ){
	runMenuAction((int)data);
}

void MenuScene::runMenuAction( int i ){
	if (i < 0 || i >= MENU_COUNT) {
		startFire();
		for (int i = 0; i < FADE_COUNT; i++) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
            if (i == 0){
                continue;
            }
#endif
			fadeNode[i]->setVisible(true);
			runFadeInAction(fadeNode[i]);
		}
		return;
	}
	CCNode* sprite = menuItem[i];
	CCPoint pos = menuPos[i];

	i--;

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	float speed = visibleSize.height/0.7f;

	sprite->setPosition(ccp(pos.x, origin.y+visibleSize.height+sprite->getContentSize().height));
	sprite->setVisible(true);
	CCMoveTo* dropAction1 = CCMoveTo::create((origin.y+visibleSize.height-pos.y)/speed, ccp(pos.x, pos.y));
	CCEaseElasticOut* dropAction = CCEaseElasticOut::create(dropAction1, 0.5f);
	CCCallFuncND* nextMenuAction = CCCallFuncND::create(this, callfuncND_selector(MenuScene::nextMenu), (void*)i);
	CCDelayTime *startDelay = CCDelayTime::create(0.5f);
	if (i+1 == MENU_COUNT-1) {
		sprite->runAction(CCSequence::create(startDelay, dropAction, NULL));
		sprite->runAction(CCSequence::create(startDelay, CCDelayTime::create(0.2f), nextMenuAction, NULL));
	} else {
		sprite->runAction(CCSequence::create(dropAction, NULL));
		sprite->runAction(CCSequence::create(CCDelayTime::create(0.2f), nextMenuAction, NULL));
	}	
}

void MenuScene::removeAllChildByTag( int tag ){
	CCNode* child = NULL;
	while (child = getChildByTag(tag)) {
		child->stopAllActions();
		this->removeChild(child);
	}
}

void MenuScene::showDaLiBao(CCObject* sender){
	if (getChildByTag(TAG_DALIBAO) != NULL){
		return;
	}
	QuickBuyLayer* pQuickBuyLayer = QuickBuyLayer::create();
	addChild(pQuickBuyLayer,Z_ORDER_BUY,TAG_DALIBAO);
	pQuickBuyLayer->setCallbackListener(this,callfuncN3I_selector(MenuScene::payLiBaoCallBack));
}

void MenuScene::showOrHideLiBao(CCObject* sender){
	MyPurchase::sharedPurchase()->payForProducts(this,(MyPayProducts)PAY_TYPE_FISH_LIBAO,callfuncN3I_selector(MenuScene::payCallBack));
}

void MenuScene::fishLiBaoClickedCallBack(CCObject* sender){
	int tag = ((CCNode *)sender)->getTag();
	if (tag == TAG_FISH_BUY){
		MyPurchase::sharedPurchase()->payForProducts(this,(MyPayProducts)PAY_TYPE_FISH_LIBAO,callfuncN3I_selector(MenuScene::payCallBack));
	}else{
		showOrHideLiBao(NULL);
	}	
}

void MenuScene::payLiBaoCallBack(CCNode* nouse, int payType, int payResult,int payTag){
	if (payTag == QUICK_MENU_CLOSE_TAG){
		CCNode* liBao = getChildByTag(TAG_DALIBAO);
		if (liBao != NULL){
			removeChild(liBao);
		}
		return;
	}
	if (payResult != PAY_RESULT_SUCCESS){
		return;
	}
	CCNode* liBao = getChildByTag(TAG_DALIBAO);
	if (liBao != NULL){
		removeChild(liBao);
	}
}

void MenuScene::payCallBack(CCNode* nouse, int payType, int payResult,int payIntNoUse){
	if (payResult != PAY_RESULT_SUCCESS){
		return;
	}
	UserInfo::setFishLiBao();		
	m_pMenuFishItem->setVisible(false);
}