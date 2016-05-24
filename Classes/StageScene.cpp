#include <math.h>

#include "StageScene.h"
#include "UserInfo.h"
#include "SoundMgr.h"
#include "PauseLayer.h"
#include "MenuScene.h"
#include "ShopLayer.h"
#include "MyPurchase.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "MyPurchaseIOS.h"
#endif
StageScene::StageScene(void)
: m_bIsStageClear(false),
m_nSkillType(-1),
m_bBonusZeroPrompted(false),
m_pPanelLayer(NULL),
m_pMagicLayer(NULL),
m_pQuickBuyLayer(NULL),
m_pGameOverLayer(NULL),
m_fRemainTime(0),
m_bShowLiBao(false)
{
	m_pBatchNode = CCNode::create();
	m_pBatchNode->retain();
	m_iSeletedIndex.x = -1;
	m_iSeletedIndex.y = -1;
	m_pStarUtil = new StarUtil();
}


StageScene::~StageScene(void)
{
	CC_SAFE_RELEASE_NULL(m_pBatchNode);
	CC_SAFE_RELEASE_NULL(m_pPanelLayer);
	CC_SAFE_DELETE(m_pStarUtil);
}

CCScene* StageScene::scene(bool resume /*= false*/)
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	StageScene *layer = StageScene::create(resume);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool StageScene::init(bool resume /*= false*/){
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init()){
		return false;
	}

	getStageValue();

	setKeypadEnabled(true);
	setTouchEnabled(true);

	// add panel layer
	PanelLayer *pPanel = PanelLayer::create();
	addChild(pPanel, Z_ORDER_PANEL);
	pPanel->setOnClickListener(this, callfuncI_selector(StageScene::onPanelButtonClicked));

	m_pPanelLayer = pPanel;
	m_pPanelLayer->retain();
	updatePanel();

	addChild(m_pBatchNode, Z_ORDER_STAR);
	initBackgound();

	m_obOriginPoint.x = VisibleRect::left().x;
	m_obOriginPoint.y = VisibleRect::bottom().y + STAR_SIZE * ROWS_SIZE;

	if (resume){
		m_pStarUtil->loadLastState();
	}
	m_bResume = resume;
	SoundMgr::playEffect(SoundMgr::EFFECT_READY_GO);
	return true;
}

void StageScene::onEnter(){
	CCLayer::onEnter();
	newStage(!m_bResume);
}

void StageScene::getStageValue()
{
	m_nLevel = m_pStarUtil->getStage() + 1;
	m_sCurrentStageInfo = DataManagerSelf->StagesVec.at((m_nLevel - 1) % DataManagerSelf->StagesVec.size());
	loadStageInfo(m_nLevel);
	m_nTargetType = m_sCurrentStageInfo.params[0];
	m_nTargetCount = m_sCurrentStageInfo.params[1];
}

void StageScene::loadStageInfo(int level){

}

void StageScene::initBackgound(){
	CCSprite* pStageBg = CCSprite::create("bg_mainscene.jpg");
	pStageBg->setPosition(VisibleRect::center());
	CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
	float scale = frameSize.width / DESIGN_WIDTH;
	if (scale > 0){
		float scaleY = frameSize.height / DESIGN_HEIGHT;
		if (scaleY > scale){
			float bgScale = scaleY / scale;
			pStageBg->setScale(bgScale);
		}
	}
	addChild(pStageBg, Z_ORDER_BACKGROUND);
}

void StageScene::keyBackClicked()
{
	PauseLayer *pPause = dynamic_cast<PauseLayer *>(getChildByTag(TAG_PAUSE));
	ShopLayer *pShop = dynamic_cast<ShopLayer *>(getChildByTag(TAG_SHOP_LAYER));
	if (!pPause){
		if (pShop){
			pShop->close(NULL);
		}
		else{
			showPauseLayer();
		}
	}
}

void StageScene::keyMenuClicked(){

}

