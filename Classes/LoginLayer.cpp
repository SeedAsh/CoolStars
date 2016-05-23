#include "LoginLayer.h"
#include "GameData.h"
#include "VisibleRect.h"
#include "SoundMgr.h"
#include "UserInfo.h"
#include "MyPurchase.h"
LoginLayer::LoginLayer(void):
m_pGetAni(NULL)
{

}


LoginLayer::~LoginLayer(void){

}

bool LoginLayer::init(){
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init()){
		return false;
	}
	CCSprite *pLoginBg = CCSprite::create("loginBg.png");
	pLoginBg->setPosition(VisibleRect::center());
	addChild(pLoginBg,Z_ORDER_LOGIN_BG);
	
	CCSprite *pItemNormal = CCSprite::create("loginCancel.png");
	CCSprite *pItemSelected = CCSprite::create("loginCancel.png");
	CCMenuItem *pClose = CCMenuItemSprite::create(pItemNormal, pItemSelected, this, menu_selector(LoginLayer::close));
	pClose->setPosition(ccp(pLoginBg->getPositionX() + pLoginBg->getContentSize().width / 2 - pClose->getContentSize().width / 2 - 5, 
		pLoginBg->getPositionY() + pLoginBg->getContentSize().height / 2 - pClose->getContentSize().height / 2 - 5));
	pItemSelected->setScale(1.1f);
	pItemSelected->setAnchorPoint(ccp(0.05f, 0.05f));
	int days = UserInfo::s_nShowLoginDays - 1;
	float startX = 65.0f;
	float startY = 100.0f;
	float preWidth = 115.0f;
	float preHeight = 110.0f;
	for (int i = 0;i < days; i++){
		CCSprite *pAlready = CCSprite::create("loginGet.png");
		pAlready->setPosition(ccp(startX + ((i % 3) * preWidth),pLoginBg->getContentSize().height - startY - (i / 3) * preHeight));
		pLoginBg->addChild(pAlready);
		if (i == (days - 1)){
			m_pGetAni = pAlready;
			m_pGetAni->setVisible(false);
			m_pGetAni->setScale(3.0f);
		}
	}
	CCMenu *pMenu = CCMenu::create(pClose, NULL);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu, Z_ORDER_LOGIN_BTN);
	CCDictionary *text = CCDictionary::createWithContentsOfFile(XML_DATA);
	if (UserInfo::getFishLiBao()){
		CCSprite* fishItem = CCSprite::create("fishlibao.png");
		CCMenuItemSprite *menuFishItem = CCMenuItemSprite::create(fishItem, fishItem, this, menu_selector(LoginLayer::menuClick));
		menuFishItem->setPosition(ccp(pLoginBg->getPositionX() + pLoginBg->getContentSize().width * 1 / 6,
			pLoginBg->getPositionY() - pLoginBg->getContentSize().height / 2 + menuFishItem->getContentSize().height + 5));
		menuFishItem->runAction(CCRepeatForever::create(
			CCSequence::create(
			CCScaleTo::create(0.75f,1.2f),
			CCScaleTo::create(0.75f,1),
			NULL)
			));
		pMenu->addChild(menuFishItem);

		CCString *onceCount = (CCString*)text->objectForKey("onceCount");
		CCString *oneTipsStr = (CCString*)text->objectForKey("onceTips2");
		CCString *oneTips = CCString::createWithFormat(oneTipsStr->getCString(),onceCount->intValue());
		CCLabelTTF *onlyPrice2Label = CCLabelTTF::create(oneTips->getCString(), "Arial", 22);
		onlyPrice2Label->setPosition(ccp(menuFishItem->getPositionX(),
			menuFishItem->getPositionY() - menuFishItem->getContentSize().height / 2 - onlyPrice2Label->getContentSize().height / 2 + 2));
		onlyPrice2Label->setColor(ccc3(252,206,0));
		addChild(onlyPrice2Label,Z_ORDER_LOGIN_FG);
	}

	CCString *phone = (CCString*)text->objectForKey("phone");
	CCLabelTTF *phoneLabel = CCLabelTTF::create(phone->getCString(), "Arial", 12);
	phoneLabel->setPosition(ccp(pLoginBg->getContentSize().width / 2,
		phoneLabel->getContentSize().height / 2 + 3));
	phoneLabel->setColor(ccc3(252,206,0));
	pLoginBg->addChild(phoneLabel);

	setPosition(ccp(0, -0.5 * getContentSize().height));

	return true;
}

bool LoginLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	return true;
}

void LoginLayer::onEnter(){
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
	//runAction(CCMoveBy::create(0.3f, ccp(0, getContentSize().height - 80) / 2));
	runAction(CCSequence::create(
		CCMoveBy::create(0.3f, ccp(0, getContentSize().height - 80) / 2),
		CCDelayTime::create(0.3f),
		CCCallFunc::create(this, callfunc_selector(LoginLayer::loginAni)),
		NULL
		));
}

void LoginLayer::loginAni(){
	if (m_pGetAni != NULL){
		m_pGetAni->setVisible(true);
		m_pGetAni->runAction(CCScaleTo::create(1.0f,1.0f));
	}
}

void LoginLayer::onExit(){
	CCLayer::onExit();	
	addLoginGift();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);    
}

void LoginLayer::addLoginGift(){
	int days = UserInfo::s_nShowLoginDays;
	if (days <= 0 || days > 7){
		return;
	}
	int giftType = GameData::getInstance()->m_nLoginGift[days - 1][0];
	if (giftType <= 0){
		return;
	}
	int giftCount = GameData::getInstance()->m_nLoginGift[days - 1][1];
	switch(giftType){
	case USERINFO_PRO_TYPE_BOMB:
	case USERINFO_PRO_TYPE_PAINT:
	case USERINFO_PRO_TYPE_REFLASH:
		UserInfo::addProByType(giftType,giftCount);
		break;
	case USERINFO_TYPE_COIN:
		UserInfo::addCoins(giftCount);
		break;
	}
	UserInfo::setLoginDays();
}

void LoginLayer::close( CCObject *pSender ){
	SoundMgr::playEffect(SoundMgr::EFFECT_CLICK);
	runAction(CCSequence::create(
		CCMoveBy::create(0.3f, ccp(0, -0.5 * getContentSize().height)),
		CCCallFunc::create(this, callfunc_selector(CCNode::removeFromParent)),
		NULL));
}

void LoginLayer::menuClick( CCObject *pSender ){
	SoundMgr::playEffect(SoundMgr::EFFECT_CLICK);
	MyPurchase::sharedPurchase()->payForProducts(this,PAY_TYPE_FISH_LIBAO,callfuncN3I_selector(LoginLayer::payCallBack));
}

void LoginLayer::payCallBack(CCNode* nouse, int payType, int payResult,int payIntNoUse){
	if (payResult != PAY_RESULT_SUCCESS){
		return;
	}
	UserInfo::setFishLiBao();		
	close(NULL);
}