#ifndef __STAGEMODEL_H__
#define __STAGEMODEL_H__

#include "cocos2d.h"
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
	virtual void onCreateNewStar(StarNode *node){}
	virtual void onStepsChanged(){}
	virtual void onScoreChanged(){}
	virtual void onCoinsChanged(){}
	virtual void onGameOver(){}
	
};

class StageModel
{
public:
	static StageModel *theModel();
public: //对星星的操作接口
	StarNode *getStarNode(const LogicGrid &grid);
	std::vector<StarNode *> &getStarNodes(){ return m_starNodes; }
	void initStarsData();
	void loadLastSavedStars();
	void loadNewStageStars();
    void moveStars();
	void removeStarNode(StarNode *node);
	void genNewStars();
	void moveOneStep();
	void replaceStar(const StarAttr &attr);
public: //基本信息存取
	int getStep(){ return m_step; }
	void setStep(int step){ m_step = step; }
	void setIsNewStage(bool isNewStage){ m_isNewStage = isNewStage; }
	int getCurScore(){return m_curScore; }
	void setCurScore(int score){ m_curScore = score; }
	int getTopScore(){return m_topScore; }
	void setTopScore(int topScore){ m_topScore = topScore; }
	int getCurStage(){ return m_curStage; }
	void setCurStage(int stage){ m_curStage = stage; }
private:
	void gameOver();
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
	int m_topScore;
	StageConfig m_stageInfo;
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