#ifndef __STAGESCENE_H__
#define __STAGESCENE_H__

#include "VisibleRect.h"
#include "StarUtil.h"
#include "PanelLayer.h"
#include "cocos-ext.h"
#include "ConfData.h"
#include "QuickBuyScene.h"
#include "DataManager.h"
USING_NS_CC_EXT;

#define Z_ORDER_BACKGROUND 0
#define Z_ORDER_STAR (Z_ORDER_BACKGROUND + 1)
#define Z_ORDER_EXPLOSION (Z_ORDER_STAR + 1)
#define Z_ORDER_PANEL (Z_ORDER_EXPLOSION + 1)
#define Z_ORDER_SHOP (Z_ORDER_PANEL + 1)
#define Z_ORDER_MENU (Z_ORDER_SHOP + 1)
#define Z_ORDER_UNLOCK (Z_ORDER_MENU + 1)
#define Z_ORDER_FAILED (Z_ORDER_UNLOCK + 1)
#define Z_ORDER_BUY (Z_ORDER_FAILED + 1)
#define Z_MENU_LAYER_TAG (Z_ORDER_BUY + 1)

#define TAG_PAUSE 1
#define TAG_BONUS (TAG_PAUSE + 1)
#define TAG_SHOP_LAYER (TAG_BONUS + 1)
#define TAG_FALIED_LAYER (TAG_SHOP_LAYER + 1)
#define TAG_BUY_LAYER (TAG_FALIED_LAYER + 1)

#define TAG_GAMEOVER_BACK 1
#define TAG_GAMEOVER_COINTINE 2
#define TAG_GAMEOVER_MENU 3
#define TAG_GAMEOVE_TIME 4

#define SHOW_TIPS_TIME 6
#define SHOW_TIPS_LATER 5

#define REMAIN_CONTINUE_TIME 10

static const char s_fire[] = "particle/fire.png";
static const string s_stars[] = {
    "particle/starp1.png",
    "particle/starp2.png",
    "particle/starp3.png",
    "particle/starp4.png",
    "particle/starp5.png"
};
class StageScene :
    public CCLayer
{
public:
    StageScene(void);
    ~StageScene(void);

    virtual bool init(bool resume = false);
	virtual void onEnter();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static CCScene* scene(bool resume = false);

    static StageScene* create(bool resume = false);

    virtual void keyBackClicked(void);
    virtual void keyMenuClicked(void);

    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);

    void starExplodedCallback(CCNode *pNode);
	void starExplodedInOrder(CCNode *pNode,void* result);
	void clickExpoledInOrder(Result result,CCPoint touchLocation);
    void stageOver();

    void onSave();
    void onPanelButtonClicked(int tag);
    void showScoreTips(int bonus,bool end = false);
    void updateCoins();
    void goToMenu();
	void showMagicPanel(bool isShow);
    CCScene* getTansitionScene(CCScene* scene);
	void quickBuyCallBack(CCNode* nouse, int clickTag, int payIntNoUse1,int payIntNoUse2);

	void showBombEffect();
private:
   // CCSpriteBatchNode *m_pBatchNode;
	CCNode *m_pBatchNode;
    PanelLayer *m_pPanelLayer;
    StarUtil *m_pStarUtil;
    CCPoint m_obOriginPoint;
    bool m_bIsStageClear;
    bool m_bBonusZeroPrompted;
    int m_nOverExplodedCount;
    int m_nSkillType;
    int m_nOldCoins;
	CCLayer *m_pMagicLayer;
	CCScale9Sprite *m_pGameOverLayer;
	QuickBuyLayer* m_pQuickBuyLayer;
	bool m_bActive;
	bool m_bResume;
	Index m_iSeletedIndex;
	float fireTime;
	float m_fRemainTime;
	bool m_bShowLiBao;

	void showRandomLiBao();
    void newStage(bool initStar = false);
    void explodeFire(CCPoint position);
    void explodeStar(CCPoint position, int totalParticles, const char *fileImage);
	void showMaxStar(float fDelta);
    void initBackgound();
    Index findTouchedIndex(CCPoint touch);
    inline CCPoint getStarPosition(int c, int r){
        return ccp(m_obOriginPoint.x + c * STAR_SIZE + STAR_SIZE / 2.0, 
            m_obOriginPoint.y - r * STAR_SIZE - STAR_SIZE / 2.0);
    }
    void onNormalClick(Index index, CCPoint touchLocation);
    void onMagicClick(Index index, CCPoint touchLocation);
	void magicMenuCallback( CCObject *pSender );
	void menuCallback( CCObject *pSender );
    void refreshStar();
    void updatePanel();
    void showPauseLayer();
    void showShop();
	void showStar();
	void starInitDone();
	void autoRemove(CCNode* node);

	void isGameOver();
	void showGameOver();
	void showStageWin();
	void doGameOver();
	void doStageWin();

	void showQuickBuy(bool isShow);
	void startFire();
	void fire(float dt);
	void remaindContinue(float dt);
	void playStarAnimation(int tag,bool isPlay);
	//void quickBuy();
	cocos2d::CCPoint getRandomPosForFire();


	StageInfo m_sCurrentStageInfo;
	int m_nLevel;
	void getStageValue();
	void loadStageInfo(int level);
	int m_nTargetType;
	int m_nTargetCount;
};
#endif // __STAGESCENE_H__