void StageScene::refreshStar(){
	Star *pStar;
	CCSprite *pOldStarSprite;
	CCSprite *pNewStarSprite;
	int tag;
	Index targetIndex;
	Index currentIndex;
	bool moved = false;
	int delay = 0;
	int lastRow = 0;

	srand(time(NULL));
	//int randomDirection = m_sCurrentStageInfo.content[m_nCurDirectionIndex]/*rand() % 4*/; //marker
	//StarUtil::m_nDirection = randomDirection;
	//m_nCurDirectionIndex++;
	//int contentSize = 0;
	//for (int i = 0; i < sizeof(m_sCurrentStageInfo.content) / sizeof(int); i++)
	//{
	//	if(m_sCurrentStageInfo.content[i] != 0)
	//	{
	//		contentSize++;
	//	}
	//	else
	//	{
	//		break;
	//	}
	//}
	//if (m_nCurDirectionIndex > contentSize)
	//{
	//	m_nCurDirectionIndex = 0;
	//}
	if (StarUtil::m_nDirection == DIC_RIGHT || StarUtil::m_nDirection == DIC_LEFT)
	{
		for (int r = ROWS_SIZE - 1; r >= 0; r--)
		for (int c = StarUtil::m_nDirection == DIC_RIGHT ? COlUMNS_SIZE - 1 : 0; StarUtil::m_nDirection == DIC_RIGHT ? c >= 0 : c < COlUMNS_SIZE; StarUtil::m_nDirection == DIC_RIGHT ? c-- : c++)
		{
			pNewStarSprite = NULL;
			pOldStarSprite = NULL;

			pStar = &(m_pStarUtil->star[c][r]);
			tag = pStar->intTag;
			currentIndex = StarUtil::getIndexByTag(tag);
			targetIndex = pStar->targetIndex;
			pOldStarSprite = (CCSprite *)m_pBatchNode->getChildByTag(tag);

			if (pOldStarSprite) {
				pOldStarSprite->stopAllActions();
				pOldStarSprite->setScale(1.0f);
				if (targetIndex.x != currentIndex.x || targetIndex.y != currentIndex.y) {
					// we need to move the old star
					pOldStarSprite->retain();
					m_pBatchNode->removeChildByTag(tag);

					CCPoint oldPosition = pOldStarSprite->getPosition();
					CCPoint newPosition = getStarPosition(targetIndex.x, targetIndex.y);
					m_pBatchNode->addChild(pOldStarSprite, Z_ORDER_STAR, StarUtil::getTagByIndex(targetIndex));

					pOldStarSprite->runAction(CCSequence::create(CCDelayTime::create(0.01f * delay),
						CCEaseBackInOut::create(CCMoveTo::create(0.3f, newPosition)), NULL));
					if (lastRow != r){
						delay++;
						lastRow = r;
					}

					pOldStarSprite->release();
					moved = true;
				}
				else{
					// no need to move old star, but we are not sure whether the state was changed,
					// recreate it anyway.
					m_pBatchNode->removeChildByTag(tag);
					if (pStar->color != STAR_COLOR_NULL){
						int imgIndex = 0;
						if (pStar->state == STAR_SELECT_YES){
							imgIndex = 1;
						}
						pNewStarSprite = CCSprite::create(
							g_starFrameNameArray[pStar->color][imgIndex].c_str());
						pNewStarSprite->setPosition(getStarPosition(c, r));
						m_pBatchNode->addChild(pNewStarSprite, Z_ORDER_STAR, tag);
					}
				}
			}
		}
	}
	else
	{
		for (int r = StarUtil::m_nDirection == DIC_UP ? 0 : ROWS_SIZE - 1; StarUtil::m_nDirection == DIC_UP ? r < ROWS_SIZE : r >= 0; StarUtil::m_nDirection == DIC_UP ? r++ : r--)
		for (int c = 0; c < COlUMNS_SIZE; c++)
		{
			pNewStarSprite = NULL;
			pOldStarSprite = NULL;

			pStar = &(m_pStarUtil->star[c][r]);
			tag = pStar->intTag;
			currentIndex = StarUtil::getIndexByTag(tag);
			targetIndex = pStar->targetIndex;
			pOldStarSprite = (CCSprite *)m_pBatchNode->getChildByTag(tag);

			if (pOldStarSprite) {
				pOldStarSprite->stopAllActions();
				pOldStarSprite->setScale(1.0f);
				if (targetIndex.x != currentIndex.x || targetIndex.y != currentIndex.y) {
					// we need to move the old star
					pOldStarSprite->retain();
					m_pBatchNode->removeChildByTag(tag);

					CCPoint oldPosition = pOldStarSprite->getPosition();
					CCPoint newPosition = getStarPosition(targetIndex.x, targetIndex.y);
					m_pBatchNode->addChild(pOldStarSprite, Z_ORDER_STAR, StarUtil::getTagByIndex(targetIndex));

					pOldStarSprite->runAction(CCSequence::create(CCDelayTime::create(0.01f * delay),
						CCEaseBackInOut::create(CCMoveTo::create(0.3f, newPosition)), NULL));
					if (lastRow != r){
						delay++;
						lastRow = r;
					}

					pOldStarSprite->release();
					moved = true;
				}
				else{
					// no need to move old star, but we are not sure whether the state was changed,
					// recreate it anyway.
					m_pBatchNode->removeChildByTag(tag);
					if (pStar->color != STAR_COLOR_NULL){
						int imgIndex = 0;
						if (pStar->state == STAR_SELECT_YES){
							imgIndex = 1;
						}
						pNewStarSprite = CCSprite::create(
							g_starFrameNameArray[pStar->color][imgIndex].c_str());
						pNewStarSprite->setPosition(getStarPosition(c, r));
						m_pBatchNode->addChild(pNewStarSprite, Z_ORDER_STAR, tag);
					}
				}
			}
		}
	}
	if (moved){
		m_pStarUtil->resetTargetTags(); //marker
	}
	float speed = m_obOriginPoint.y / 0.5f;
	srand(time(NULL));
	for (int i = 0; i < STAR_ROW_COUNT; i++){
		for (int j = STAR_ROW_COUNT - 1; j >= 0; j--){
			if (m_pStarUtil->star[i][j].color == STAR_COLOR_NULL){
				int starColor = rand() % (STAR_COLOR_5 + 1);
				if (m_pStarUtil->getNextColor() != STAR_COLOR_NULL)
				{
					starColor = m_pStarUtil->getNextColor();
				}
				m_pStarUtil->star[i][j].color = starColor;
				m_pStarUtil->star[i][j].state = STAR_SELECT_NO;   //ʧȥѡ��״̬
				m_pStarUtil->star[i][j].intTag = i * COlUMNS_SIZE + j;
				m_pStarUtil->star[i][j].targetIndex.x = i;
				m_pStarUtil->star[i][j].targetIndex.y = j;

				//StarUtil::m_nDirection = randomDirection;
				CCPoint tpos = getStarPosition(i, j);
				CCPoint spos;
				float actionTime = 0;
				switch (StarUtil::m_nDirection)
				{
				case DIC_UP:
					spos = ccp(tpos.x, tpos.y - STAR_SIZE * 2);
					actionTime = fabs(spos.y - tpos.y);
					break;
				case DIC_DOWN:
					spos = ccp(tpos.x, tpos.y + STAR_SIZE * 2);
					actionTime = fabs(spos.y - tpos.y);
					break;
				case DIC_LEFT:
					spos = ccp(tpos.x + STAR_SIZE * 2, tpos.y);
					actionTime = fabs(spos.x - tpos.x);
					speed = m_obOriginPoint.y / 1.0f;
					break;
				case DIC_RIGHT:
					spos = ccp(tpos.x - STAR_SIZE * 2, tpos.y);
					actionTime = fabs(spos.x - tpos.x);
					speed = m_obOriginPoint.y / 1.0f;
					break;
				}
				CCSprite* pNewStarSprite = CCSprite::create(
					g_starFrameNameArray[m_pStarUtil->star[i][j].color][1].c_str());
				pNewStarSprite->setPosition(spos);
				m_pBatchNode->addChild(pNewStarSprite, Z_ORDER_STAR, m_pStarUtil->star[i][j].intTag);
				CCMoveTo* move = CCMoveTo::create(actionTime / speed, tpos);
				pNewStarSprite->runAction(move);
			}
		}
	}
	m_pStarUtil->findStarMax();
}

void StageScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
	if (!m_bActive || (m_pMagicLayer != NULL && m_pMagicLayer->isVisible())) {
		return;
	}
	CCPoint touchLocation = (((CCTouch*)(*(pTouches->begin())))->getLocation());
	Index index = findTouchedIndex(touchLocation);

	if (index.x == -1 || index.y == -1){
		m_pStarUtil->resetStarState();
		m_pPanelLayer->setScoreHint("");
	}
	else{
		if (m_nSkillType == TAG_BOMB){
			onMagicClick(index, touchLocation);
			refreshStar();
			isGameOver();
		}
		else if (m_nSkillType == TAG_PAINT){
			m_iSeletedIndex = index;
			showMagicPanel(true);
			return;
		}
		else{
			onNormalClick(index, touchLocation);
		}
	}

	if (DBG){
		CCLog("touch position:x=%f y=%f star:x=%d y=%d", touchLocation.x, touchLocation.y, index.x, index.y);
	}
}

Index StageScene::findTouchedIndex(CCPoint touch){
	Index index = { -1, -1 };
	for (int c = 0; c < COlUMNS_SIZE; c++){
		for (int r = 0; r < ROWS_SIZE; r++){
			if ((m_obOriginPoint.x + c * STAR_SIZE + STAR_SIZE) > touch.x
				&& (m_obOriginPoint.x + c * STAR_SIZE) < touch.x){
				index.x = c;
				if ((m_obOriginPoint.y - r * STAR_SIZE - STAR_SIZE) < touch.y
					&& (m_obOriginPoint.y - r * STAR_SIZE) > touch.y){
					index.y = r;
					break;
				}
			}
		}
	}

	return index;
}

void StageScene::explodeFire(CCPoint position){
	CCParticleExplosion *pEmitter = CCParticleExplosion::create();
	pEmitter->setTexture(CCTextureCache::sharedTextureCache()->addImage(s_fire));
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

	pEmitter->setDuration(0.5);

	addChild(pEmitter, Z_ORDER_EXPLOSION);
	SoundMgr::playFire(SoundMgr::FIRE_MAX);
}

void StageScene::explodeStar(CCPoint position, int totalParticles, const char *fileImage){
	CCParticleExplosion *pEmitter = CCParticleExplosion::create();
	pEmitter->setTexture(CCTextureCache::sharedTextureCache()->addImage(fileImage));
	pEmitter->setAutoRemoveOnFinish(true);

	pEmitter->setPosition(position);

	ccColor4F c4Var = { 0, 0, 0, 0.0 };
	ccColor4F c4 = { 1, 1, 1, 1 };
	pEmitter->setStartColor(c4);
	pEmitter->setEndColor(c4);
	pEmitter->setStartColorVar(c4Var);
	pEmitter->setEndColorVar(c4Var);

	pEmitter->setTotalParticles(totalParticles);

	pEmitter->setRadialAccel(1);
	pEmitter->setRadialAccelVar(5);

	pEmitter->setSpeed(200);
	pEmitter->setScale(1.2f);
	pEmitter->setGravity(ccp(0, -200));

	addChild(pEmitter, Z_ORDER_EXPLOSION);
}

