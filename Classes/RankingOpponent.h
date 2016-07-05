#ifndef __RANKINGOPPONENT_H__
#define __RANKINGOPPONENT_H__
#include "cocos2d.h"
#include "RankingModel.h"

struct RankingData;
class RankingOpponent
{
public:
	static RankingOpponent *theOpponent();

	void loadLastSavedData();
	void firstInitData(int rankId);
	void saveData();

	void update();
	RankingData getRankingData();
	bool needUpdate();
private:
	RankingOpponent(){}
private:
	int m_opponentId;
	int m_lastDays;
	int m_ownPets;
	int m_stage;
};
#endif