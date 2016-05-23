#include "ShopLayer.h"
#include "VisibleRect.h"
#include "UserInfo.h"
#include "SoundMgr.h"
#include "MyPurchase.h"
#include "ConfirmLayer.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "MyPurchaseIOS.h"
#endif
enum {
    TAG_BACKGROUND = 0,
    TAG_BUY_1,
    TAG_BUY_2,
    TAG_BUY_3,
    TAG_BUY_4,
	TAG_BUY_5
};

ShopLayer::ShopLayer(void)
    : m_pCallback(NULL)
	,m_pCoinLabel(NULL)
{
}


ShopLayer::~ShopLayer(void){
    CC_SAFE_RELEASE_NULL(m_pCallback);
}

bool ShopLayer::init(){
    //////////////////////////////
    // 1. super init first
    if (!CCLayer::init()){
        return false;
    }
	CCScale9Sprite *pBackground = CCScale9Sprite::create("Dialog_bg.png");
    
	pBackground->setAnchorPoint(ccp(0.5f,0.5f));
	pBackground->setPreferredSize(CCSizeMake(DESIGN_WIDTH - 20,DESIGN_HEIGHT - 200));
    CCSize size = pBackground->getContentSize();
    pBackground->setPosition(VisibleRect::center());
    addChild(pBackground, 0, TAG_BACKGROUND);

	CCSprite *pTitleBgSp = CCSprite::create("Dialog_Title.png");
	pTitleBgSp->setPosition(ccp(pBackground->getPositionX(),pBackground->getPositionY() + pBackground->getContentSize().height / 2));
	addChild(pTitleBgSp);

	CCSprite *pTitleSp = CCSprite::create("Title_shop.png");
	pTitleSp->setPosition(ccp(pTitleBgSp->getPositionX(),pTitleBgSp->getPositionY() + pTitleSp->getContentSize().height / 2 + 5));
	addChild(pTitleSp);

    CCSprite *pItemNormal = CCSprite::create("cancel_s.png");
    CCSprite *pItemSelected = CCSprite::create("cancel_s.png");
    CCMenuItem *pClose = CCMenuItemSprite::create(pItemNormal, pItemSelected, this, menu_selector(ShopLayer::close));
    pClose->setPosition(ccp(pTitleSp->getPositionX() + pTitleSp->getContentSize().width * 3 / 2, pTitleSp->getPositionY()));
    pItemSelected->setScale(1.1f);
    pItemSelected->setAnchorPoint(ccp(0.05f, 0.05f));

    CCMenu *pMenu = CCMenu::create(pClose, NULL);
    pMenu->setPosition(CCPointZero);
    addChild(pMenu, 1);

	//第一行
	CCSprite *purchaseBg1 = CCSprite::create("Dialog_Item2.png");
	float preDiv = purchaseBg1->getContentSize().height + 10;
	float purchaseBgPosY = VisibleRect::center().y + preDiv * 2;
#if (PAY_PLUGIN_TYPE_DUOTUI == 1)
	purchaseBgPosY -= preDiv / 2;
#endif
	purchaseBg1->setPosition(ccp(pBackground->getPositionX(),purchaseBgPosY));
	addChild(purchaseBg1);

	CCSprite *pBtnBg = CCSprite::create("menu_money.png");
	CCPoint labelPos = ccp(pBtnBg->getContentSize().width / 2, pBtnBg->getContentSize().height / 2);
	pBtnBg->setPosition(labelPos);

	CCMenuItemFont::setFontSize(30);
	CCDictionary *text = CCDictionary::createWithContentsOfFile(XML_DATA);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    CCMenuItemFont::setFontName("Arial");
#endif
	CCString *price = (CCString*)text->objectForKey("price1");
	CCString *geStr = (CCString*)text->objectForKey("ge");
	CCMenuItemFont *pPurchase = CCMenuItemFont::create(price->getCString(), this, menu_selector(ShopLayer::purchase));
	pPurchase->addChild(pBtnBg);
	pPurchase->setPosition(ccp(purchaseBg1->getPositionX() + purchaseBg1->getContentSize().width / 2 - pBtnBg->getContentSize().width / 2 - 5, 
		purchaseBg1->getPositionY()));
	pPurchase->setContentSize(pBtnBg->getContentSize());
	pPurchase->setAnchorPoint(ccp(0.5f,0.5f));
	pPurchase->getLabel()->setAnchorPoint(ccp(0.5f,0.5f));
	pPurchase->getLabel()->setPosition(labelPos);
	pPurchase->getLabel()->setZOrder(1);
	((CCLabelTTF *)pPurchase->getLabel())->setColor(ccc3(0,0,0));
	pPurchase->setTag(TAG_BUY_1);
	pMenu->addChild(pPurchase);

	CCSprite *diamodSp = CCSprite::create("diamond.png");
	diamodSp->setPosition(ccp(diamodSp->getContentSize().width / 2 + 15,purchaseBg1->getContentSize().height / 2));
	purchaseBg1->addChild(diamodSp);

	CCString *buyCount = (CCString*)text->objectForKey("buy1");
	CCString *showBuyCountString = CCString::createWithFormat("%s%s",buyCount->getCString(),geStr->getCString());

	CCLabelTTF *showBuyCountLabel1 = CCLabelTTF::create(showBuyCountString->getCString(), "Arial", 24);
	showBuyCountLabel1->setPosition(ccp(diamodSp->getPositionX() + diamodSp->getContentSize().width / 2 + showBuyCountLabel1->getContentSize().width / 2 + 7,
		diamodSp->getPositionY()));
	purchaseBg1->addChild(showBuyCountLabel1);

	CCSprite *zengsongSp1 = CCSprite::create("zengsong.png");
	CCSize zengsongSize = zengsongSp1->getContentSize();
	zengsongSp1->setContentSize(zengsongSize * 0.4f);
	zengsongSp1->setScale(0.4f);
	zengsongSp1->setAnchorPoint(ccp(1.4,1.4));
	zengsongSp1->setPosition(ccp(showBuyCountLabel1->getPositionX() + showBuyCountLabel1->getContentSize().width / 2 + zengsongSp1->getContentSize().width / 2 + 12,
		showBuyCountLabel1->getPositionY()));
	purchaseBg1->addChild(zengsongSp1);

	CCString *presentCount = (CCString*)text->objectForKey("pres1");
	CCString *showPresentCountString = CCString::createWithFormat("%s%s",presentCount->getCString(),geStr->getCString());
	CCLabelTTF *showPresentCountLabel1 = CCLabelTTF::create(showPresentCountString->getCString(), "Arial", 24);
	showPresentCountLabel1->setPosition(ccp(zengsongSp1->getPositionX() + zengsongSp1->getContentSize().width / 2 + showPresentCountLabel1->getContentSize().width / 2 + 8,
		diamodSp->getPositionY()));
	purchaseBg1->addChild(showPresentCountLabel1);

	//第二行
	CCSprite *purchaseBg2 = CCSprite::create("Dialog_Item2.png");
	purchaseBg2->setPosition(ccp(pBackground->getPositionX(),purchaseBg1->getPositionY() - preDiv));
	addChild(purchaseBg2);

	pBtnBg = CCSprite::create("menu_money.png");
	pBtnBg->setPosition(labelPos);

	price = (CCString*)text->objectForKey("price2");
	pPurchase = CCMenuItemFont::create(price->getCString(), this, menu_selector(ShopLayer::purchase));
	pPurchase->addChild(pBtnBg);
	pPurchase->setPosition(ccp(purchaseBg2->getPositionX() + purchaseBg2->getContentSize().width / 2 - pBtnBg->getContentSize().width / 2 - 5, 
		purchaseBg2->getPositionY()));
	pPurchase->setContentSize(pBtnBg->getContentSize());
	pPurchase->setAnchorPoint(ccp(0.5f,0.5f));
	pPurchase->getLabel()->setAnchorPoint(ccp(0.5f,0.5f));
	pPurchase->getLabel()->setPosition(labelPos);
	pPurchase->getLabel()->setZOrder(1);
	((CCLabelTTF *)pPurchase->getLabel())->setColor(ccc3(0,0,0));
	pPurchase->setTag(TAG_BUY_2);
	pMenu->addChild(pPurchase);

	diamodSp = CCSprite::create("diamond.png");
	diamodSp->setPosition(ccp(diamodSp->getContentSize().width / 2 + 15,purchaseBg2->getContentSize().height / 2));
	purchaseBg2->addChild(diamodSp);

	buyCount = (CCString*)text->objectForKey("buy2");
	showBuyCountString = CCString::createWithFormat("%s%s",buyCount->getCString(),geStr->getCString());
	CCLabelTTF* showBuyCountLabel2 = CCLabelTTF::create(showBuyCountString->getCString(), "Arial", 24);
	showBuyCountLabel2->setPosition(ccp(showBuyCountLabel1->getPositionX(),
		diamodSp->getPositionY()));
	purchaseBg2->addChild(showBuyCountLabel2);

	CCSprite *zengsongSp = CCSprite::create("zengsong.png");
	zengsongSp->setContentSize(zengsongSize * 0.4f);
	zengsongSp->setScale(0.4f);
	zengsongSp->setAnchorPoint(ccp(1.4,1.4));
	zengsongSp->setPosition(ccp(zengsongSp1->getPositionX(),showBuyCountLabel2->getPositionY()));
	purchaseBg2->addChild(zengsongSp);

	presentCount = (CCString*)text->objectForKey("pres2");
	showPresentCountString = CCString::createWithFormat("%s%s",presentCount->getCString(),geStr->getCString());
	CCLabelTTF* showPresentCountLabel2 = CCLabelTTF::create(showPresentCountString->getCString(), "Arial", 24);
	showPresentCountLabel2->setPosition(ccp(showPresentCountLabel1->getPositionX(),
		diamodSp->getPositionY()));
	purchaseBg2->addChild(showPresentCountLabel2);

	//第三行
	CCSprite *purchaseBg3 = CCSprite::create("Dialog_Item2.png");
	purchaseBg3->setPosition(ccp(pBackground->getPositionX(),purchaseBg2->getPositionY() - preDiv));
	addChild(purchaseBg3);

	pBtnBg = CCSprite::create("menu_money.png");
	pBtnBg->setPosition(labelPos);

	price = (CCString*)text->objectForKey("price3");
	pPurchase = CCMenuItemFont::create(price->getCString(), this, menu_selector(ShopLayer::purchase));
	pPurchase->addChild(pBtnBg);
	pPurchase->setPosition(ccp(purchaseBg3->getPositionX() + purchaseBg3->getContentSize().width / 2 - pBtnBg->getContentSize().width / 2 - 5, 
		purchaseBg3->getPositionY()));
	pPurchase->setContentSize(pBtnBg->getContentSize());
	pPurchase->setAnchorPoint(ccp(0.5f,0.5f));
	pPurchase->getLabel()->setAnchorPoint(ccp(0.5f,0.5f));
	pPurchase->getLabel()->setPosition(labelPos);
	pPurchase->getLabel()->setZOrder(1);
	((CCLabelTTF *)pPurchase->getLabel())->setColor(ccc3(0,0,0));
	pPurchase->setTag(TAG_BUY_3);
	pMenu->addChild(pPurchase);

	diamodSp = CCSprite::create("diamond.png");
	diamodSp->setPosition(ccp(diamodSp->getContentSize().width / 2 + 15,purchaseBg3->getContentSize().height / 2));
	purchaseBg3->addChild(diamodSp);

	buyCount = (CCString*)text->objectForKey("buy3");
	showBuyCountString = CCString::createWithFormat("%s%s",buyCount->getCString(),geStr->getCString());
	CCLabelTTF* showBuyCountLabel3 = CCLabelTTF::create(showBuyCountString->getCString(), "Arial", 24);
	showBuyCountLabel3->setPosition(ccp(showBuyCountLabel1->getPositionX(),
		diamodSp->getPositionY()));
	purchaseBg3->addChild(showBuyCountLabel3);

	zengsongSp = CCSprite::create("zengsong.png");
	zengsongSp->setContentSize(zengsongSize * 0.4f);
	zengsongSp->setScale(0.4f);
	zengsongSp->setAnchorPoint(ccp(1.4,1.4));
	zengsongSp->setPosition(ccp(zengsongSp1->getPositionX(),
		showBuyCountLabel3->getPositionY()));
	purchaseBg3->addChild(zengsongSp);

	presentCount = (CCString*)text->objectForKey("pres3");
	showPresentCountString = CCString::createWithFormat("%s%s",presentCount->getCString(),geStr->getCString());
	CCLabelTTF* showPresentCountLabel3 = CCLabelTTF::create(showPresentCountString->getCString(), "Arial", 24);
	showPresentCountLabel3->setPosition(ccp(showPresentCountLabel1->getPositionX(),
		diamodSp->getPositionY()));
	purchaseBg3->addChild(showPresentCountLabel3);

	//第四行
	CCSprite *purchaseBg4 = CCSprite::create("Dialog_Item2.png");
	purchaseBg4->setPosition(ccp(pBackground->getPositionX(),purchaseBg3->getPositionY() - preDiv));
	addChild(purchaseBg4);

	pBtnBg = CCSprite::create("menu_money.png");
	pBtnBg->setPosition(labelPos);

	price = (CCString*)text->objectForKey("price4");
	pPurchase = CCMenuItemFont::create(price->getCString(), this, menu_selector(ShopLayer::purchase));
	pPurchase->addChild(pBtnBg);
	pPurchase->setPosition(ccp(purchaseBg4->getPositionX() + purchaseBg4->getContentSize().width / 2 - pBtnBg->getContentSize().width / 2 - 5, 
		purchaseBg4->getPositionY()));
	pPurchase->setContentSize(pBtnBg->getContentSize());
	pPurchase->setAnchorPoint(ccp(0.5f,0.5f));
	pPurchase->getLabel()->setAnchorPoint(ccp(0.5f,0.5f));
	pPurchase->getLabel()->setPosition(labelPos);
	pPurchase->getLabel()->setZOrder(1);
	((CCLabelTTF *)pPurchase->getLabel())->setColor(ccc3(0,0,0));
	pPurchase->setTag(TAG_BUY_4);
	pMenu->addChild(pPurchase);

	diamodSp = CCSprite::create("diamond.png");
	diamodSp->setPosition(ccp(diamodSp->getContentSize().width / 2 + 15,purchaseBg4->getContentSize().height / 2));
	purchaseBg4->addChild(diamodSp);

	buyCount = (CCString*)text->objectForKey("buy4");
	showBuyCountString = CCString::createWithFormat("%s%s",buyCount->getCString(),geStr->getCString());
	CCLabelTTF* showBuyCountLabel4 = CCLabelTTF::create(showBuyCountString->getCString(), "Arial", 24);
	showBuyCountLabel4->setPosition(ccp(showBuyCountLabel1->getPositionX(),
		diamodSp->getPositionY()));
	purchaseBg4->addChild(showBuyCountLabel4);

	zengsongSp = CCSprite::create("zengsong.png");
	zengsongSp->setContentSize(zengsongSize * 0.4f);
	zengsongSp->setScale(0.4f);
	zengsongSp->setAnchorPoint(ccp(1.4,1.4));
	zengsongSp->setPosition(ccp(zengsongSp1->getPositionX(),
		showBuyCountLabel4->getPositionY()));
	purchaseBg4->addChild(zengsongSp);

	presentCount = (CCString*)text->objectForKey("pres4");
	showPresentCountString = CCString::createWithFormat("%s%s",presentCount->getCString(),geStr->getCString());
	CCLabelTTF* showPresentCountLabel4 = CCLabelTTF::create(showPresentCountString->getCString(), "Arial", 24);
	showPresentCountLabel4->setPosition(ccp(showPresentCountLabel1->getPositionX(),
		diamodSp->getPositionY()));
	purchaseBg4->addChild(showPresentCountLabel4);
#if (PAY_PLUGIN_TYPE_DUOTUI != 1)
	//第五行
	CCSprite *purchaseBg5 = CCSprite::create("Dialog_Item2.png");
	purchaseBg5->setPosition(ccp(pBackground->getPositionX(),purchaseBg4->getPositionY() - preDiv));
	addChild(purchaseBg5);

	pBtnBg = CCSprite::create("menu_money.png");
	pBtnBg->setPosition(labelPos);

	price = (CCString*)text->objectForKey("price5");
	pPurchase = CCMenuItemFont::create(price->getCString(), this, menu_selector(ShopLayer::purchase));
	pPurchase->addChild(pBtnBg);
	pPurchase->setPosition(ccp(purchaseBg5->getPositionX() + purchaseBg5->getContentSize().width / 2 - pBtnBg->getContentSize().width / 2 - 5, 
		purchaseBg5->getPositionY()));
	pPurchase->setContentSize(pBtnBg->getContentSize());
	pPurchase->setAnchorPoint(ccp(0.5f,0.5f));
	pPurchase->getLabel()->setAnchorPoint(ccp(0.5f,0.5f));
	pPurchase->getLabel()->setPosition(labelPos);
	pPurchase->getLabel()->setZOrder(1);
	((CCLabelTTF *)pPurchase->getLabel())->setColor(ccc3(0,0,0));
	pPurchase->setTag(TAG_BUY_5);
	pMenu->addChild(pPurchase);

	diamodSp = CCSprite::create("diamond.png");
	diamodSp->setPosition(ccp(diamodSp->getContentSize().width / 2 + 15,purchaseBg5->getContentSize().height / 2));
	purchaseBg5->addChild(diamodSp);

	buyCount = (CCString*)text->objectForKey("buy5");
	showBuyCountString = CCString::createWithFormat("%s%s",buyCount->getCString(),geStr->getCString());
	CCLabelTTF* showBuyCountLabel5 = CCLabelTTF::create(showBuyCountString->getCString(), "Arial", 24);
	showBuyCountLabel5->setPosition(ccp(showBuyCountLabel1->getPositionX(),
		diamodSp->getPositionY()));
	purchaseBg5->addChild(showBuyCountLabel5);

	zengsongSp = CCSprite::create("zengsong.png");
	zengsongSp->setContentSize(zengsongSize * 0.4f);
	zengsongSp->setScale(0.4f);
	zengsongSp->setAnchorPoint(ccp(1.4,1.4));
	zengsongSp->setPosition(ccp(zengsongSp1->getPositionX(),
		showBuyCountLabel5->getPositionY()));
	purchaseBg5->addChild(zengsongSp);

	presentCount = (CCString*)text->objectForKey("pres5");
	showPresentCountString = CCString::createWithFormat("%s%s",presentCount->getCString(),geStr->getCString());
	CCLabelTTF* showPresentCountLabel5 = CCLabelTTF::create(showPresentCountString->getCString(), "Arial", 24);
	showPresentCountLabel5->setPosition(ccp(showPresentCountLabel1->getPositionX(),
		diamodSp->getPositionY()));
	purchaseBg5->addChild(showPresentCountLabel5);
#endif
#if (PAY_PLUGIN_TYPE_MILI == 1)
	diamodSp = CCSprite::create("diamond.png");
	diamodSp->setPosition(ccp(purchaseBg5->getPositionX(),
		purchaseBg1->getPositionY() + purchaseBg1->getContentSize().height / 2 + diamodSp->getContentSize().height / 2 + 10));
	addChild(diamodSp);

	presentCount = (CCString*)text->objectForKey("have");
	showBuyCountLabel = CCLabelTTF::create(presentCount->getCString(), "Arial", 24);
	showBuyCountLabel->setPosition(ccp(diamodSp->getPositionX() - showPresentCountLabel->getContentSize().width / 2 - diamodSp->getContentSize().width / 2 - 5,
		diamodSp->getPositionY()));
	showBuyCountLabel->setColor(ccc3(0,0,0));
	addChild(showBuyCountLabel);

	showPresentCountString = CCString::createWithFormat("%d%s",UserInfo::getCoins(),geStr->getCString());
	m_pCoinLabel = CCLabelTTF::create(showPresentCountString->getCString(), "Arial", 24);
	m_pCoinLabel->setColor(ccc3(0,0,0));
	m_pCoinLabel->setPosition(ccp(diamodSp->getPositionX() + diamodSp->getContentSize().width / 2 + showPresentCountLabel->getContentSize().width / 2 + 5,
		showBuyCountLabel->getPositionY()));
	addChild(m_pCoinLabel);

	presentCount = (CCString*)text->objectForKey("msmTips");
	CCLabelTTF* msmLabel = CCLabelTTF::create(presentCount->getCString(), "Arial", 18);
	msmLabel->setPosition(ccp(purchaseBg5->getPositionX(),
		purchaseBg5->getPositionY() - purchaseBg5->getContentSize().height / 2 - diamodSp->getContentSize().height / 2 - 10));
	msmLabel->setColor(ccc3(0,0,0));
	addChild(msmLabel);

	presentCount = (CCString*)text->objectForKey("chargeTips");
	showBuyCountLabel = CCLabelTTF::create(presentCount->getCString(), "Arial", 21);
	showBuyCountLabel->setPosition(ccp(msmLabel->getPositionX(),
		msmLabel->getPositionY() - msmLabel->getContentSize().height / 2 - showBuyCountLabel->getContentSize().height / 2 - 5));
	showBuyCountLabel->setColor(ccc3(0,0,0));
	addChild(showBuyCountLabel);
#elif (PAY_PLUGIN_TYPE_DUOTUI == 1)
	diamodSp = CCSprite::create("diamond.png");
	diamodSp->setPosition(ccp(purchaseBg4->getPositionX(),
		purchaseBg4->getPositionY() - purchaseBg4->getContentSize().height - diamodSp->getContentSize().height / 2 - 10));
	addChild(diamodSp);

	presentCount = (CCString*)text->objectForKey("have");
	CCLabelTTF* showBuyCountLabel = CCLabelTTF::create(presentCount->getCString(), "Arial", 24);
	showBuyCountLabel->setPosition(ccp(diamodSp->getPositionX() - showPresentCountLabel4->getContentSize().width / 2 - diamodSp->getContentSize().width / 2 - 5,
		diamodSp->getPositionY()));
	showBuyCountLabel->setColor(ccc3(0,0,0));
	addChild(showBuyCountLabel);

	showPresentCountString = CCString::createWithFormat("%d%s",UserInfo::getCoins(),geStr->getCString());
	m_pCoinLabel = CCLabelTTF::create(showPresentCountString->getCString(), "Arial", 24);
	m_pCoinLabel->setColor(ccc3(0,0,0));
	m_pCoinLabel->setPosition(ccp(diamodSp->getPositionX() + diamodSp->getContentSize().width / 2 + showPresentCountLabel4->getContentSize().width / 2 + 5,
		showBuyCountLabel->getPositionY()));
	addChild(m_pCoinLabel);

	presentCount = (CCString*)text->objectForKey("chargeTips");
	showBuyCountLabel = CCLabelTTF::create(presentCount->getCString(), "Arial", 21);
	showBuyCountLabel->setPosition(ccp(diamodSp->getPositionX(),
		diamodSp->getPositionY() - diamodSp->getContentSize().height / 2 - showBuyCountLabel->getContentSize().height / 2 - 5));
	showBuyCountLabel->setColor(ccc3(0,0,0));
	addChild(showBuyCountLabel);
#else
	diamodSp = CCSprite::create("diamond.png");
	diamodSp->setPosition(ccp(purchaseBg5->getPositionX(),
		purchaseBg5->getPositionY() - purchaseBg5->getContentSize().height / 2 - diamodSp->getContentSize().height / 2 - 10));
	addChild(diamodSp);

	presentCount = (CCString*)text->objectForKey("have");
	CCLabelTTF* showBuyCountLabel = CCLabelTTF::create(presentCount->getCString(), "Arial", 24);
	showBuyCountLabel->setPosition(ccp(diamodSp->getPositionX() - showPresentCountLabel5->getContentSize().width / 2 - diamodSp->getContentSize().width / 2 - 5,
		diamodSp->getPositionY()));
	showBuyCountLabel->setColor(ccc3(0,0,0));
	addChild(showBuyCountLabel);

	showPresentCountString = CCString::createWithFormat("%d%s",UserInfo::getCoins(),geStr->getCString());
	m_pCoinLabel = CCLabelTTF::create(showPresentCountString->getCString(), "Arial", 24);
	m_pCoinLabel->setColor(ccc3(0,0,0));
	m_pCoinLabel->setPosition(ccp(diamodSp->getPositionX() + diamodSp->getContentSize().width / 2 + showPresentCountLabel5->getContentSize().width / 2 + 5,
		showBuyCountLabel->getPositionY()));
	addChild(m_pCoinLabel);

	presentCount = (CCString*)text->objectForKey("chargeTips");
	showBuyCountLabel = CCLabelTTF::create(presentCount->getCString(), "Arial", 21);
	showBuyCountLabel->setPosition(ccp(diamodSp->getPositionX(),
		diamodSp->getPositionY() - diamodSp->getContentSize().height / 2 - showBuyCountLabel->getContentSize().height / 2 - 5));
	showBuyCountLabel->setColor(ccc3(0,0,0));
	addChild(showBuyCountLabel);
#endif
	

    setPosition(ccp(0, -0.5 * getContentSize().height));
    return true;
}