void StageScene::newStage(bool initStar){
	m_bActive = false;
	m_pPanelLayer->setTouchEnabled(false);
	m_bShowLiBao = false;
	if (initStar){
		m_pStarUtil->initStarEx();
		//m_pStarUtil->initStar();
	}
	StarUtil::m_nDirection = m_sCurrentStageInfo.content[0];
	StarUtil::m_nCurDirectionIndex = 0;
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCLabelTTF *pBonus = NULL;
	pBonus = (CCLabelTTF *)getChildByTag(TAG_BONUS);
	if (pBonus){
		pBonus->stopAllActions();
		removeChild(pBonus);
	}
	CCDictionary *text = CCDictionary::createWithContentsOfFile(XML_DATA);
	CCString *msgLev = (CCString*)text->objectForKey("lev");
	CCString *msgTar = (CCString*)text->objectForKey("tar");
	CCString* score = CCString::createWithFormat("%s %d\n%s %d", msgLev->getCString(), m_pStarUtil->getStage() + 1, msgTar->getCString(), m_pStarUtil->getTarget());
	CCLabelTTF* pScoreLabel = CCLabelTTF::create(score->getCString(), "Arial", 32);
	pScoreLabel->setColor(ccc3(255, 255, 255));
	this->addChild(pScoreLabel, 1);
	CCPoint tpos = ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + pScoreLabel->getContentSize().height / 2);
	pScoreLabel->setPosition(ccp(origin.x + visibleSize.width + pScoreLabel->getContentSize().width, tpos.y));
	pScoreLabel->runAction(CCSequence::create(CCDelayTime::create(0.8f), CCMoveTo::create(0.5f, tpos), CCDelayTime::create(1.2f),
		CCCallFuncN::create(this, callfuncN_selector(StageScene::autoRemove)),
		CCCallFunc::create(this, callfunc_selector(StageScene::showStar)), NULL));
	unschedule(schedule_selector(StageScene::showMaxStar));
}


void StageScene::showStar(){ //marker
	CCSprite *pStarSprite = NULL;
	Star *pStar = NULL;
	float speed = m_obOriginPoint.y / 0.5f;
	for (int r = 0; r < ROWS_SIZE; r++){
		for (int c = 0; c < COlUMNS_SIZE; c++){
			pStar = &m_pStarUtil->star[c][r];
			if (pStar->color != STAR_COLOR_NULL){
				bool first = (pStarSprite == NULL);
				int imgIndex = 0;
				if (pStar->state == STAR_SELECT_YES){
					imgIndex = 1;
				}
				//CCLOG("pStar->color===========%d, imgIndex====================%d", pStar->color, imgIndex);
				pStarSprite = CCSprite::create(g_starFrameNameArray[pStar->color][imgIndex].c_str());
				pStarSprite->setPosition(ccp(STAR_SIZE / 2.0 + m_obOriginPoint.x + c * STAR_SIZE,
					m_obOriginPoint.y - STAR_SIZE / 2.0 - r * STAR_SIZE));
				m_pBatchNode->addChild(pStarSprite, Z_ORDER_STAR, pStar->intTag);
				CCPoint tpos = pStarSprite->getPosition();
				CCPoint spos = ccp(tpos.x, STAR_SIZE * 2 * (c % 2) + m_obOriginPoint.y * 4 - STAR_SIZE / 2.0 - r * STAR_SIZE * 4 + VisibleRect::getVisibleRect().size.height);
				pStarSprite->setPosition(spos);
				CCMoveTo* move = CCMoveTo::create((spos.y - tpos.y) / speed, tpos);
				if (first) {
					pStarSprite->runAction(CCSequence::create(move, CCCallFunc::create(this, callfunc_selector(StageScene::starInitDone)), NULL));
				}
				else {
					pStarSprite->runAction(move);
				}
			}
		}
	}

	m_bIsStageClear = false;
	updatePanel();
}


void StageScene::starInitDone(){
	if (UserInfo::getFirstLogin()){
		showQuickBuy(true);
		return;
	}
	m_bActive = true;
	m_pPanelLayer->setTouchEnabled(true);
	isGameOver();
	schedule(schedule_selector(StageScene::showMaxStar), SHOW_TIPS_LATER);
}


void StageScene::autoRemove(CCNode* node){
	this->removeChild(node);
}


void StageScene::stageOver(){
	int tag;
	CCSprite *pSprite;
	int actionCount = 1;;
	bool revert = false;
	m_nOverExplodedCount = 0;
	for (int r = 0; r < ROWS_SIZE; r++){
		for (int c = revert ? (COlUMNS_SIZE - 1) : 0; revert ? (c >= 0) : (c < COlUMNS_SIZE); revert ? c-- : c++){
			// TODO: animation
			pSprite = NULL;

			tag = m_pStarUtil->star[c][r].intTag;
			pSprite = (CCSprite *)m_pBatchNode->getChildByTag(tag);
			if (pSprite){
				pSprite->runAction(CCSequence::create(CCDelayTime::create(0.1f * actionCount),
					CCCallFuncN::create(this, callfuncN_selector(StageScene::starExplodedCallback)), NULL));
				actionCount++;
				if (r == (ROWS_SIZE - 1)){
					break;
				}
			}
		}
		revert = !revert;
	}

	if (actionCount == 1){
		// all stars were cleared
		this->runAction(CCSequence::create(CCDelayTime::create(0.5f),
			CCCallFuncN::create(this, callfuncN_selector(StageScene::starExplodedCallback)), NULL));
		showScoreTips(0, true);
		m_pPanelLayer->setScore(m_pStarUtil->getScore(), 0.6f);
	}
	else{
		showScoreTips(m_pStarUtil->remainCount(), true);
	}
}

void StageScene::updatePanel(){
	if (m_pPanelLayer){
		m_pPanelLayer->setStage(m_pStarUtil->getStage() + 1);
		m_pPanelLayer->setStep(m_pStarUtil->getStep());
		m_pPanelLayer->setTarget(m_pStarUtil->getTarget());
		m_pPanelLayer->setScore(m_pStarUtil->getScore());
		m_pPanelLayer->setBestScore(UserInfo::getBestScore());
		m_pPanelLayer->setStageClear(m_bIsStageClear);
		m_pPanelLayer->setCoins(UserInfo::getCoins());
	}
}

