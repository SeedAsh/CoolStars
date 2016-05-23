#include "PanelLayer.h"
#include "VisibleRect.h"
#include "UserInfo.h"
#include "GameData.h"
#include "SoundMgr.h"

#define Z_ORDER_PROPS_BG 0
#define Z_ORDER_PROPS (Z_ORDER_PROPS_BG + 1)
#define Z_ORDER_TITLE_BG (Z_ORDER_PROPS + 1)
#define Z_ORDER_TITLE (Z_ORDER_TITLE_BG + 1)
#define Z_ORDER_REWARD Z_ORDER_TITLE

#define SELECTED_SKILL_OFFSET 20

PanelLayer::PanelLayer(void)
    : m_pStageLabel(NULL),
      m_pTargetLabel(NULL),
      m_pScoreLabel(NULL),
	  m_pStepLabel(NULL),
      m_pScoreHint(NULL),
      m_pStageClear(NULL),
      m_pCoins(NULL),
      m_pSelectedSkill(NULL),
	  m_pBombLabel(NULL),
	  m_pPaintLabel(NULL),
	  m_pReflashLabel(NULL),
	  m_nTargetCoins(0),
	  m_nCurrentCoins(0),
	  m_nUpdateCoinsInterval(UPDATE_COINS_TIME / 10),
      m_nCurrentScore(0)
{
    m_obOnClickListener.pTarget = NULL;
    m_obOnClickListener.pCallback = NULL;
}


PanelLayer::~PanelLayer(void)
{
    CC_SAFE_RELEASE_NULL(m_pStageLabel);
    CC_SAFE_RELEASE_NULL(m_pTargetLabel);
    CC_SAFE_RELEASE_NULL(m_pScoreLabel);
	CC_SAFE_RELEASE_NULL(m_pStepLabel);
    CC_SAFE_RELEASE_NULL(m_obOnClickListener.pTarget);
    CC_SAFE_RELEASE_NULL(m_pScoreHint);
    CC_SAFE_RELEASE_NULL(m_pStageClear);
    CC_SAFE_RELEASE_NULL(m_pCoins);
    CC_SAFE_RELEASE_NULL(m_pSelectedSkill);
}

