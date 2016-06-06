#ifndef __STAGEBASEINFO_H__
#define __STAGEBASEINFO_H__
class StageBaseInfo
{
public:
	StageBaseInfo();
public: //基本信息存取
	int getCurStep(){ return m_step; }
	void setCurStep(int step){ m_step = step; }
	int getLeftStep();
	void addStep() {m_step++; }

	bool isNewStage(){ return m_isNewStage; }
	void setIsNewStage(bool isNewStage){ m_isNewStage = isNewStage; }

	int getCurScore(){ return m_curScore; }
	void addCurScore(int value){ setCurScore(m_curScore + value); }
	void setCurScore(int score);

	int getTopScore(){ return m_topScore; }
	void setTopScore(int topScore){ m_topScore = topScore; }

	int getCurStage(){ return m_curStage; }
	void setCurStage(int stage){ m_curStage = stage; }
	bool isTheLastStage();
	void toNextStage();

	int getCurDirection();

	void init();
private:
	bool m_isNewStage;//是否为新关卡
	int m_curStage;
	int m_step;
	int m_curScore;
	int m_topScore;
};
#endif