void StageScene::starExplodedCallback(CCNode *pNode){
	if (pNode == this){
		if (m_pStarUtil->nextStage()){
			showStageWin();
		}
		else{
			showGameOver();
		}
	}
	else{
		SoundMgr::playEffect(SoundMgr::EFFECT_BROKEN);
		int tag = pNode->getTag();
		Index index = StarUtil::getIndexByTag(tag);
		if (index.y == (ROWS_SIZE - 1)){
			CCSprite *pSprite;
			int count = 0;
			for (int c = 0; c < COlUMNS_SIZE; c++){
				pSprite = NULL;
				int tag = m_pStarUtil->star[c][ROWS_SIZE - 1].intTag;
				pSprite = (CCSprite *)m_pBatchNode->getChildByTag(tag);
				index = StarUtil::getIndexByTag(tag);
				if (pSprite){
					count++;
					if (m_pStarUtil->star[index.x][index.y].color >= STAR_COLOR_1 && m_pStarUtil->star[index.x][index.y].color < STAR_COLOR_5){
						explodeStar(pSprite->getPosition(), 10, s_stars[m_pStarUtil->star[index.x][index.y].color].c_str());
					}
					m_pBatchNode->removeChild(pSprite, true);
				}
			}
			m_nOverExplodedCount += count;
			// promptBonus(StarUtil::getBonus(m_nOverExplodedCount));
			m_pPanelLayer->setScore(m_pStarUtil->getScore(), 0.6f);

			this->runAction(CCSequence::create(CCDelayTime::create(2.0f),
				CCCallFuncN::create(this, callfuncN_selector(StageScene::starExplodedCallback)), NULL));
		}
		else{
			m_nOverExplodedCount++;
			// promptBonus(StarUtil::getBonus(m_nOverExplodedCount));
			if (m_pStarUtil->star[index.x][index.y].color >= STAR_COLOR_1 && m_pStarUtil->star[index.x][index.y].color < STAR_COLOR_5){
				explodeStar(pNode->getPosition(), 10, s_stars[m_pStarUtil->star[index.x][index.y].color].c_str());
			}
			m_pBatchNode->removeChild(pNode, true);
		}
	}
}

void StageScene::starExplodedInOrder(CCNode *pNode, void* result){
	if (pNode == this){
		m_bActive = true;
		m_pPanelLayer->setTouchEnabled(true);
		string reward = StarUtil::getRewardFrame((int)result);
		CCSprite *pReward = NULL;
		CCLog("reward %s", reward.c_str());
		if (!reward.empty()){
			pReward = CCSprite::create(reward.c_str());
			pReward->setPosition(VisibleRect::center());
			m_pBatchNode->addChild(pReward, Z_ORDER_PANEL);
			pReward->runAction(CCSequence::create(
				CCBlink::create(1.0f, 10),
				CCDelayTime::create(1.0f),
				CCFadeOut::create(0.5f),
				CCCallFunc::create(pReward, callfunc_selector(CCNode::removeFromParent)),
				NULL
				));
			SoundMgr::playCombo(SoundMgr::COMBO_MAX);
			startFire();
		}

		if (!m_bIsStageClear && m_pStarUtil->isStageClear()){
			m_pPanelLayer->setStageClear(true);
			m_bIsStageClear = true;
		}
		unschedule(schedule_selector(StageScene::showMaxStar));
		schedule(schedule_selector(StageScene::showMaxStar), SHOW_TIPS_LATER);
		refreshStar();
		isGameOver();
	}
	else{
		SoundMgr::playEffect(SoundMgr::EFFECT_BROKEN);
		int tag = pNode->getTag();
		Index index = StarUtil::getIndexByTag(tag);
		explodeStar(pNode->getPosition(), 10, s_stars[(int)result].c_str());
		m_pBatchNode->removeChild(pNode, true); //marker
	}
}

void StageScene::showRandomLiBao(){
	if (m_bShowLiBao){
		return;
	}

	if (GameData::getInstance()->m_nLibaoStage != NULL){
		for (int i = 0; i < GameData::getInstance()->m_nLibaoStageSize; i++){
			if (GameData::getInstance()->m_nLibaoStage[i] == m_pStarUtil->getStage() + 1){
				if (m_pStarUtil->getNotClearCount(false) < COlUMNS_SIZE * COlUMNS_SIZE * 2 / 3){
					showQuickBuy(true);
					m_bShowLiBao = true;
				}
				return;
			}
		}
	}
	if (GameData::getInstance()->m_nLibaoBase <= 0 || GameData::getInstance()->m_fLiBaoPer <= 0){
		return;
	}
	int baseStage = 0;
	if (GameData::getInstance()->m_nLibaoStage != NULL){
		baseStage = GameData::getInstance()->m_nLibaoStage[GameData::getInstance()->m_nLibaoStageSize - 1];
	}
	if ((m_pStarUtil->getStage() + 1 - baseStage) >= GameData::getInstance()->m_nLibaoBase){
		if ((m_pStarUtil->getStage() + 1 - baseStage) % GameData::getInstance()->m_nLibaoBase != 0){
			return;
		}
		int radomPer = CCRANDOM_0_1() * 100;
		if (radomPer < GameData::getInstance()->m_fLiBaoPer){
			showQuickBuy(true);
			m_bShowLiBao = true;
		}
	}
}

void StageScene::showPauseLayer(){
	if (!m_bActive || getChildByTag(TAG_PAUSE)){
		return;
	}
	PauseLayer *pPauseLayer = PauseLayer::create();
	pPauseLayer->setOnSaveListener(CCCallFunc::create(this, callfunc_selector(StageScene::onSave)));
	addChild(pPauseLayer, Z_ORDER_MENU, TAG_PAUSE);
}

void StageScene::clickExpoledInOrder(Result result, CCPoint touchLocation){
	for (int i = 0; i < result.count; i++){
		int tag = result.pTags[i];
		CCSprite *pSprite = (CCSprite *)m_pBatchNode->getChildByTag(tag);
		int color = result.color;
		if (pSprite != NULL){
			if (result.tools[TOOL_DIAMOND] > 0)
			{
				for (int t = 0; t < STAR_ROW_COUNT * STAR_ROW_COUNT; t++)
				{
					if (result.toolIndex[t] < 0)
					{
						break;
					}
					else if (result.toolIndex[t] == i)
					{
						CCSprite* diamond = CCSprite::create("diamond.png");
						diamond->setPosition(pSprite->getPosition());
						this->addChild(diamond, Z_ORDER_STAR + 1);
						CCSpawn* spawn = CCSpawn::create(CCScaleBy::create(1.2f, 2.0f), CCMoveTo::create(1.2f, m_pPanelLayer->m_pCoins->getPosition()), NULL);
						diamond->runAction(CCSequence::create(spawn, CCCallFunc::create(diamond, callfunc_selector(StageScene::removeFromParent)), NULL));
						//this->runAction(CCSequence::create(CCDelayTime::create(1.0f), CCCallFunc::create(this, callfunc_selector(StageScene::showBombEffect)), NULL));
					}
				}
			}
			pSprite->runAction(CCSequence::create(
				CCDelayTime::create(0.05f * i),
				CCCallFuncND::create(this, callfuncND_selector(StageScene::starExplodedInOrder), ((void*)color)),
				NULL));
		}
	}
	int count = result.count;
	this->runAction(CCSequence::create(
		CCDelayTime::create(0.05f * (result.count + 1)),
		CCCallFuncND::create(this, callfuncND_selector(StageScene::starExplodedInOrder), (void*)count),
		NULL));
	m_pPanelLayer->setScore(m_pStarUtil->getScore(), 0.6f);
	m_pPanelLayer->deliveryScore(touchLocation, StarUtil::getScore(result.count), result.count);

	m_pPanelLayer->setScoreHint("");
}

void StageScene::onSave(){
	m_pStarUtil->saveState();
	CCDirector::sharedDirector()->replaceScene(getTansitionScene(Menu::scene()));
}