PanelLayer * PanelLayer::create(){
    PanelLayer *pRet = new PanelLayer();
    if (pRet && pRet->init()){
        pRet->autorelease();
        return pRet;
    }else{
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool PanelLayer::init(){
    if (!CCLayer::init()){
        return false;
    }

    this->setTouchEnabled(true);

    CCPoint top = VisibleRect::top();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCDictionary *text = CCDictionary::createWithContentsOfFile(XML_DATA);
	CCString *msg = (CCString*)text->objectForKey("hight");//历史最高分

	CCLabelTTF* hightScore = CCLabelTTF::create(msg->getCString(), "Arial", 21);
	hightScore->setColor(ccWHITE);
	CCSize size = hightScore->getContentSize();
	CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
	float scale = frameSize.width / DESIGN_WIDTH;
	float difY = (frameSize.height / scale - DESIGN_HEIGHT) / 2;
	if (difY < 0){
		difY = 0;
	}
	hightScore->setPosition(ccp(visibleSize.width * 0.6f, visibleSize.height - size.height - difY));
	this->addChild(hightScore, Z_ORDER_TITLE);

	char *label = new char[16];
	sprintf(label, "%d", UserInfo::getBestScore());
	CCLabelTTF* bestSocre = CCLabelTTF::create(label, "Arial", 21);
	bestSocre->setColor(ccWHITE);
	bestSocre->setPosition(ccp(hightScore->getPositionX() + size.width / 2 + bestSocre->getContentSize().width,
		hightScore->getPositionY()));
	this->addChild(bestSocre, Z_ORDER_TITLE);
	CC_SAFE_DELETE_ARRAY(label);
	
	msg = (CCString*)text->objectForKey("lev");
    CCLabelTTF* pStage = CCLabelTTF::create(msg->getCString(), "Arial", 21);
    pStage->setColor(ccWHITE);
    size = pStage->getContentSize();
    pStage->setPosition(ccp(size.width / 2 + 10, hightScore->getPositionY() - hightScore->getContentSize().height - pStage->getContentSize().height));
    this->addChild(pStage, Z_ORDER_TITLE);

    m_pStageLabel = CCLabelTTF::create("1", "Arial", 21);
	m_pStageLabel->setColor((ccc3(255,255,255)));
    m_pStageLabel->retain();
    m_pStageLabel->setPosition(ccp(pStage->getPositionX() + size.width + 10, pStage->getPositionY()));
    this->addChild(m_pStageLabel, Z_ORDER_TITLE);

	msg = (CCString*)text->objectForKey("tar");
    CCLabelTTF *pTarget = CCLabelTTF::create(msg->getCString(), "Arial", 21);
    pTarget->setColor(ccWHITE);
    size = pTarget->getContentSize();
    pTarget->setPosition(ccp(visibleSize.width * 2 / 5, pStage->getPositionY()));
    this->addChild(pTarget, Z_ORDER_TITLE);

    m_pTargetLabel = CCLabelTTF::create("1000", "Arial", 21);
    m_pTargetLabel->setColor(ccWHITE);
    m_pTargetLabel->retain();
    m_pTargetLabel->setPosition(ccp(pTarget->getPositionX() + size.width, pStage->getPositionY()));
    this->addChild(m_pTargetLabel, Z_ORDER_TITLE);

	//当前金币数量
	CCSprite* currentCoinBg = CCSprite::create("dialog_item.png");
	currentCoinBg->setPosition(ccp(VisibleRect::right().x - currentCoinBg->getContentSize().width / 2 - 10, pTarget->getPositionY()));
	this->addChild(currentCoinBg, Z_ORDER_PROPS_BG);

	//步数
	msg = (CCString*)text->objectForKey("step");
	pTarget = CCLabelTTF::create(msg->getCString(), "Arial", 21);
	pTarget->setColor(ccWHITE);
	size = pTarget->getContentSize();
	pTarget->setPosition(ccp(visibleSize.width * 0.1f, hightScore->getPositionY()));
	this->addChild(pTarget, Z_ORDER_TITLE);

	m_pStepLabel = CCLabelTTF::create("10", "Arial", 21);
	m_pStepLabel->setColor(ccWHITE);
	m_pStepLabel->retain();
	m_pStepLabel->setPosition(ccp(pTarget->getPositionX() + size.width, hightScore->getPositionY()));
	this->addChild(m_pStepLabel, Z_ORDER_TITLE);

	CCSprite* diamondSp = CCSprite::create("diamond.png");
	diamondSp->setPosition(ccp(diamondSp->getContentSize().width / 4,currentCoinBg->getContentSize().height / 2));
	currentCoinBg->addChild(diamondSp);

	CCSprite *pBuyItemNormal = CCSprite::create("coin_add.png");
	CCSprite *pBuyItemSelected = CCSprite::create("coin_add.png");
	pBuyItemSelected->setScale(1.1f);
	pBuyItemSelected->setAnchorPoint(ccp(0.05f, 0.05f));
	CCMenuItem *pBuy = CCMenuItemSprite::create(pBuyItemNormal, pBuyItemSelected, this, menu_selector(PanelLayer::menuCallback));
	pBuy->setPosition(ccp(currentCoinBg->getPositionX() + currentCoinBg->getContentSize().width / 2 - pBuy->getContentSize().width / 2,
		currentCoinBg->getPositionY()));
	pBuy->setTag(TAG_SHOP);

	CCNode *pBatchNode = CCNode::create();
    this->addChild(pBatchNode, Z_ORDER_PROPS);

    CCSprite *pItemNormal = CCSprite::create("Item_pause.png");
    CCSprite *pItemSelected = CCSprite::create("Item_pause.png");
    CCMenuItem *pPause = CCMenuItemSprite::create(pItemNormal, pItemSelected, this, menu_selector(PanelLayer::menuCallback));
    pItemSelected->setScale(1.1f);
    pItemSelected->setAnchorPoint(ccp(0.05f, 0.05f));
    pPause->setTag(TAG_PAUSE_BUTTON);
    size = pPause->getContentSize();
    pPause->setPosition(ccp(size.width / 2 + 4, 
		pStage->getPositionY() - pStage->getContentSize().height / 2 - pPause->getContentSize().height));
	 
	m_pScoreLabel = CCLabelTTF::create("0", "Arial", 32);
	m_pScoreLabel->setColor(ccWHITE);
	m_pScoreLabel->retain();
	m_pScoreLabel->setPosition(ccp(VisibleRect::center().x - 16 * 3, pPause->getPositionY()));
	this->addChild(m_pScoreLabel, Z_ORDER_TITLE);

    CCMenu *pMenu = CCMenu::create(pPause, NULL);
    pMenu->setTouchPriority(1);
    pMenu->setPosition(CCPointZero);
    addChild(pMenu, Z_ORDER_PROPS, TAG_MENU);

    float leftX = VisibleRect::center().x;
    float propsY = pPause->getPositionY();

    pItemNormal = CCSprite::create("Props_Bomb.png");
    pItemSelected = CCSprite::create("Props_Bomb.png");
    CCMenuItemSprite* pMagic = CCMenuItemSprite::create(pItemNormal, pItemSelected, this, menu_selector(PanelLayer::menuCallback));
    pMagic->setTag(TAG_BOMB);
    pMagic->setPosition(ccp(leftX + 108, propsY));
    pMenu->addChild(pMagic);
	if (GameData::getInstance()->m_nUseProType != USE_PRO_TYPE_COINONLY){
		m_pBombLabel = CCLabelTTF::create(CCString::createWithFormat("%d",UserInfo::getProCount(USERINFO_PRO_TYPE_BOMB))->getCString(), "Arial", 18);
		m_pBombLabel->setPosition(ccp(pMagic->getContentSize().width - m_pBombLabel->getContentSize().width / 2,0));
		pMagic->addChild(m_pBombLabel);
	}
    leftX = pMagic->getPositionX();
    pItemNormal = CCSprite::create("Props_Paint.png");
    pItemSelected = CCSprite::create("Props_Paint.png");
    pMagic = CCMenuItemSprite::create(pItemNormal, pItemSelected, this, menu_selector(PanelLayer::menuCallback));
    pItemSelected->setScale(1.2f);
    pItemSelected->setAnchorPoint(ccp(0.05f, 0.05f));
    pMagic->setTag(TAG_PAINT);
    pMagic->setPosition(ccp(leftX + 54, propsY));
    pMenu->addChild(pMagic);
	if (GameData::getInstance()->m_nUseProType != USE_PRO_TYPE_COINONLY){
		m_pPaintLabel = CCLabelTTF::create(CCString::createWithFormat("%d",UserInfo::getProCount(USERINFO_PRO_TYPE_PAINT))->getCString(), "Arial", 18);
		m_pPaintLabel->setPosition(ccp(pMagic->getContentSize().width- m_pPaintLabel->getContentSize().width / 2,0));
		pMagic->addChild(m_pPaintLabel);
	}

    m_pCoins = CCLabelTTF::create("0", "Arial", 21);
    m_pCoins->setColor(ccWHITE);
    m_pCoins->retain();
    m_pCoins->setPosition(currentCoinBg->getPosition());
    addChild(m_pCoins, Z_ORDER_TITLE);

    leftX = pMagic->getPositionX();
    pItemNormal = CCSprite::create("Props_Rainbow.png");
    pItemSelected = CCSprite::create("Props_Rainbow.png");
    pMagic = CCMenuItemSprite::create(pItemNormal, pItemSelected, this, menu_selector(PanelLayer::menuCallback));
    pItemSelected->setScale(1.2f);
    pItemSelected->setAnchorPoint(ccp(0.05f, 0.05f));
    pMagic->setTag(TAG_RAINBOW);
    pMagic->setPosition(ccp(leftX + 54, propsY));
    pMenu->addChild(pMagic);
	if (GameData::getInstance()->m_nUseProType != USE_PRO_TYPE_COINONLY){
		m_pReflashLabel = CCLabelTTF::create(CCString::createWithFormat("%d",UserInfo::getProCount(USERINFO_PRO_TYPE_REFLASH))->getCString(), "Arial", 18);
		m_pReflashLabel->setPosition(ccp(pMagic->getContentSize().width - m_pReflashLabel->getContentSize().width / 2,0));
		pMagic->addChild(m_pReflashLabel);
	}
	pMenu->addChild(pBuy);
    m_pScoreHint = CCLabelTTF::create("", "Arial", 21);
    m_pScoreHint->retain();
    m_pScoreHint->setPosition(ccp(VisibleRect::center().x,
        m_pTargetLabel->getPositionY() - size.height - m_pScoreHint->getContentSize().height - 80));
    m_pScoreHint->setColor(ccWHITE);
    this->addChild(m_pScoreHint, Z_ORDER_TITLE);

    m_pStageClear = CCSprite::create("stage_clear.png");
    m_pStageClear->retain();
    m_pStageClear->setVisible(false);
    size = m_pStageClear->getContentSize() / 3.5;
    m_obStageClearPosition.x = visibleSize.width - size.width / 2;
    m_obStageClearPosition.y = m_pScoreHint->getPositionY() - pStage->getContentSize().height / 2 - size.height / 2 - 50;
    this->addChild(m_pStageClear);

    return true;
}

void PanelLayer::ccTouchesBegan( CCSet *pTouches, CCEvent *pEvent ){

}

void PanelLayer::ccTouchesMoved( CCSet *pTouches, CCEvent *pEvent ){

}

void PanelLayer::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent ){

}

void PanelLayer::ccTouchesCancelled( CCSet *pTouches, CCEvent *pEvent ){

}

void PanelLayer::setBestScore( int bestScore ){

}

void PanelLayer::setStage( int stage ){
    char *label = new char[16];
    sprintf(label, "%d", stage);
    m_pStageLabel->setString(label);
    CC_SAFE_DELETE_ARRAY(label);
}

void PanelLayer::setTarget( int target ){
    char *label = new char[16];
    sprintf(label, "%d", target);
    m_pTargetLabel->setString(label);
    CC_SAFE_DELETE_ARRAY(label);
}

void PanelLayer::setStep(int step){
	char *label = new char[16];
	sprintf(label, "%d", step);
	m_pStepLabel->setString(label);
	CC_SAFE_DELETE_ARRAY(label);
}

void PanelLayer::setScore( int score ){
    m_nCurrentScore = score;
    char *label = new char[16];
    sprintf(label, "%d", score);
    m_pScoreLabel->setString(label);
    unschedule(schedule_selector(PanelLayer::updateScore));
    CC_SAFE_DELETE_ARRAY(label);
}

void PanelLayer::setScore( int targetScore, float duration ){
    if (m_nCurrentScore < targetScore){
        int steps = targetScore - m_nCurrentScore;
        m_nTargetScore = targetScore;
        m_nUpdateDelta = 1;
        if (steps > MAX_UPDATE_STEPS){
            m_nUpdateDelta = (float) steps / MAX_UPDATE_STEPS + 0.5;
            steps = MAX_UPDATE_STEPS;
        }
        m_nCurrentScore += m_nUpdateDelta;
        setScore(m_nCurrentScore);
        m_fUpdateInterval = duration / steps;
        unschedule(schedule_selector(PanelLayer::updateScore));
        schedule(schedule_selector(PanelLayer::updateScore), m_fUpdateInterval);
    }
}

void PanelLayer::setScoreHint( const char* hint ){
    m_pScoreHint->setString(hint);
    m_pScoreHint->runAction(CCSequence::create(
        CCScaleTo::create(0.06f, 1.3f, 1.3f),
        CCScaleTo::create(0.06f, 0.8f, 0.8f),
        CCScaleTo::create(0.06f, 1.0f, 1.0f),
        NULL
        ));
}

void PanelLayer::setCoins( int coins ){
    char *label = new char[16];
    sprintf(label, "%d", coins);
    m_pCoins->setString(label);
    CC_SAFE_DELETE_ARRAY(label);
	m_nCurrentCoins = coins;
}

void PanelLayer::setTargetCoins(int target,float delayTime){
	m_nTargetCoins = target;
	m_fUpdateCoinsAllTime = 0;
	if (m_nTargetCoins == m_nCurrentCoins){
		return;
	}
	m_nUpdateCoinsInterval = (UPDATE_COINS_TIME * 1.0f) / (target - m_nCurrentCoins);
	unschedule(schedule_selector(PanelLayer::updateCoins));
	schedule(schedule_selector(PanelLayer::updateCoins), delayTime + abs(m_nUpdateCoinsInterval));
}

void PanelLayer::updateCoins(float dt){
	 unschedule(schedule_selector(PanelLayer::updateCoins));
	 m_fUpdateCoinsAllTime += dt;
	 if (m_fUpdateCoinsAllTime > UPDATE_COINS_TIME){
		 m_nCurrentCoins = m_nTargetCoins;
		 setCoins(m_nCurrentCoins);
		 return;
	 }
	 if (m_nUpdateCoinsInterval > 0){
		 if (m_nCurrentCoins < m_nTargetCoins){
			 m_nCurrentCoins += 1;
			 if (m_nCurrentCoins > m_nTargetCoins){
				 m_nCurrentCoins = m_nTargetCoins;
			 }
			 setCoins(m_nCurrentCoins);
			 schedule(schedule_selector(PanelLayer::updateCoins), m_nUpdateCoinsInterval);
		 }else{
			 CCLOG("%f",m_fUpdateCoinsAllTime);
		 }
	 }else if(m_nUpdateCoinsInterval < 0){
		 if (m_nCurrentCoins > m_nTargetCoins){
			 m_nCurrentCoins -= 1;
			 if (m_nCurrentCoins < m_nTargetCoins){
				 m_nCurrentCoins = m_nTargetCoins;
			 }
			 setCoins(m_nCurrentCoins);
			 schedule(schedule_selector(PanelLayer::updateCoins), abs(m_nUpdateCoinsInterval));
		 }else{
			 CCLOG("%f",m_fUpdateCoinsAllTime);
		 }
	 }	 
}

void PanelLayer::showCoinsAni(){
	CCSprite* dia = CCSprite::create("diamond.png");
	dia->setPosition(VisibleRect::center());
	addChild(dia, 11);
	dia->setScale(3.0f);
	float showTime = 0.3f;
	float moveTime = 0.5f;
	dia->runAction(CCSequence::create(
		CCDelayTime::create(showTime),
		CCSpawn::createWithTwoActions(CCMoveTo::create(moveTime, m_pCoins->getPosition()),CCScaleTo::create(moveTime,1.0f)),
		CCCallFuncN::create(this, callfuncN_selector(PanelLayer::removeChild)),
		NULL));
	setTargetCoins(UserInfo::getCoins(),showTime + moveTime);
}

void PanelLayer::updateScore(float dt){
    if (m_nCurrentScore < m_nTargetScore){
        m_nCurrentScore += m_nUpdateDelta;
        if (m_nCurrentScore > m_nTargetScore){
            m_nCurrentScore = m_nTargetScore;
        }
        setScore(m_nCurrentScore);
        unschedule(schedule_selector(PanelLayer::updateScore));
        schedule(schedule_selector(PanelLayer::updateScore), m_fUpdateInterval);
    }
}

void PanelLayer::deliveryScore( const CCPoint &from, int totalScore, int count ){
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
            CCCallFuncN::create(this, callfuncN_selector(PanelLayer::removeChild)),
            NULL));
        delay++;
    }
}

