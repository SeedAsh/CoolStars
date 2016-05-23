#include "QuickBuyScene.h"
#include "VisibleRect.h"
#include "MyPurchase.h"
#include "GameData.h"
#include "ConfirmLayer.h"

QuickBuyLayer::QuickBuyLayer(void){
	m_pCallback = NULL;
	m_pCallbackTarget = NULL;
	m_pCurrentStage = 0;
}


QuickBuyLayer::~QuickBuyLayer(void){
	
}

bool QuickBuyLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent ){
	CCSprite* pBg = CCSprite::create("libaobg.png");
	CCSize pSize = pBg->getContentSize();
	bool yTouch = false;
	if (pTouch->getLocation().y > VisibleRect::center().y - pSize.height / 2 && pTouch->getLocation().y < VisibleRect::center().y){
		yTouch = true;
	}
	bool xTouch = false;
	if (pTouch->getLocation().x > VisibleRect::center().x - pSize.width / 2 + 20 && pTouch->getLocation().x < VisibleRect::center().x + pSize.width / 2 - 20){
		xTouch = true;
	}
	if (xTouch && yTouch){
		CCNode* pNode = CCNode::create();
		pNode->setTag(QUICK_MENU_BUY_TAG);
		onMenuBtnCallBack(pNode);
	}
	return true;
}

void QuickBuyLayer::onEnter(){
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void QuickBuyLayer::onExit(){
	CCLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);    
}