void StageScene::onPanelButtonClicked(int tag){
	if (tag == TAG_PAUSE_BUTTON){
		showPauseLayer();
	}
	else if (tag <= TAG_BOMB){
	}
	else if (tag == TAG_SHOP){
		UserInfo::s_nCurrentLevel = m_pStarUtil->getStage();
		showQuickBuy(true);
	}
	else if (tag == TAG_RAINBOW){
		bool useCoin = true;

		if (GameData::getInstance()->m_nUseProType == USE_PRO_TYPE_COUNTONLY){
			useCoin = false;
		}
		else if (GameData::getInstance()->m_nUseProType == USE_PRO_TYPE_COUNTANDCOIN){
			if (UserInfo::getProCount(USERINFO_PRO_TYPE_REFLASH) > 0){
				useCoin = false;
			}
		}
		if (useCoin){
			UserInfo::expendCoins(GameData::getInstance()->m_nReflashUseCoin);
			//m_pPanelLayer->setCoins(UserInfo::getCoins());
			m_pPanelLayer->setTargetCoins(UserInfo::getCoins());
		}
		else{
			UserInfo::useProByType(USERINFO_PRO_TYPE_REFLASH);
			m_pPanelLayer->updateProCountLabel(USERINFO_PRO_TYPE_REFLASH);
		}
		m_pStarUtil->radomRemain();
		refreshStar();
		isGameOver();
	}

	if (m_nSkillType == tag){
		m_nSkillType = TAG_MAX;
	}
	else{
		m_nSkillType = tag;
	}

}