void PanelLayer::setStageClear( bool clear ){
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
}

void PanelLayer::menuCallback( CCObject *pSender )
{
    CCNode *pNode = dynamic_cast<CCNode *>(pSender);
	
    if (pNode) {
        int tag = pNode->getTag();
        switch (tag) {
        case TAG_PAUSE_BUTTON:
            invokeListener(pNode);
            disableSkill();
            break;
        case TAG_STAR_4:
        case TAG_STAR_2:
        case TAG_STAR_1:
        case TAG_STAR_3:
        case TAG_STAR_5:
			break;
        case TAG_BOMB:
			{
				bool showShop = false;
				if (GameData::getInstance()->m_nUseProType == USE_PRO_TYPE_COINONLY){
					if (UserInfo::getCoins() < GameData::getInstance()->m_nBombUseCoin){
						showShop = true;
					}
				}else if (GameData::getInstance()->m_nUseProType == USE_PRO_TYPE_COUNTONLY){
					if (UserInfo::getProCount(USERINFO_PRO_TYPE_BOMB) < 1){
						showShop = true;
					}
				}else{
					if (UserInfo::getCoins() < GameData::getInstance()->m_nBombUseCoin &&
						UserInfo::getProCount(USERINFO_PRO_TYPE_BOMB) < 1){
						showShop = true;
					}
				}
				if (showShop){
					CCMenu *pMenu = (CCMenu *) getChildByTag(TAG_MENU);
					invokeListener(pMenu->getChildByTag(TAG_SHOP));
				}else{
					invokeListener(pNode);
					toggleSkill(tag);
				}
			}

            
            break;
		case TAG_PAINT:
			{
				bool showShop = false;
				if (GameData::getInstance()->m_nUseProType == USE_PRO_TYPE_COINONLY){
					if (UserInfo::getCoins() < GameData::getInstance()->m_nPaintUseCoin){
						showShop = true;
					}
				}else if (GameData::getInstance()->m_nUseProType == USE_PRO_TYPE_COUNTONLY){
					if (UserInfo::getProCount(USERINFO_PRO_TYPE_PAINT) < 1){
						showShop = true;
					}
				}else{
					if (UserInfo::getCoins() < GameData::getInstance()->m_nPaintUseCoin &&
						UserInfo::getProCount(USERINFO_PRO_TYPE_PAINT) < 1){
							showShop = true;
					}
				}
				if (showShop){
					CCMenu *pMenu = (CCMenu *) getChildByTag(TAG_MENU);
					invokeListener(pMenu->getChildByTag(TAG_SHOP));
				}else{
					invokeListener(pNode);
					toggleSkill(tag);
				}
			}
			break;
        case TAG_SHOP:
            invokeListener(pNode);
            disableSkill();
			SoundMgr::playEffect(SoundMgr::EFFECT_CLICK);
			break;
		case TAG_RAINBOW:			
			SoundMgr::playEffect(SoundMgr::EFFECT_PRO_RAINBOW);
			{
				bool showShop = false;
				if (GameData::getInstance()->m_nUseProType == USE_PRO_TYPE_COINONLY){
					if (UserInfo::getCoins() < GameData::getInstance()->m_nReflashUseCoin){
						showShop = true;
					}
				}else if (GameData::getInstance()->m_nUseProType == USE_PRO_TYPE_COUNTONLY){
					if (UserInfo::getProCount(USERINFO_PRO_TYPE_REFLASH) < 1){
						showShop = true;
					}
				}else{
					if (UserInfo::getCoins() < GameData::getInstance()->m_nReflashUseCoin &&
						UserInfo::getProCount(USERINFO_PRO_TYPE_REFLASH) < 1){
							showShop = true;
					}
				}
				if (showShop){
					CCMenu *pMenu = (CCMenu *) getChildByTag(TAG_MENU);
					invokeListener(pMenu->getChildByTag(TAG_SHOP));
				}else{
					invokeListener(pNode);
				}
			}
			disableSkill();
			break;
        default:
			invokeListener(pNode);
            disableSkill();
            break;
        }
    }
}