QuickBuyLayer* QuickBuyLayer::create(int stage){
	QuickBuyLayer *pRet = new QuickBuyLayer();
	if (pRet && pRet->init(stage)){
		pRet->autorelease();
		return pRet;
	}else{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

bool QuickBuyLayer::init(){
	return init(0);
}

bool QuickBuyLayer::init(int stage){
	m_pCurrentStage = stage;
	float menuDelayTime = 1.0f;
	float menuShowTime = 1.0f;
	if (GameData::getInstance()->m_nShowQuickBtn != 1){
		menuDelayTime = 0.1f;
		menuShowTime = 0.4f;
	}
	CCSprite* pBg = CCSprite::create("libaobg.png");
	pBg->setPosition(VisibleRect::center());
	addChild(pBg);
	CCSize size = pBg->getContentSize();

	CCDictionary *text = CCDictionary::createWithContentsOfFile(XML_DATA);
#if (PAY_PLUGIN_TYPE_XINYINHE == 1)
	CCSprite* pItemNormal = CCSprite::create("cancel_s.png");
	CCSprite* pItemSelected = CCSprite::create("cancel_s.png");
	pItemSelected->setScale(1.1f);
	CCMenuItemSprite* menuBackBtn = CCMenuItemSprite::create(pItemNormal, pItemSelected, this, menu_selector(QuickBuyLayer::onMenuBtnCallBack));
	menuBackBtn->setTag(QUICK_MENU_CLOSE_TAG);
	menuBackBtn->setPosition(ccp(pBg->getContentSize().width - menuBackBtn->getContentSize().width / 2 - 15,
		pBg->getContentSize().height - menuBackBtn->getContentSize().width / 2 - 5));
	menuBackBtn->setOpacity(0);
	menuBackBtn->runAction(CCSequence::create(CCDelayTime::create(menuDelayTime),CCFadeIn::create(menuShowTime),NULL));
	pItemNormal = CCSprite::create("menu_lingqu.png");
	pItemSelected = CCSprite::create("menu_lingqu.png");
	pItemSelected->setScale(1.05f);
	CCMenuItemSprite *menuLingquBtn = CCMenuItemSprite::create(pItemNormal, pItemSelected, this, menu_selector(QuickBuyLayer::onMenuBtnCallBack));
	menuLingquBtn->setTag(QUICK_MENU_BUY_TAG);
	menuLingquBtn->setPosition(ccp(pBg->getContentSize().width - menuLingquBtn->getContentSize().width / 2 - 20,
		pBg->getContentSize().height / 2 - menuLingquBtn->getContentSize().height - 10));

	CCMenu *menu = CCMenu::create(menuBackBtn, menuLingquBtn, NULL);
	menu->setPosition(CCPointZero);
	pBg->addChild(menu);

	/*ÃèÊö*/
	CCString *msg = (CCString*)text->objectForKey("libaodetail");
	CCString *bombCount = (CCString*)text->objectForKey("libaoBomb");
	CCString *paintCount = (CCString*)text->objectForKey("libaoPai");
	CCString *reflashCount = (CCString*)text->objectForKey("libaoRef");
	CCString *diaCount = (CCString*)text->objectForKey("libaoDia");
	CCString *detail = CCString::createWithFormat(msg->getCString(),bombCount->getCString(),paintCount->getCString(),reflashCount->getCString(),diaCount->getCString());
	CCLabelTTF *msgLabel = CCLabelTTF::create(detail->getCString(), "Arial", 19, CCSizeMake(pBg->getContentSize().width - 20,0),kCCTextAlignmentCenter);
	msgLabel->setPosition(ccp(pBg->getContentSize().width / 2,
		msgLabel->getContentSize().height / 2 + 10));
	int red = GameData::getInstance()->m_nLibaoMsgColorR;
	int green = GameData::getInstance()->m_nLibaoMsgColorG;
	int blue = GameData::getInstance()->m_nLibaoMsgColorB;
	msgLabel->setColor(ccc3(red,green,blue));
	pBg->addChild(msgLabel);
#else
	CCSprite* pItemNormal = CCSprite::create("cancel_s.png");
	CCSprite* pItemSelected = CCSprite::create("cancel_s.png");
	pItemSelected->setScale(1.1f);
	CCMenuItemSprite* menuBackBtn = CCMenuItemSprite::create(pItemNormal, pItemSelected, this, menu_selector(QuickBuyLayer::onMenuBtnCallBack));
	menuBackBtn->setTag(QUICK_MENU_CLOSE_TAG);
	menuBackBtn->setPosition(ccp(pBg->getContentSize().width - menuBackBtn->getContentSize().width / 2 - 15,
		pBg->getContentSize().height - menuBackBtn->getContentSize().width / 2 - 5));
	menuBackBtn->setOpacity(0);
	menuBackBtn->runAction(CCSequence::create(CCDelayTime::create(menuDelayTime),CCFadeIn::create(menuShowTime),NULL));
	pItemNormal = CCSprite::create("menu_lingqu.png");
	pItemSelected = CCSprite::create("menu_lingqu.png");
	pItemSelected->setScale(1.05f);
	CCMenuItemSprite *menuLingquBtn = CCMenuItemSprite::create(pItemNormal, pItemSelected, this, menu_selector(QuickBuyLayer::onMenuBtnCallBack));
	menuLingquBtn->setTag(QUICK_MENU_BUY_TAG);
	menuLingquBtn->setPosition(ccp(pBg->getContentSize().width / 2,menuLingquBtn->getContentSize().height / 2 + 10));

	if (GameData::getInstance()->m_nShowQuickBtn != 1){
		scheduleOnce(schedule_selector(QuickBuyLayer::autoBuy), 2.0f);
		menuLingquBtn->setEnabled(false);
		menuLingquBtn->setVisible(false);
	}

	CCMenu *menu = CCMenu::create(menuBackBtn, menuLingquBtn, NULL);
	menu->setPosition(CCPointZero);
	pBg->addChild(menu);

	/*ÃèÊö*/
	CCString *msg = (CCString*)text->objectForKey("libaodetail");
	CCString *bombCount = (CCString*)text->objectForKey("libaoBomb");
	CCString *paintCount = (CCString*)text->objectForKey("libaoPai");
	CCString *reflashCount = (CCString*)text->objectForKey("libaoRef");
	CCString *diaCount = (CCString*)text->objectForKey("libaoDia");
	CCString *detail = CCString::createWithFormat(msg->getCString(),bombCount->getCString(),paintCount->getCString(),reflashCount->getCString(),diaCount->getCString());
	CCString *qq = (CCString*)text->objectForKey("qqser");
	CCString *phone = (CCString*)text->objectForKey("phone");
	CCString *allMsg = CCString::createWithFormat("%s%s\n%s",detail->getCString(),qq->getCString(),phone->getCString());
	CCLabelTTF *msgLabel = CCLabelTTF::create(allMsg->getCString(), "Arial", 11, CCSizeMake(pBg->getContentSize().width / 2,0),kCCTextAlignmentLeft);
	msgLabel->setPosition(ccp(pBg->getContentSize().width / 2 + msgLabel->getContentSize().width / 2,
		menuLingquBtn->getPositionY() + menuLingquBtn->getContentSize().height / 2 + msgLabel->getContentSize().height / 2 + 20));
	int red = GameData::getInstance()->m_nLibaoMsgColorR;
	int green = GameData::getInstance()->m_nLibaoMsgColorG;
	int blue = GameData::getInstance()->m_nLibaoMsgColorB;
	msgLabel->setColor(ccc3(red,green,blue));
	pBg->addChild(msgLabel);
#endif
	return true;
}

void QuickBuyLayer::onMenuBtnCallBack(CCObject* pSender){
	int tag = ((CCNode *)pSender)->getTag();
	if (tag == QUICK_MENU_BUY_TAG){
#if (PAY_DOUBLE_SHOW == 1)
		ConfirmLayer *pConfirmDig = ConfirmLayer::create();
		pConfirmDig->setPayCallBack(m_pCallbackTarget,PAY_TYPE_EXIT_LIBAO,m_pCallback);
		addChild(pConfirmDig,2);
#else
		MyPurchase::sharedPurchase()->payForProducts(m_pCallbackTarget,PAY_TYPE_EXIT_LIBAO,m_pCallback);
#endif
	}else{
		if(m_pCallbackTarget != NULL && m_pCallback != NULL) {
			(m_pCallbackTarget->*m_pCallback)(NULL,PAY_TYPE_EXIT_LIBAO,PAY_RESULT_CANCEL,QUICK_MENU_CLOSE_TAG);
		}
	}
}

void QuickBuyLayer::setCallbackListener(CCObject *target,SEL_CallFuncN3I pListener /* = NULL */){
	m_pCallbackTarget = target;
	m_pCallback = pListener;
}

void QuickBuyLayer::autoBuy(float dt){
	unschedule(schedule_selector(QuickBuyLayer::autoBuy));
#if (PAY_DOUBLE_SHOW == 1)
	ConfirmLayer *pConfirmDig = ConfirmLayer::create();
	pConfirmDig->setPayCallBack(m_pCallbackTarget,PAY_TYPE_EXIT_LIBAO,m_pCallback);
	addChild(pConfirmDig,2);
#else
	MyPurchase::sharedPurchase()->payForProducts(m_pCallbackTarget,PAY_TYPE_EXIT_LIBAO,m_pCallback);
#endif
}