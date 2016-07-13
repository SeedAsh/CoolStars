#ifndef __STAGEBASEINFO_H__
#define __STAGEBASEINFO_H__
#include "cocos2d.h"
#include "DataConfig.h"
#include "CommonMacros.h"

struct IStageDataView
{
	virtual void onStepsChanged(){}
	virtual void onScoreChanged(){}
	virtual void onCoinsChanged(){}
};

class StageDataMgr
{
public: //������Ϣ��ȡ
	static StageDataMgr *theMgr();
	void newRound();
public:
	int getCurStep(){ return m_step; }
	void setCurStep(int step);
	int getLeftSteps();
	void addStep() { setCurStep(m_step + 1); }

	int getCurScore(){ return m_curScore; }
	void setNextScoreBonus(int bonus){ m_curScoreBonus = bonus; }
	void addCurScore(int value);
	void setCurScore(int score);
	int getTargetScore();

	int getTopScore(){ return m_topScore; }
	void setTopScore(int topScore){ m_topScore = topScore; }

	int getCurStage(){ return m_curStage; }
	void setCurStage(int stage){ m_curStage = stage; }
	bool isTheLastStage();
	//��ǰ����ս�����ؿ�
	int getTopStage(){ return m_topStage; }
	void setTopStage(int stage){ m_topStage = stage; }

	int getCurDirection();

	void toNextStage();
	void getStageStars(std::vector<std::vector<StageStarInfo>> &stars);
	void init();
	void doSave();
	void reset(int gameType = kNormalType);
public:
	void addView(IStageDataView *view);
	void removeView(IStageDataView *view);
private:
	StageDataMgr();
private:
	std::vector<IStageDataView *> m_views;
	int m_curStage;
	int m_topStage;
	int m_step;
	int m_curScore;
	int m_topScore;
	float m_curScoreBonus;
};
#endif