StageScene* StageScene::create(bool resume /*= false*/){
	StageScene *pRet = new StageScene();
	if (pRet && pRet->init(resume)){
		pRet->autorelease();
		return pRet;
	}
	else{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

CCScene* StageScene::getTansitionScene(CCScene* scene){
	return CCTransitionFade::create(0.5f, scene);
}

void StageScene::showScoreTips(int bonus, bool end /*= false*/){
	CCLabelTTF *pBonus = NULL;
	pBonus = (CCLabelTTF *)getChildByTag(TAG_BONUS);
	if (pBonus){
		pBonus->stopAllActions();
		removeChild(pBonus);
	}
	CCDictionary *text = CCDictionary::createWithContentsOfFile(XML_DATA);
	CCString *showMsg = NULL;
	CCPoint msgPos = VisibleRect::center();
	if (end){
		CCString *msg = (CCString*)text->objectForKey("remainscore");
		showMsg = CCString::createWithFormat(msg->getCString(), bonus, StarUtil::getBonus(bonus));
	}
	else{
		CCString *msg = (CCString*)text->objectForKey("cleanscore");
		showMsg = CCString::createWithFormat(msg->getCString(), bonus, StarUtil::getScore(bonus));
		msgPos = ccp(VisibleRect::center().x, VisibleRect::center().y + 48 * 3);
	}

	pBonus = CCLabelTTF::create(showMsg->getCString(), "Arial", 28);
	if (end){
		pBonus->setFontSize(32);
	}
	else{
		pBonus->setFontSize(28);
	}
	pBonus->setPosition(msgPos);
	pBonus->setScale(0.6f);
	addChild(pBonus, Z_ORDER_PANEL, TAG_BONUS);
	pBonus->runAction(CCSequence::create(
		CCScaleTo::create(0.2f, 1.0f, 1.0f),
		CCDelayTime::create(3.0f),
		CCCallFunc::create(pBonus, callfunc_selector(CCNode::removeFromParent)),
		NULL
		));
}

void StageScene::showGameOver(){
	if (m_pGameOverLayer == NULL){
		m_pGameOverLayer = CCScale9Sprite::create("Dialog_bg.png");
		m_pGameOverLayer->setAnchorPoint(ccp(0.5f, 0.5f));
		m_pGameOverLayer->setPreferredSize(CCSizeMake(350, 400));
		CCSize size = m_pGameOverLayer->getContentSize();
		m_pGameOverLayer->setPosition(ccp(VisibleRect::center().x, VisibleRect::top().y + size.height / 2));
		m_pPanelLayer->addChild(m_pGameOverLayer, Z_ORDER_MENU);
		CCSprite *pGameOver = CCSprite::create("GameOver.png");
		pGameOver->setPosition(ccp(m_pGameOverLayer->getContentSize().width / 2, m_pGameOverLayer->getContentSize().height));
		m_pGameOverLayer->addChild(pGameOver);

		CCDictionary *text = CCDictionary::createWithContentsOfFile(XML_DATA);
		CCString *msg = (CCString*)text->objectForKey("Cont");
		CCLabelTTF* msgLabel = CCLabelTTF::create(msg->getCString(), "Arial", 50);
		msgLabel->setColor(ccBLACK);
		msgLabel->setPosition(ccp(pGameOver->getPositionX(),
			pGameOver->getPositionY() - pGameOver->getContentSize().height / 2 - msgLabel->getContentSize().height / 2 - 30));
		m_pGameOverLayer->addChild(msgLabel);

		CCSprite* pItemNormal = CCSprite::create("cancel_s.png");
		CCSprite* pItemSelected = CCSprite::create("cancel_s.png");
		pItemSelected->setScale(1.1f);
		CCMenuItemSprite* menuBackBtn = CCMenuItemSprite::create(pItemNormal, pItemSelected, this, menu_selector(StageScene::menuCallback));
		menuBackBtn->setTag(TAG_GAMEOVER_BACK);
		menuBackBtn->setPosition(ccp(m_pGameOverLayer->getContentSize().width - menuBackBtn->getContentSize().width / 4,
			m_pGameOverLayer->getContentSize().height - menuBackBtn->getContentSize().height / 4));

		pItemNormal = CCSprite::create("menu_continue2.png");
		pItemSelected = CCSprite::create("menu_continue2.png");
		pItemSelected->setScale(1.01f);
		CCMenuItemSprite *menuContinueBtn = CCMenuItemSprite::create(pItemNormal, pItemSelected, this, menu_selector(StageScene::menuCallback));
		menuContinueBtn->setTag(TAG_GAMEOVER_COINTINE);
		menuContinueBtn->setPosition(ccp(m_pGameOverLayer->getContentSize().width / 2, menuContinueBtn->getContentSize().height - 20));

		msg = (CCString*)text->objectForKey("ContTips");
		CCString *useCoinTips = CCString::createWithFormat(msg->getCString(), GameData::getInstance()->m_nFuHuoUseCoin);
		msgLabel = CCLabelTTF::create(useCoinTips->getCString(), "Arial", 18);
		msgLabel->setColor(ccWHITE);
		msgLabel->setPosition(ccp(menuContinueBtn->getPositionX(),
			menuContinueBtn->getPositionY() - menuContinueBtn->getContentSize().height / 2 - msgLabel->getContentSize().height / 2));
		m_pGameOverLayer->addChild(msgLabel);

		msg = (CCString*)text->objectForKey("sec");
		useCoinTips = CCString::createWithFormat("%d%s", REMAIN_CONTINUE_TIME, msg->getCString());
		msgLabel = CCLabelTTF::create(useCoinTips->getCString(), "Arial", 28);
		msgLabel->setColor(ccBLACK);
		msgLabel->setPosition(ccp(menuContinueBtn->getPositionX() + menuContinueBtn->getContentSize().width / 2 - msgLabel->getContentSize().width / 2 - 10,
			menuContinueBtn->getPositionY()));
		msgLabel->setTag(TAG_GAMEOVE_TIME);
		m_pGameOverLayer->addChild(msgLabel, 2);

		CCMenu *menu = CCMenu::create(menuBackBtn, menuContinueBtn, NULL);
		menu->setPosition(CCPointZero);
		m_pGameOverLayer->addChild(menu, 1, TAG_GAMEOVER_MENU);
		m_pGameOverLayer->runAction(CCSequence::create(CCEaseBackOut::create(CCMoveTo::create(1.5f, VisibleRect::center() - ccp(0, 50))),
			CCDelayTime::create(1.2f),
			CCCallFunc::create(this, callfunc_selector(StageScene::doGameOver)), NULL));
		m_fRemainTime = 0;
		schedule(schedule_selector(StageScene::remaindContinue), 0.3f);
	}
}

void StageScene::showStageWin(){
	newStage();
	startFire();
	SoundMgr::playEffect(SoundMgr::EFFECT_NEXT);
}

void StageScene::startFire()
{
	srand(time(NULL));

	fireTime = 0;
	fire(0);
}

void StageScene::remaindContinue(float dt){
	m_fRemainTime += dt;
	if (m_fRemainTime > REMAIN_CONTINUE_TIME){
		m_fRemainTime = REMAIN_CONTINUE_TIME;
	}

	CCLabelTTF *remainTimeLabel = (CCLabelTTF*)m_pGameOverLayer->getChildByTag(TAG_GAMEOVE_TIME);
	if (remainTimeLabel){
		CCDictionary *text = CCDictionary::createWithContentsOfFile(XML_DATA);
		CCString *msg = (CCString*)text->objectForKey("sec");
		int remainTime = REMAIN_CONTINUE_TIME - m_fRemainTime;
		CCString *remainTimeStr = CCString::createWithFormat("%d%s", remainTime, msg->getCString());
		remainTimeLabel->setString(remainTimeStr->getCString());
		if (m_fRemainTime >= REMAIN_CONTINUE_TIME){
			CCMenu* menu = (CCMenu*)m_pGameOverLayer->getChildByTag(TAG_GAMEOVER_MENU);
			CCMenuItemSprite* contineBtn = (CCMenuItemSprite*)menu->getChildByTag(TAG_GAMEOVER_COINTINE);
			menuCallback(contineBtn);
		}
	}
	else{
		unschedule(schedule_selector(StageScene::remaindContinue));
	}

}

void StageScene::fire(float dt){
	CCLog("fire db %f", dt);
	float delay = 0.5f;
	if (fireTime == 0) {
		fireTime += 0.1f;
	}
	else if (fireTime > 3.0f) {
		fireTime = 0;
		unschedule(schedule_selector(StageScene::fire));
		return;
	}
	else {
		fireTime += dt;
	}
	if (fireTime != 0) {
		explodeFire(getRandomPosForFire());
	}
	unschedule(schedule_selector(StageScene::fire));
	schedule(schedule_selector(StageScene::fire), delay);
}

cocos2d::CCPoint StageScene::getRandomPosForFire(){
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	int x = rand() % ((int)visibleSize.width) + origin.x;
	int y = rand() % ((int)(visibleSize.height / 2)) + origin.y + visibleSize.height / 2;
	return ccp(x, y);
}

void StageScene::doStageWin(){
	//SoundMgr::stopMusic();
	newStage();
}

void StageScene::doGameOver(){
	//goToMenu();
}

void StageScene::onNormalClick(Index index, CCPoint touchLocation){
	if (m_pStarUtil->star[index.x][index.y].color >= STAR_COLOR_1 && m_pStarUtil->star[index.x][index.y].color <= STAR_COLOR_5)
	{
		Result result = m_pStarUtil->onStarClicked(index.x, index.y);
		if (result.del){
			showScoreTips(result.count);
			m_bActive = false;
			m_pPanelLayer->setTouchEnabled(false);
			clickExpoledInOrder(result, touchLocation);
			m_pPanelLayer->setStep(m_pStarUtil->getStep());
		}
		CC_SAFE_DELETE_ARRAY(result.pTags);
	}
}

void StageScene::onMagicClick(Index index, CCPoint touchLocation){
	m_pStarUtil->resetStarState();
	m_pPanelLayer->setScoreHint("");
	Star *pStar = &(m_pStarUtil->star[index.x][index.y]);
	if (m_nSkillType < TAG_BOMB){
		if (pStar->color != STAR_COLOR_NULL && pStar->color != m_nSkillType){
			int tag = pStar->intTag;
			CCSprite *pOld = (CCSprite *)m_pBatchNode->getChildByTag(tag);
			if (pOld){
				pStar->color = m_nSkillType;
				m_nSkillType = -1;
				bool useCoin = true;
				if (GameData::getInstance()->m_nUseProType == USE_PRO_TYPE_COUNTONLY){
					useCoin = false;
				}
				else if (GameData::getInstance()->m_nUseProType == USE_PRO_TYPE_COUNTANDCOIN){
					if (UserInfo::getProCount(USERINFO_PRO_TYPE_PAINT) > 0){
						useCoin = false;
					}
				}
				if (useCoin){
					UserInfo::expendCoins(GameData::getInstance()->m_nPaintUseCoin);
					//m_pPanelLayer->setCoins(UserInfo::getCoins());
					m_pPanelLayer->setTargetCoins(UserInfo::getCoins());
				}
				else{
					UserInfo::useProByType(USERINFO_PRO_TYPE_PAINT);
					m_pPanelLayer->updateProCountLabel(USERINFO_PRO_TYPE_PAINT);
				}
				m_pPanelLayer->disableSkill();
				SoundMgr::playEffect(SoundMgr::EFFECT_PRO_PAINT);
				refreshStar();
				m_pStarUtil->findStarMax();
				unschedule(schedule_selector(StageScene::showMaxStar));
				schedule(schedule_selector(StageScene::showMaxStar), SHOW_TIPS_LATER);
			}
		}
	}
	else if (m_nSkillType == TAG_BOMB){
		Result result = m_pStarUtil->bulkDelete(index.x, index.y);
		if (result.count > 0){
			SoundMgr::playEffect(SoundMgr::EFFECT_PRO_BOMB);

			bool useCoin = true;
			if (GameData::getInstance()->m_nUseProType == USE_PRO_TYPE_COUNTONLY){
				useCoin = false;
			}
			else if (GameData::getInstance()->m_nUseProType == USE_PRO_TYPE_COUNTANDCOIN){
				if (UserInfo::getProCount(USERINFO_PRO_TYPE_BOMB) > 0){
					useCoin = false;
				}
			}
			if (useCoin){
				UserInfo::expendCoins(GameData::getInstance()->m_nBombUseCoin);
				//m_pPanelLayer->setCoins(UserInfo::getCoins());
				m_pPanelLayer->setTargetCoins(UserInfo::getCoins());
			}
			else{
				UserInfo::useProByType(USERINFO_PRO_TYPE_BOMB);
				m_pPanelLayer->updateProCountLabel(USERINFO_PRO_TYPE_BOMB);
			}
			for (int i = 0; i < result.count; i++){
				int tag = result.pTags[i];
				CCSprite *pSprite = (CCSprite*)m_pBatchNode->getChildByTag(tag);
				if (pSprite){
					Index spriteIndex = StarUtil::getIndexByTag(tag);
					Star *pStar = &(m_pStarUtil->star[spriteIndex.x][spriteIndex.y]);

					if (pStar->color == TOOL_BOMB)
					{
						CCSprite* bomb = CCSprite::create("bomb.png");
						bomb->setPosition(pSprite->getPosition());
						this->addChild(bomb, Z_ORDER_STAR + 1);
						CCSpawn* spawn = CCSpawn::create(CCScaleBy::create(1.0f, 2.0f), CCMoveTo::create(1.0f, VisibleRect::center()), NULL);
						bomb->runAction(CCSequence::create(spawn, CCCallFunc::create(bomb, callfunc_selector(StageScene::removeFromParent)), NULL));
						this->runAction(CCSequence::create(CCDelayTime::create(1.0f), CCCallFunc::create(this, callfunc_selector(StageScene::showBombEffect)), NULL));
					}
					else
					{
						explodeStar(pSprite->getPosition(), 10, s_stars[pStar->color].c_str());
					}
					m_pBatchNode->removeChild(pSprite, true);
					m_pPanelLayer->deliveryScore(touchLocation, StarUtil::getScore(result.count), result.count);
				}
			}
			CC_SAFE_DELETE_ARRAY(result.pTags);
			result = m_pStarUtil->bulkDelete(index.x, index.y, true);
			CC_SAFE_DELETE_ARRAY(result.pTags);
			m_pPanelLayer->setScore(m_pStarUtil->getScore(), 0.6f);

			m_nSkillType = -1;
			m_pPanelLayer->disableSkill();

			if (!m_bIsStageClear && m_pStarUtil->isStageClear()){
				m_pPanelLayer->setStageClear(true);
				m_bIsStageClear = true;
			}
			m_pStarUtil->findStarMax();
			unschedule(schedule_selector(StageScene::showMaxStar));
			schedule(schedule_selector(StageScene::showMaxStar), SHOW_TIPS_LATER);
		}
	}
}

void StageScene::showBombEffect()
{
	Result result = m_pStarUtil->bombClearAllStar();
	if (result.count > 0){
		SoundMgr::playEffect(SoundMgr::EFFECT_PRO_BOMB);
		for (int i = 0; i < result.count; i++){
			int tag = result.pTags[i];
			CCSprite *pSprite = (CCSprite*)m_pBatchNode->getChildByTag(tag);
			if (pSprite){
				Index spriteIndex = StarUtil::getIndexByTag(tag);
				Star *pStar = &(m_pStarUtil->star[spriteIndex.x][spriteIndex.y]);
				if (pStar->color == TOOL_BOMB)
				{

				}
				else
				{
					explodeStar(pSprite->getPosition(), 10, s_stars[pStar->color].c_str());
				}
				m_pBatchNode->removeChild(pSprite, true);
				//m_pPanelLayer->deliveryScore(touchLocation, StarUtil::getScore(result.count), result.count);
			}
		}
		CC_SAFE_DELETE_ARRAY(result.pTags);
		result = m_pStarUtil->bombClearAllStar(true);
		CC_SAFE_DELETE_ARRAY(result.pTags);
		m_pPanelLayer->setScore(m_pStarUtil->getScore(), 0.6f);
		if (!m_bIsStageClear && m_pStarUtil->isStageClear()){
			m_pPanelLayer->setStageClear(true);
			m_bIsStageClear = true;
		}
		this->runAction(CCSequence::create(CCDelayTime::create(1.0f), CCCallFunc::create(this, callfunc_selector(StageScene::refreshStar)),
			CCCallFunc::create(this, callfunc_selector(StageScene::isGameOver)), NULL));
		m_pStarUtil->findStarMax();
		unschedule(schedule_selector(StageScene::showMaxStar));
		schedule(schedule_selector(StageScene::showMaxStar), SHOW_TIPS_LATER);
	}
}

void StageScene::showShop(){
	if (!m_bActive || getChildByTag(TAG_SHOP_LAYER)){
		return;
	}
	ShopLayer *pShop = ShopLayer::create();
	pShop->setOnUpdateListener(CCCallFunc::create(this, callfunc_selector(StageScene::updateCoins)));
	addChild(pShop, Z_ORDER_SHOP, TAG_SHOP_LAYER);
}

void StageScene::updateCoins(){
	if (m_pPanelLayer){
		m_pPanelLayer->setCoins(UserInfo::getCoins());
	}
}

void StageScene::goToMenu(){
	CCDirector::sharedDirector()->replaceScene(getTansitionScene(Menu::scene()));
}


void StageScene::showMagicPanel(bool isShow){
	if (m_pMagicLayer == NULL){
		m_pMagicLayer = CCLayer::create();
		CCSprite *magicBg = CCSprite::create("paint_bg.png");
		magicBg->setPosition(VisibleRect::center());
		m_pMagicLayer->addChild(magicBg);
		float divWidthX = DESIGN_WIDTH / 12;
		CCMenu *pMenu = CCMenu::create();
		for (int i = 0; i < 5; i++){
			CCSprite *starMagic = CCSprite::create(g_starFrameNameArray[i][0].c_str());
			CCSprite *starMagicSelected = CCSprite::create(g_starFrameNameArray[i][0].c_str());
			starMagicSelected->setScale(1.1f);
			CCMenuItemSprite* pMagic = CCMenuItemSprite::create(starMagic, starMagicSelected, this, menu_selector(StageScene::magicMenuCallback));
			pMagic->setTag(TAG_STAR_1 + i);
			pMagic->setPosition(ccp(divWidthX + i * divWidthX * 2, magicBg->getPositionY()));
			pMenu->addChild(pMagic);
		}
		CCSprite *backMagic = CCSprite::create("paint_back.png");
		CCSprite *backMagicSelected = CCSprite::create("paint_back.png");
		backMagicSelected->setScale(1.1f);
		CCMenuItemSprite* pBackMagic = CCMenuItemSprite::create(backMagic, backMagicSelected, this, menu_selector(StageScene::magicMenuCallback));
		pBackMagic->setTag(TAG_MAGIC_BACK);
		pBackMagic->setPosition(ccp(DESIGN_WIDTH - divWidthX - pBackMagic->getContentSize().width / 2, magicBg->getPositionY()));
		pMenu->addChild(pBackMagic);
		pMenu->setPosition(CCPointZero);
		m_pMagicLayer->addChild(pMenu);

		CCSprite *pArrowSp = CCSprite::create("paint_arrow.png");
		pArrowSp->setPosition(ccp(VisibleRect::center().x,
			magicBg->getPositionY() - magicBg->getContentSize().height / 2 - pArrowSp->getContentSize().height / 2 + 10));
		m_pMagicLayer->addChild(pArrowSp, 1, TAG_MAGIC_ARROW);
		addChild(m_pMagicLayer, Z_ORDER_SHOP);
	}
	if (m_iSeletedIndex.x == -1 || m_iSeletedIndex.y == -1){
		m_pMagicLayer->setVisible(false);
		if (m_pPanelLayer){
			m_pPanelLayer->disableSkill();
			m_pPanelLayer->setTouchEnabled(true);
		}
		return;
	}
	int tag = StarUtil::getTagByIndex(m_iSeletedIndex);
	if (isShow){
		CCSprite *pArrowSp = (CCSprite*)(m_pMagicLayer->getChildByTag(TAG_MAGIC_ARROW));
		pArrowSp->setPositionX((m_iSeletedIndex.x + 1) * STAR_SIZE - STAR_SIZE / 2);
		m_pMagicLayer->setPositionY((ROWS_SIZE - m_iSeletedIndex.y) * STAR_SIZE - STAR_SIZE / 2 - DESIGN_HEIGHT / 2 + 70);
		playStarAnimation(tag, true);
	}
	else{
		playStarAnimation(tag, false);
	}
	m_pMagicLayer->setVisible(isShow);
	if (m_pPanelLayer){
		m_pPanelLayer->setTouchEnabled(!isShow);
	}
}

void StageScene::magicMenuCallback(CCObject *pSender){
	CCNode *pNode = dynamic_cast<CCNode *>(pSender);
	int starTag = StarUtil::getTagByIndex(m_iSeletedIndex);
	playStarAnimation(starTag, false);
	if (pNode) {
		int tag = pNode->getTag();
		switch (tag) {
		case TAG_STAR_4:
		case TAG_STAR_2:
		case TAG_STAR_1:
		case TAG_STAR_3:
		case TAG_STAR_5:
		{
						   m_nSkillType = tag;
						   onMagicClick(m_iSeletedIndex, CCPointZero);
						   m_iSeletedIndex.x = -1;
						   m_iSeletedIndex.y = -1;
						   showMagicPanel(false);
		}
			break;
		case TAG_MAGIC_BACK:
			m_nSkillType = TAG_MAGIC_BACK;
			m_iSeletedIndex.x = -1;
			m_iSeletedIndex.y = -1;
			showMagicPanel(false);
			break;
		case TAG_SHOP:
			break;
		default:
			break;
		}
	}
}

void StageScene::isGameOver(){
	if (m_pStarUtil->isStageOver()){
		m_bActive = false;
		m_nSkillType = -1;
		m_pPanelLayer->setTouchEnabled(false);
		m_pStarUtil->stageOverScore();

		this->runAction(
			CCSequence::create(
			CCDelayTime::create(0.5f),
			CCCallFunc::create(this, callfunc_selector(StageScene::stageOver)),
			NULL
			)
			);
	}
	else{
		showRandomLiBao();
	}
}

void StageScene::menuCallback(CCObject *pSender){
	CCNode *pNode = dynamic_cast<CCNode *>(pSender);

	if (pNode) {
		int tag = pNode->getTag();
		switch (tag) {
		case TAG_GAMEOVER_BACK:
			if (m_pQuickBuyLayer != NULL && m_pQuickBuyLayer->isVisible()){
				return;
			}
			goToMenu();
			break;
		case TAG_GAMEOVER_COINTINE:
		{
									  if (m_pQuickBuyLayer != NULL && m_pQuickBuyLayer->isVisible()){
										  return;
									  }
									  CCLabelTTF *remainTimeLabel = (CCLabelTTF*)m_pGameOverLayer->getChildByTag(TAG_GAMEOVE_TIME);
									  if (remainTimeLabel){
										  unschedule(schedule_selector(StageScene::remaindContinue));
										  remainTimeLabel->setVisible(false);
									  }
									  if (UserInfo::getCoins() >= GameData::getInstance()->m_nFuHuoUseCoin){
										  UserInfo::expendCoins(GameData::getInstance()->m_nFuHuoUseCoin);
										  m_pPanelLayer->removeChild(m_pGameOverLayer);
										  m_pGameOverLayer = NULL;
										  m_pPanelLayer->setTargetCoins(UserInfo::getCoins());
										  if (GameData::getInstance()->m_bResetScore){
											  m_pStarUtil->setScore(m_pStarUtil->getCurStageScore());
										  }
										  else{
											  m_pStarUtil->setScore(m_pStarUtil->getNewScore());
										  }
										  if (GameData::getInstance()->m_bResetHard){
											  m_pStarUtil->m_fCurrentPersent = 0;
										  }
										  bool tempShowLibao = m_bShowLiBao;
										  newStage(true);
										  m_bShowLiBao = tempShowLibao;
									  }
									  else{
#if(PAY_DOUBLE_SHOW == 1 || PAY_PLUGIN_TYPE_XINYINHE == 1)
										  showQuickBuy(true);
#else
										  MyPurchase::sharedPurchase()->payForProducts(this, PAY_TYPE_EXIT_LIBAO, callfuncN3I_selector(StageScene::quickBuyCallBack));
#endif
									  }
		}
			break;
		default:
			break;
		}
	}
}
void StageScene::quickBuyCallBack(CCNode* nouse, int payType, int payResult, int clickTag){
	if (QUICK_MENU_CLOSE_TAG == clickTag){
		showQuickBuy(false);
		if (UserInfo::getFirstLogin()){
			UserInfo::setFirstLogin();
			UserInfo::addCoins(GameData::getInstance()->m_nDefaultCoin);
			m_pPanelLayer->showCoinsAni();
		}
		return;
	}
	if (payResult != PAY_RESULT_SUCCESS){
		return;
	}
	showQuickBuy(false);
	if (UserInfo::getFirstLogin()){
		UserInfo::setFirstLogin();
		UserInfo::addCoins(GameData::getInstance()->m_nDefaultCoin);
	}
	m_pPanelLayer->showCoinsAni();
	m_pPanelLayer->updateProCountLabel(USERINFO_PRO_TYPE_BOMB);
	m_pPanelLayer->updateProCountLabel(USERINFO_PRO_TYPE_PAINT);
	m_pPanelLayer->updateProCountLabel(USERINFO_PRO_TYPE_REFLASH);
}

void StageScene::showQuickBuy(bool isShow){
	if (isShow){
		if (m_pQuickBuyLayer == NULL){
			m_pQuickBuyLayer = QuickBuyLayer::create(m_pStarUtil->getStage() + 1);
			m_pQuickBuyLayer->setCallbackListener(this, callfuncN3I_selector(StageScene::quickBuyCallBack));
			m_pPanelLayer->addChild(m_pQuickBuyLayer, Z_ORDER_MENU + 1);
		}
		m_bActive = false;
		m_pPanelLayer->setTouchEnabled(false);

	}
	else{
		if (m_pQuickBuyLayer != NULL){
			m_pPanelLayer->removeChild(m_pQuickBuyLayer);
			m_pQuickBuyLayer = NULL;
		}
		if (m_pGameOverLayer != NULL && m_pGameOverLayer->isVisible()){
			return;
		}
		m_bActive = true;
		m_pPanelLayer->setTouchEnabled(true);
	}
}

void StageScene::playStarAnimation(int tag, bool isPlay){
	CCSprite *pStarSprite = (CCSprite *)m_pBatchNode->getChildByTag(tag);
	if (pStarSprite){
		if (isPlay){
			pStarSprite->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(0.7f, 0.8f), CCScaleTo::create(0.7f, 1.0f), NULL)));
		}
		else{
			pStarSprite->stopAllActions();
			pStarSprite->setScale(1.0f);
		}
	}
}

void StageScene::showMaxStar(float fDelta){
	unschedule(schedule_selector(StageScene::showMaxStar));
	Star *pStar;
	CCSprite *pStarSprite;
	int tag;
	for (int r = ROWS_SIZE - 1; r >= 0; r--){
		for (int c = 0; c < COlUMNS_SIZE; c++){
			pStar = &(m_pStarUtil->star[c][r]);
			if (pStar->state != STAR_SELECT_MAX || pStar->color == STAR_COLOR_NULL){
				continue;
			}
			tag = pStar->intTag;
			pStarSprite = (CCSprite *)m_pBatchNode->getChildByTag(tag);

			if (pStarSprite) {
				pStarSprite->runAction(CCRepeat::create(
					CCSequence::create(CCScaleTo::create(0.8f, 0.8f), CCScaleTo::create(0.8f, 1.0f), CCDelayTime::create(0.5f), NULL), 3));
			}
		}
	}
	schedule(schedule_selector(StageScene::showMaxStar), SHOW_TIPS_TIME);
}