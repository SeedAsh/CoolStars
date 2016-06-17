#ifndef __STAGEUILAYER_H___
#define __STAGEUILAYER_H___ 

#include "cocos2d.h"
#include "StageModel.h"
#include "StageLayersMgr.h"
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

class UiLayout;

class StageUiLayer
    : public CCLayer
	, public IStageView
	, public IStageLayer
{
public:
    StageUiLayer(void);
    ~StageUiLayer(void);

	CREATE_FUNC(StageUiLayer);
    virtual bool init();
	void initTopUi();
	void initPets();
	void initBottomUi();
public:
	virtual void onStepsChanged();
	virtual void onScoreChanged();
	virtual void onCoinsChanged();
	virtual void onGameOver(int isWon);

private:
	virtual void onEnter();
	virtual void onExit();
	void showGameOverHint();
	void showPetsSkillPanel();
	void deliveryScore(const CCPoint &from, int totalScore, int count);

	void onPauseBtnClicked(CCObject *pSender);
	void onReOrderBtnClicked(CCObject *pSender);
	void onChangeColorBtnClicked(CCObject *pSender);
	void onBombBtnClicked(CCObject *pSender);
	void menuCallback(CCObject *pSender);
private:

private:
	static const int kZorder_Pet = 10;
	static const int kZorder_Dialog = 20;
	UiLayout *m_bottomUi;
	UiLayout *m_topUi;

};
#endif // __PANELLLAYER_H__