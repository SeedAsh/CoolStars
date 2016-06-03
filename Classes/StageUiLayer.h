#ifndef __STAGEUILAYER_H___
#define __STAGEUILAYER_H___ 

#include "cocos2d.h"
USING_NS_CC;
struct StageUiValue
{
	int step;
	std::vector<int> targets;
	int bestScore;
	int stage;
	int score;
	int coins;

};
struct IStageUiView
{
	virtual void stepsChanged(){}
	virtual void scoreChanged(){}
	virtual void coinsChanged(){}
};

class StageUiLayer
    : public CCLayer
	, public IStageUiView 	
{
public:
    StageUiLayer(void);
    ~StageUiLayer(void);

    static StageUiLayer *create();
    virtual bool init();
	void initTopUi();
	void initPets();
	void initBottomUi();
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
public:
	void stepsChanged();
	void scoreChanged();
	void coinsChanged();
private:
	void onQuitGame();
	void showGameOverHint();
	void deliveryScore(const CCPoint &from, int totalScore, int count);
	void setStageClear(bool clear);

	void onPauseBtnClicked(CCObject *pSender);
	void menuCallback(CCObject *pSender);
	CCMenuItemSprite *getItemSprite(std::string fileName, SEL_MenuHandler selector);
private:
    CCLabelTTF *m_pScoreLabel;
	CCLabelTTF *m_pStepLabel;
    CCLabelTTF *m_pScoreHint;
	CCLabelTTF *m_pCoins;

	CCLabelTTF *m_pBombLabel;
	CCLabelTTF *m_pPaintLabel;
	CCLabelTTF *m_pReflashLabel;

private:
	static const int kZorder_Pet = 10;

};
#endif // __PANELLLAYER_H__