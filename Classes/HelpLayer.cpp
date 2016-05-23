#include "HelpLayer.h"
#include "VisibleRect.h"
#include "GameData.h"
#include "SoundMgr.h"

HelpLayer::HelpLayer(void){

}


HelpLayer::~HelpLayer(void){

}

bool HelpLayer::init(){
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init()){
		return false;
	}
	CCScale9Sprite *pBackground = CCScale9Sprite::create("Dialog_bg.png");

	pBackground->setAnchorPoint(ccp(0.5f,0.5f));
	CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
	float scale = frameSize.width / DESIGN_WIDTH;
	float newScaleY = 1.0f;
	if (scale > 0){
		float scaleY = frameSize.height / DESIGN_HEIGHT;
		if (scaleY > scale){
			newScaleY = scaleY / scale;
		}		
	}	
	pBackground->setPreferredSize(CCSizeMake(DESIGN_WIDTH - 20,(DESIGN_HEIGHT - 130) * newScaleY));
	CCSize size = pBackground->getContentSize();
	pBackground->setPosition(VisibleRect::center());
	addChild(pBackground);

	CCSprite *pTitleBgSp = CCSprite::create("Dialog_Title.png");
	pTitleBgSp->setPosition(ccp(pBackground->getPositionX(),pBackground->getPositionY() + pBackground->getContentSize().height / 2));
	addChild(pTitleBgSp);

	CCSprite *pTitleSp = CCSprite::create("Title_Help.png");
	pTitleSp->setPosition(ccp(pTitleBgSp->getPositionX(),pTitleBgSp->getPositionY() + pTitleSp->getContentSize().height / 2 + 5));
	addChild(pTitleSp);

	CCSprite *pItemNormal = CCSprite::create("cancel_s.png");
	CCSprite *pItemSelected = CCSprite::create("cancel_s.png");
	CCMenuItem *pClose = CCMenuItemSprite::create(pItemNormal, pItemSelected, this, menu_selector(HelpLayer::close));
	pClose->setPosition(ccp(pTitleSp->getPositionX() + pTitleSp->getContentSize().width * 3 / 2, pTitleSp->getPositionY()));
	pItemSelected->setScale(1.1f);
	pItemSelected->setAnchorPoint(ccp(0.05f, 0.05f));

	CCMenu *pMenu = CCMenu::create(pClose, NULL);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu, 1);
	CCDictionary *text = CCDictionary::createWithContentsOfFile(XML_DATA);
	CCString *msg = (CCString*)text->objectForKey("rule");
	CCLabelTTF *msgLabel = CCLabelTTF::create(msg->getCString(), "Arial", 21,CCSizeMake(DESIGN_WIDTH - 40, 0),kCCTextAlignmentLeft);
	msgLabel->setColor(ccc3(0,0,0));
	msgLabel->setPosition(ccp(pTitleBgSp->getPositionX(),pTitleBgSp->getPositionY() - pTitleBgSp->getContentSize().height / 2 - msgLabel->getContentSize().height / 2 - 5));
	addChild(msgLabel);

	CCSprite *phSp = CCSprite::create("Help_1.png");
	phSp->setPosition(ccp(msgLabel->getPositionX(),msgLabel->getPositionY() - msgLabel->getContentSize().height / 2 - phSp->getContentSize().height / 2 - 3));
	addChild(phSp);

	msg = (CCString*)text->objectForKey("scoreTips");
	msgLabel = CCLabelTTF::create(msg->getCString(), "Arial", 21,CCSizeMake(DESIGN_WIDTH - 40, 0),kCCTextAlignmentCenter);
	msgLabel->setColor(ccc3(0,0,0));
	msgLabel->setPosition(ccp(phSp->getPositionX(),phSp->getPositionY() - phSp->getContentSize().height / 2 - msgLabel->getContentSize().height / 2 - 10));
	addChild(msgLabel);

	phSp = CCSprite::create("Help_2.png");
	phSp->setPosition(ccp(msgLabel->getPositionX(),msgLabel->getPositionY() - msgLabel->getContentSize().height / 2 - phSp->getContentSize().height / 2 - 3));
	addChild(phSp);

	msg = (CCString*)text->objectForKey("pro");
	msgLabel = CCLabelTTF::create(msg->getCString(), "Arial", 21,CCSizeMake(DESIGN_WIDTH - 40, 0),kCCTextAlignmentLeft);
	msgLabel->setColor(ccc3(0,0,0));
	msgLabel->setPosition(ccp(pBackground->getPositionX() - pBackground->getContentSize().width / 2 + msgLabel->getContentSize().width / 2 + 10,
		phSp->getPositionY() - phSp->getContentSize().height / 2 - msgLabel->getContentSize().height / 2 - 3));
	addChild(msgLabel);

	CCSprite* bombSp = CCSprite::create("Props_Bomb.png");
	bombSp->setPosition(ccp(pBackground->getPositionX() - pBackground->getContentSize().width / 2 + bombSp->getContentSize().width / 2 + 10,
		msgLabel->getPositionY() - msgLabel->getContentSize().height / 2 - bombSp->getContentSize().height / 2 - 3));
	addChild(bombSp);

	msg = (CCString*)text->objectForKey("bomb");
	msgLabel = CCLabelTTF::create(msg->getCString(), "Arial", 18,CCSizeMake(DESIGN_WIDTH - 40, 0),kCCTextAlignmentLeft);
	msgLabel->setColor(ccc3(0,0,0));
	msgLabel->setPosition(ccp(bombSp->getPositionX() + bombSp->getContentSize().width / 2 + msgLabel->getContentSize().width / 2 + 5,
		bombSp->getPositionY() + 13));
	addChild(msgLabel);

	msg = (CCString*)text->objectForKey("useCoin");
	CCString *showUseString = CCString::createWithFormat(msg->getCString(),GameData::getInstance()->m_nBombUseCoin);
	CCLabelTTF *showUseLabel = CCLabelTTF::create(showUseString->getCString(), "Arial", 14,CCSizeMake(DESIGN_WIDTH - 40, 0),kCCTextAlignmentLeft);
	showUseLabel->setColor(ccc3(0,0,0));
	showUseLabel->setPosition(ccp(bombSp->getPositionX() + bombSp->getContentSize().width / 2 + showUseLabel->getContentSize().width / 2 + 5,
		msgLabel->getPositionY() - msgLabel->getContentSize().height / 2 - showUseLabel->getContentSize().height / 2 - 2));
	addChild(showUseLabel);

	CCSprite *paintSp = CCSprite::create("Props_Paint.png");
	paintSp->setPosition(ccp(pBackground->getPositionX() - pBackground->getContentSize().width / 2 + paintSp->getContentSize().width / 2 + 10,
		bombSp->getPositionY() - bombSp->getContentSize().height / 2 - paintSp->getContentSize().height / 2 - 10));
	addChild(paintSp);

	msg = (CCString*)text->objectForKey("shua");
	msgLabel = CCLabelTTF::create(msg->getCString(), "Arial", 18,CCSizeMake(DESIGN_WIDTH - 40, 0),kCCTextAlignmentLeft);
	msgLabel->setColor(ccc3(0,0,0));
	msgLabel->setPosition(ccp(paintSp->getPositionX() + paintSp->getContentSize().width / 2 + msgLabel->getContentSize().width / 2 + 5,
		paintSp->getPositionY() + 13));
	addChild(msgLabel);
	
	msg = (CCString*)text->objectForKey("useCoin");
	showUseString = CCString::createWithFormat(msg->getCString(),GameData::getInstance()->m_nPaintUseCoin);
	showUseLabel = CCLabelTTF::create(showUseString->getCString(), "Arial", 14,CCSizeMake(DESIGN_WIDTH - 40, 0),kCCTextAlignmentLeft);
	showUseLabel->setColor(ccc3(0,0,0));
	showUseLabel->setPosition(ccp(paintSp->getPositionX() + paintSp->getContentSize().width / 2 + showUseLabel->getContentSize().width / 2 + 5,
		msgLabel->getPositionY() - msgLabel->getContentSize().height / 2 - showUseLabel->getContentSize().height / 2 - 2));
	addChild(showUseLabel);

	CCSprite *rainSp = CCSprite::create("Props_Rainbow.png");
	rainSp->setPosition(ccp(pBackground->getPositionX() - pBackground->getContentSize().width / 2 + rainSp->getContentSize().width / 2 + 10,
		paintSp->getPositionY() - paintSp->getContentSize().height / 2 - rainSp->getContentSize().height / 2 - 10));
	addChild(rainSp);

	msg = (CCString*)text->objectForKey("zhuan");
	msgLabel = CCLabelTTF::create(msg->getCString(), "Arial", 18,CCSizeMake(DESIGN_WIDTH - 40, 0),kCCTextAlignmentLeft);
	msgLabel->setColor(ccc3(0,0,0));
	msgLabel->setPosition(ccp(rainSp->getPositionX() + rainSp->getContentSize().width / 2 + msgLabel->getContentSize().width / 2 + 5,
		rainSp->getPositionY() + 13));
	addChild(msgLabel);

	msg = (CCString*)text->objectForKey("useCoin");
	showUseString = CCString::createWithFormat(msg->getCString(),GameData::getInstance()->m_nReflashUseCoin);
	showUseLabel = CCLabelTTF::create(showUseString->getCString(), "Arial", 14,CCSizeMake(DESIGN_WIDTH - 40, 0),kCCTextAlignmentLeft);
	showUseLabel->setColor(ccc3(0,0,0));
	showUseLabel->setPosition(ccp(rainSp->getPositionX() + rainSp->getContentSize().width / 2 + showUseLabel->getContentSize().width / 2 + 5,
		msgLabel->getPositionY() - msgLabel->getContentSize().height / 2 - showUseLabel->getContentSize().height / 2 - 2));
	addChild(showUseLabel);

	msg = (CCString*)text->objectForKey("quese");
	msgLabel = CCLabelTTF::create(msg->getCString(), "Arial", 21,CCSizeMake(DESIGN_WIDTH - 40, 0),kCCTextAlignmentLeft);
	msgLabel->setColor(ccc3(0,0,0));
	msgLabel->setPosition(ccp(pBackground->getPositionX() - pBackground->getContentSize().width / 2 + msgLabel->getContentSize().width / 2 + 10,
		rainSp->getPositionY() - rainSp->getContentSize().height / 2 - 25));
	addChild(msgLabel);
	
	msg = (CCString*)text->objectForKey("phone");
	showUseLabel = CCLabelTTF::create(msg->getCString(), "Arial", 21,CCSizeMake(DESIGN_WIDTH - 40, 0),kCCTextAlignmentLeft);
	showUseLabel->setColor(ccc3(0,0,0));
	showUseLabel->setPosition(ccp(pBackground->getPositionX() - pBackground->getContentSize().width / 2 + showUseLabel->getContentSize().width / 2 + 10,
		msgLabel->getPositionY() - msgLabel->getContentSize().height / 2 - showUseLabel->getContentSize().height / 2 - 2));
	addChild(showUseLabel);

	msg = (CCString*)text->objectForKey("qq");
	msgLabel = CCLabelTTF::create(msg->getCString(), "Arial", 21,CCSizeMake(DESIGN_WIDTH - 40, 0),kCCTextAlignmentLeft);
	msgLabel->setColor(ccc3(0,0,0));
	msgLabel->setPosition(ccp(pBackground->getPositionX() - pBackground->getContentSize().width / 2 + msgLabel->getContentSize().width / 2 + 10,
		showUseLabel->getPositionY() - showUseLabel->getContentSize().height / 2 - msgLabel->getContentSize().height / 2 - 2));
	addChild(msgLabel);

	setPosition(ccp(0, -0.5 * getContentSize().height));
	return true;
}

bool HelpLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	return true;
}

void HelpLayer::onEnter(){
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
	runAction(CCMoveBy::create(0.3f, ccp(0, getContentSize().height - 80) / 2));
}

void HelpLayer::onExit(){
	CCLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);    
}

void HelpLayer::close( CCObject *pSender ){
	SoundMgr::playEffect(SoundMgr::EFFECT_CLICK);
	runAction(CCSequence::create(
		CCMoveBy::create(0.3f, ccp(0, -0.5 * getContentSize().height)),
		CCCallFunc::create(this, callfunc_selector(CCNode::removeFromParent)),
		NULL));
}