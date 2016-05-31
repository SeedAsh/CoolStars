#ifndef __STAGEMODEL_H__
#define __STAGEMODEL_H__

#define MOVE_UP 0
#define MOVE_DOWN 1
#define MOVE_LEFT 2
#define MOVE_RIGHT 3

#include "cocos2d.h"
#include "SavingHelper.h"
#include "ConfData.h"
#include "StarNode.h"
#include "DataManager.h"

#define NOTIFY_VIEWS(_FUNC_ ,...)						\
for (size_t index = 0; index < m_views.size(); ++index) \
{														\
	m_views[index]->_FUNC_(__VA_ARGS__);				\
}											

struct IStageView
{
	virtual void createNewStar(StarNode *node){}
	virtual void stepsChanged(){}
	virtual void scoreChanged(){}
	virtual void coinsChanged(){}
	
};

class StageModel
{
public:
	static StageModel *theModel();

	StarNode *getStarData(const LogicGrid &grid);
	void saveStage(){ m_savingHelper.saveCurState(); }

	void initStarsData();
    void moveStars();
	void removeStarNode(StarNode *node);
	void genNewStars();

	void moveOneStep();
public:
	void addView(IStageView *view);
	void removeView(IStageView *view);
private:
	StageModel();
	~StageModel();

	int getCurDirection();
	void resetStarsData();
    void moveStar(StarNode *node);
	bool isGridEmpty(const LogicGrid &grid);
;
private:
	bool m_isNewStage;
	int m_curStage;
	int m_step;
	StageInfo m_currentStageInfo;
	SavingHelper m_savingHelper;
	std::vector<StarNode *> m_starNodes;
	std::vector<IStageView *> m_views;
};
#endif