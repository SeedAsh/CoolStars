#include "ExitLayer.h"
#include "VisibleRect.h"
#include "MyPurchase.h"
#include "ConfirmLayer.h"
USING_NS_CC;

bool Exit::init(){
	float btnShowTime = 1.0f;
	float btnFadeInTime = 1.0f;
	setKeypadEnabled(true);
	CCSprite* pBg = CCSprite::create("exitbg.png");
	pBg->setPosition(VisibleRect::center());
	addChild(pBg);

	CCDictionary *text = CCDictionary::createWithContentsOfFile(XML_DATA);
#if (PAY_PLUGIN_TYPE_XINYINHE == 1)
	CCString *msg = (CCString*)text->objectForKey("libao");//
	CCLabelTTF *qqmsgLabel = CCLabelTTF::create(msg->getCString(), "Arial", 26);
	qqmsgLabel->setPosition(ccp(pBg->getContentSize().width / 2,pBg->getContentSize().height / 4 + qqmsgLabel->getContentSize().height / 2));
	qqmsgLabel->setColor(ccc3(0,0,0));
	pBg->addChild(qqmsgLabel);
#elif ((PAY_PLUGIN_TYPE_SKYMM == 1) || (PAY_PLUGIN_TYPE_MM == 1) || (PAY_PLUGIN_TYPE_MM_STRONG == 1) || (PAY_PLUGIN_TYPE_SKYMMSTRONG == 1))
	CCString *msg = (CCString*)text->objectForKey("libaodetail");
	CCString *bombCount = (CCString*)text->objectForKey("libaoBomb");
	CCString *paintCount = (CCString*)text->objectForKey("libaoPai");
	CCString *reflashCount = (CCString*)text->objectForKey("libaoRef");
	CCString *diaCount = (CCString*)text->objectForKey("libaoDia");
	CCString *detail = CCString::createWithFormat(msg->getCString(),bombCount->getCString(),paintCount->getCString(),reflashCount->getCString(),diaCount->getCString());
	CCLabelTTF *msgLabel = CCLabelTTF::create(detail->getCString(), "Arial", 11, CCSizeMake(pBg->getContentSize().width - 80,0),kCCTextAlignmentCenter);
	msgLabel->setPosition(ccp(pBg->getContentSize().width / 2,
		msgLabel->getContentSize().height * 3 - 11));
	msgLabel->setColor(ccc3(41,55,188));
	pBg->addChild(msgLabel);
#else
	CCString *msg = (CCString*)text->objectForKey("qqser");//qq客服
	CCLabelTTF *qqmsgLabel = CCLabelTTF::create(msg->getCString(), "Arial", 11);
	qqmsgLabel->setPosition(ccp(pBg->getContentSize().width / 2,pBg->getContentSize().height / 4 + qqmsgLabel->getContentSize().height));
	qqmsgLabel->setColor(ccc3(41,55,188));
	pBg->addChild(qqmsgLabel);

	msg = (CCString*)text->objectForKey("phone");//客服电话
	CCLabelTTF *phoneMsgLabel = CCLabelTTF::create(msg->getCString(), "Arial", 11);
	phoneMsgLabel->setPosition(ccp(qqmsgLabel->getPositionX(),qqmsgLabel->getPositionY() - qqmsgLabel->getContentSize().height - 5));
	phoneMsgLabel->setColor(qqmsgLabel->getColor());
	pBg->addChild(phoneMsgLabel);

	msg = (CCString*)text->objectForKey("libao");//礼包金额
	CCLabelTTF *libaoMsgLabel = CCLabelTTF::create(msg->getCString(), "Arial", 11);
	libaoMsgLabel->setPosition(ccp(phoneMsgLabel->getPositionX(),phoneMsgLabel->getPositionY() - phoneMsgLabel->getContentSize().height - 5));
	libaoMsgLabel->setColor(qqmsgLabel->getColor());
	pBg->addChild(libaoMsgLabel);
#endif
	CCSprite* pItemNormal = CCSprite::create("cancel_s.png");
	CCSprite* pItemSelected = CCSprite::create("cancel_s.png");
	pItemSelected->setScale(1.1f);
	CCMenuItemSprite* menuCancelBtn = CCMenuItemSprite::create(pItemNormal, pItemSelected, this, menu_selector(Exit::onMenuBtnCallBack));
	menuCancelBtn->setTag(EXIT_MENU_CANCEL_TAG);
	menuCancelBtn->setPosition(ccp(pBg->getContentSize().width - menuCancelBtn->getContentSize().width / 2 - 5,
		pBg->getContentSize().height / 2 + 10));
	menuCancelBtn->setOpacity(0);
	menuCancelBtn->runAction(CCSequence::create(CCDelayTime::create(btnShowTime),CCFadeIn::create(btnFadeInTime),NULL));

	pItemNormal = CCSprite::create("exit_lq.png");
	pItemSelected = CCSprite::create("exit_lq.png");
	pItemSelected->setScale(1.05f);
	CCMenuItemSprite *menuLingquBtn = CCMenuItemSprite::create(pItemNormal, pItemSelected, this, menu_selector(Exit::onMenuBtnCallBack));
	menuLingquBtn->setTag(EXIT_MENU_BUY_TAG);
	menuLingquBtn->setPosition(ccp(pBg->getContentSize().width - menuLingquBtn->getContentSize().width,
		menuLingquBtn->getContentSize().height / 2 + 10));

	pItemNormal = CCSprite::create("exit.png");
	pItemSelected = CCSprite::create("exit.png");
	pItemSelected->setScale(1.05f);
	CCMenuItemSprite *menuExitBtn = CCMenuItemSprite::create(pItemNormal, pItemSelected, this, menu_selector(Exit::onMenuBtnCallBack));
	menuExitBtn->setTag(EXIT_MENU_CLOSE_TAG);
	menuExitBtn->setPosition(ccp(menuExitBtn->getContentSize().width, menuLingquBtn->getPositionY()));
	menuExitBtn->setOpacity(0);
	menuExitBtn->runAction(CCSequence::create(CCDelayTime::create(btnShowTime),CCFadeIn::create(btnFadeInTime),NULL));

	CCMenu *menu = CCMenu::create(menuCancelBtn, menuLingquBtn,menuExitBtn, NULL);
	menu->setPosition(CCPointZero);
	pBg->addChild(menu);
	return true;
}

void Exit::onEnter(){
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void Exit::onExit(){
	CCLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);    
}

bool Exit::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent ){
	return true;
}

void Exit::onMenuBtnCallBack(CCObject* pSender){
	int tag = ((CCMenuItemSprite*)pSender)->getTag();
	if (tag == EXIT_MENU_CLOSE_TAG){
		exitGame();
	}else if (tag == EXIT_MENU_BUY_TAG){
#if (PAY_DOUBLE_SHOW == 1)
		ConfirmLayer *pConfirmDig = ConfirmLayer::create();
		pConfirmDig->setPayCallBack(this,PAY_TYPE_EXIT_LIBAO,callfuncN3I_selector(Exit::payCallBack));
		addChild(pConfirmDig,2);
#else
		MyPurchase::sharedPurchase()->payForProducts(this,(MyPayProducts)PAY_TYPE_EXIT_LIBAO,callfuncN3I_selector(Exit::payCallBack));
#endif
	}else{
		removeFromParent();
	}
}

void Exit::payCallBack(CCNode* nouse, int payType, int payResult,int payIntNoUse){
	if (payResult != PAY_RESULT_SUCCESS){
		return;
	}
	removeFromParent();
}

void Exit::exitGame(){
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

void Exit::keyBackClicked(){
  removeFromParent();
}