void PanelLayer::toggleSkill( int tag )
{
    CCSprite *pNewSkill = (CCSprite *) getChildByTag(TAG_MENU)->getChildByTag(tag);

    if ( pNewSkill != m_pSelectedSkill){
        if (m_pSelectedSkill){
            disableSkill();
        }

        m_pSelectedSkill = pNewSkill;
        m_pSelectedSkill->retain();
        if (tag == TAG_BOMB || tag == TAG_PAINT){
            m_pSelectedSkill->runAction(CCRepeatForever::create(CCSequence::create(
                CCScaleTo::create(0.5f, 1.3f, 1.3f),
                CCScaleTo::create(0.5f, 1.0f, 1.0f),
                NULL)));
        }
    }else{
        disableSkill();
    }
}

void PanelLayer::disableSkill()
{
    if (m_pSelectedSkill){
        int tag = m_pSelectedSkill->getTag();

		if (tag == TAG_BOMB || tag == TAG_PAINT){
            m_pSelectedSkill->stopAllActions();
            m_pSelectedSkill->setScale(1.0f);
        }
		if (TAG_BOMB == tag){
			updateProCountLabel(USERINFO_PRO_TYPE_BOMB);
		}
		if (TAG_PAINT == tag){
			updateProCountLabel(USERINFO_PRO_TYPE_PAINT);
		}
		if (TAG_RAINBOW == tag){
			updateProCountLabel(USERINFO_PRO_TYPE_REFLASH);
		}
        m_pSelectedSkill->release();
        m_pSelectedSkill = NULL;
    }
}

