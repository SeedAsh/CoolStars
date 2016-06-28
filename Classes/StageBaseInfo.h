#ifndef __STAGEBASEINFO_H__
#define __STAGEBASEINFO_H__
#include "cocos2d.h"
#include "DataConfig.h"
#include "CommonMacros.h"

class StageBaseInfo
{
public:
	StageBaseInfo();
public: //基本信息存取
	int getCurStep(){ return m_step; }
	void setCurStep(int step){ m_step = step; }
	int getLeftSteps();
	void addStep() {m_step++; }

	int getCurScore(){ return m_curScore; }
	void setNextScoreBonus(int bonus){ m_curScoreBonus = bonus; }
	void addCurScore(int value);
	void setCurScore(int score);

	int getTopScore(){ return m_topScore; }
	void setTopScore(int topScore){ m_topScore = topScore; }

	int getCurStage(){ return m_curStage; }
	void setCurStage(int stage){ m_curStage = stage; }
	bool isTheLastStage();
	//当前可挑战的最大关卡
	int getTopStage(){ return m_topStage; }
	void setTopStage(int stage){ m_topStage = stage; }

	int getCurDirection();

	void toNextStage();
	void getStageStars(std::vector<std::vector<StageStarInfo>> &stars);
	void init();
	void doSave();
	void reset(int gameType = kNormalType);
private:


private:
	int m_curStage;
	int m_topStage;
	int m_step;
	int m_curScore;
	int m_topScore;
	float m_curScoreBonus;
};
#endif