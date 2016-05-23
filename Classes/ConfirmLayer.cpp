#include "ConfirmLayer.h"
#include "VisibleRect.h"
#include "MyPurchase.h"

ConfirmLayer::ConfirmLayer(void){
	m_pCallback = NULL;
	m_pCallbackTarget = NULL;
}


ConfirmLayer::~ConfirmLayer(void){

}

bool ConfirmLayer::init(){
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init()){
		return false;
	}
	CCSprite *spBg = CCSprite::create("payconfirmbg.png");
	spBg->setPosition(VisibleRect::center());
	addChild(spBg);

	CCSprite *pItemNormal = CCSprite::create("exit_lq.png");
	CCSprite *pItemSelected = CCSprite::create("exit_lq.png");
	CCMenuItem *pConfirm = CCMenuItemSprite::create(pItemNormal, pItemSelected, this, menu_selector(ConfirmLayer::menuClicked));
	pConfirm->setPosition(ccp(spBg->getPositionX() + spBg->getContentSize().width / 4, 
		spBg->getPositionY() - spBg->getContentSize().height / 2 + pConfirm->getContentSize().height / 2 + 20));
	pItemSelected->setScale(1.1f);
	pItemSelected->setAnchorPoint(ccp(0.05f, 0.05f));
	pConfirm->setTag(CONFIRM_SURE_BTN_TAG);

	CCSprite *pItemClose = CCSprite::create("confirm_cancel.png");
	CCSprite *pItemCloseSelected = CCSprite::create("confirm_cancel.png");
	CCMenuItem *pClose = CCMenuItemSprite::create(pItemClose, pItemCloseSelected, this, menu_selector(ConfirmLayer::menuClicked));
	pClose->setPosition(ccp(spBg->getPositionX() - spBg->getContentSize().width / 4, 
		pConfirm->getPositionY()));
	pItemCloseSelected->setScale(1.1f);
	pItemCloseSelected->setAnchorPoint(ccp(0.05f, 0.05f));
	pClose->setTag(CONFIRM_CLOSE_BTN_TAG);

	CCMenu *pMenu = CCMenu::create(pConfirm, pClose, NULL);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu, 1);

	setPosition(ccp(0, 0));
	return true;
}

bool ConfirmLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	return true;
}

void ConfirmLayer::setPayCallBack(CCObject *target,MyPayProducts product, SEL_CallFuncN3I selector /* = NULL */ ){
	m_pCallbackTarget = target;
	m_pCallback = selector;
	m_nCurrentPayType = product;
}

void ConfirmLayer::onEnter(){
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
}

void ConfirmLayer::onExit(){
	CCLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);    
}

void ConfirmLayer::menuClicked( CCObject *pSender ){
	CCMenuItem *pMenuClick = (CCMenuItem*)pSender;
	if (pSender == NULL){
		return;
	}
	int tag = pMenuClick->getTag();
	if (tag == CONFIRM_SURE_BTN_TAG){
		MyPurchase::sharedPurchase()->payForProducts(m_pCallbackTarget,(MyPayProducts)m_nCurrentPayType,m_pCallback);
	}
	removeFromParent();
}