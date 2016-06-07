#ifndef __STAGEBASEINFO_H__
#define __STAGEBASEINFO_H__
#include "cocos2d.h"
class StageBaseInfo
{
public:
	StageBaseInfo();
public: //基本信息存取
	int getCurStep(){ return m_step; }
	void setCurStep(int step){ m_step = step; }
	int getLeftStep();
	void addStep() {m_step++; }

	int getCurScore(){ return m_curScore; }
	void addCurScore(int value){ setCurScore(m_curScore + value); }
	void setCurScore(int score);

	int getTopScore(){ return m_topScore; }
	void setTopScore(int topScore){ m_topScore = topScore; }

	int getCurStage(){ return m_curStage; }
	void setCurStage(int stage){ m_curStage = stage; }
	bool isTheLastStage();

	int getCurDirection();

	void newGame();//新游戏
	void resumeGame();
	void toNextStage();
	void getStageStars(std::vector<std::vector<int>> &stars);
	void init();
	void doSave();
private:
	void reset();

private:
	bool m_isNewStage;//是否为新关卡
	int m_curStage;
	int m_step;
	int m_curScore;
	int m_topScore;
};
#endif