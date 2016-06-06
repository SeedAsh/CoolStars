#ifndef __STAGEMODEL_H__
#define __STAGEMODEL_H__

#include "cocos2d.h"
#include "ConfData.h"
#include "StarNode.h"
#include "DataManager.h"
#include "StageTarget.h"
#include "StageBaseInfo.h"

#define NOTIFY_VIEWS(_FUNC_ ,...)						\
for (size_t index = 0; index < m_views.size(); ++index) \
{														\
	m_views[index]->_FUNC_(__VA_ARGS__);				\
}											

struct IStageView
{
	virtual void onCreateNewStar(StarNode *node){}
	virtual void onStepsChanged(){}
	virtual void onScoreChanged(){}
	virtual void onCoinsChanged(){}
	virtual void onGameOver(int isWon){}
	
};

class StageModel
{
public:
	static StageModel *theModel();
public: //对星星的操作接口
	StarNode *getStarNode(const LogicGrid &grid);
	std::vector<StarNode *> &getStarNodes(){ return m_starNodes; }
	void initStarsData();
    void moveStars();
	void removeStarNode(StarNode *node);
	void genNewStars();
	void moveOneStep();
	void addScore(int value);
	void replaceStar(const StarAttr &attr);
	
public:
	StageBaseInfo *getStageInfo(){ return &m_stageInfo; }
	StageTarget *getStageTarget(){ return &m_target; }
private:
	void gameOver(bool isWon);
public:
	void addView(IStageView *view);
	void removeView(IStageView *view);
private:
	StageModel();
	~StageModel();

	void resetStarsData();
    void moveStar(StarNode *node);
	bool isGridEmpty(const LogicGrid &grid);
private:
	StageBaseInfo m_stageInfo;
	std::vector<StarNode *> m_starNodes;
	std::vector<IStageView *> m_views;
	StageTarget m_target;
private:
	enum Direction
	{
		kMoveUp,		
		kMoveDown,	
		kMoveLeft,	
		kMoveRight,
	};
};
#endif