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

class StageModel
{
public:
	static StageModel *theModel();
	int getCurDirection(){ return m_direction; }

	StarNode *getStarData(LogicGrid &grid);
	void saveStage(){ m_savingHelper.saveCurState(); }

	void initStarsData();
private:
	StageModel();
	~StageModel();

	void resetStarsData();
	void releaseStarsData();
private:
	bool m_isNewStage;
	int m_direction;
	int m_curStage;
	SavingHelper m_savingHelper;
	StarNode *m_starNodes[ROWS_SIZE][COlUMNS_SIZE];
	//std::vector<std::vector<int>> m_starNodes;
};
#endif