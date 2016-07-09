#ifndef __STAGEUILAYER_H___
#define __STAGEUILAYER_H___ 

#include "cocos2d.h"
#include "StarsController.h"
#include "StageLayersMgr.h"
#include "StageDataMgr.h"
#include <unordered_map>
USING_NS_CC;

class StagePetNode;
class UiLayout;
class StageStateOwner;
class StageUiLayer
    : public CCLayer
	, public IStageDataView
	, public IStarsControlView
	, public IStageLayer
{
public:
	StageUiLayer();
    ~StageUiLayer(void);

	static StageUiLayer *create();
    virtual bool init();
	void initTopUi();
	void initPets();
	void initBottomUi();
	std::unordered_map<int, cocos2d::CCPoint> getPetViewsInfo();
public:
	virtual void onStepsChanged();
	virtual void onScoreChanged();
	virtual void onCoinsChanged();
	virtual void onGameOver(int isWon);
	virtual void onNormalStarErased(cocos2d::CCPoint pos, int color);
	virtual void onHighLightPets(const std::vector<int> &petIds);
	virtual void onToNormalState();
public:
	void showChangeColorPanel(const LogicGrid &grid);
private:
	virtual void onEnter();
	virtual void onExit();
	void handlePetClicked(int petId);
	void handlePropsItemClicked(int type);
	void showGameOverHint();
	void showPetsSkillPanel();

	void onPauseBtnClicked(CCObject *pSender);

private:

private:
	static const int kZorder_Pet = 10;
	static const int kZorder_Dialog = 20;
	UiLayout *m_bottomUi;
	UiLayout *m_topUi;
	StageStateOwner *m_stateOwner;
	std::unordered_map<int , StagePetNode *>m_petViews;
};
#endif // __PANELLLAYER_H__