#ifndef __STAGEMODEL_H__
#define __STAGEMODEL_H__

#include "cocos2d.h"
#include "SavingHelper.h"
#include "ConfData.h"
#include "StarNode.h"
#include "DataManager.h"
#include "StageTarget.h"

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

	StarNode *getStarNode(const LogicGrid &grid);
	std::vector<StarNode *> &getStarNodes(){ return m_starNodes; }

	void initStarsData();
    void moveStars();
	void removeStarNode(StarNode *node);
	void genNewStars();

	void moveOneStep();
	int getStep(){ return m_step;}
	void setStep(int step){ m_step = step; }
	void doSave();

	void setIsNewStage(bool isNewStage){m_isNewStage = isNewStage;}

	void replaceStar(const StarAttr &attr);
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

private:
	bool m_isNewStage;//是否为新关卡
	int m_curStage;
	int m_step;
	int m_curScore;
	int m_highScore;
	StageInfo m_currentStageInfo;
	std::vector<StarNode *> m_starNodes;
	std::vector<IStageView *> m_views;
	StageTarget m_target;
private:
	enum Direction
	{
		kMoveUp		= 1,
		kMoveDown	= 2,
		kMoveLeft	= 3,
		kMoveRight	= 4,
	};
};
#endif