void PanelLayer::invokeListener( CCNode *pSender ){
    CCObject *pTarget = m_obOnClickListener.pTarget;
    SEL_CallFuncI pCallback = m_obOnClickListener.pCallback;
    if (pTarget && pCallback){
        (pTarget->*pCallback)(pSender->getTag());
    }
}

void PanelLayer::setTouchEnabled( bool value ){
    CCLayer::setTouchEnabled(value);

    CCMenu *pMenu = (CCMenu *) getChildByTag(TAG_MENU);
    if (pMenu){
        pMenu->setTouchEnabled(value);
    }
}

void PanelLayer::updateProCountLabel(int proType){
	if (proType == USERINFO_PRO_TYPE_REFLASH && m_pReflashLabel != NULL){
		m_pReflashLabel->setString(CCString::createWithFormat("%d",UserInfo::getProCount(USERINFO_PRO_TYPE_REFLASH))->getCString());
	}
	if (proType == USERINFO_PRO_TYPE_BOMB && m_pBombLabel != NULL){
		m_pBombLabel->setString(CCString::createWithFormat("%d",UserInfo::getProCount(USERINFO_PRO_TYPE_BOMB))->getCString());
	}
	if (proType == USERINFO_PRO_TYPE_PAINT && m_pPaintLabel != NULL){
		m_pPaintLabel->setString(CCString::createWithFormat("%d",UserInfo::getProCount(USERINFO_PRO_TYPE_PAINT))->getCString());
	}
}