void ShopLayer::onEnter(){
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);

    runAction(CCMoveBy::create(0.3f, ccp(0, getContentSize().height) / 2));
}

void ShopLayer::onExit(){
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);    

}

bool ShopLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent ){
    return true;
}

void ShopLayer::close( CCObject *pSender ){
    runAction(CCSequence::create(
        CCMoveBy::create(0.3f, ccp(0, -0.5 * getContentSize().height)),
        CCCallFunc::create(this, callfunc_selector(CCNode::removeFromParent)),
        NULL));
}

void ShopLayer::purchase( CCObject *pSender ){
	int tag = ((CCNode *) pSender)->getTag();
	SoundMgr::playEffect(SoundMgr::EFFECT_CLICK);
	MyPayProducts payType = PAY_TYPE_DIAMOND1;
	switch (tag){
	case TAG_BUY_1:
		payType = PAY_TYPE_DIAMOND1;
		break;
	case TAG_BUY_2:
		payType = PAY_TYPE_DIAMOND2;
		break;
	case TAG_BUY_3:
		payType = PAY_TYPE_DIAMOND3;
		break;
	case TAG_BUY_4:
		payType = PAY_TYPE_DIAMOND4;
		break;
	case TAG_BUY_5:
		payType = PAY_TYPE_DIAMOND5;
		break;
	}
#if (PAY_DOUBLE_SHOW == 1)
	ConfirmLayer *pConfirmDig = ConfirmLayer::create();
	pConfirmDig->setPayCallBack(this,(MyPayProducts)payType,callfuncN3I_selector(ShopLayer::payCallBack));
	addChild(pConfirmDig,2);
#else
	MyPurchase::sharedPurchase()->payForProducts(this,(MyPayProducts)payType,callfuncN3I_selector(ShopLayer::payCallBack));
#endif
}

void ShopLayer::setOnUpdateListener( CCCallFunc *pCallback ){
    if (pCallback){
	    m_pCallback = pCallback;
        m_pCallback->retain();
    }
}

void ShopLayer::onPayResult(){
    if (m_pCallback){
        m_pCallback->execute();
    }
}

void ShopLayer::payCallBack(CCNode* nouse, int payType, int payResult,int payIntNoUse){
	if (payResult != PAY_RESULT_SUCCESS){
		return;
	}
	int orderCoins = 0;
	CCDictionary *text = CCDictionary::createWithContentsOfFile(XML_DATA);
	if (m_pCoinLabel){
		CCString *geStr = (CCString*)text->objectForKey("ge");
		CCString *coinCoinString = CCString::createWithFormat("%d%s",UserInfo::getCoins(),geStr->getCString());
		m_pCoinLabel->setString(coinCoinString->getCString());
	}
	if (m_pCallback){
		m_pCallback->execute();
	}
}