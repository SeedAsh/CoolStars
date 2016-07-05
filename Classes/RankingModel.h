#ifndef __RANKINGMODEL_H__
#define __RANKINGMODEL_H__
#include "cocos2d.h"
#include "RankingOpponent.h"

enum RankingType
{
	kPlayer,
	kOpponent,
	kData,
};

struct RankingData
{
	int type;
	std::string name;
	int stage;
	int ownPetPercent;
};

class RankingModel
{
public:
	static RankingModel *theModel();
	void loadData();

	std::string getRandomName();
	bool isValidName(std::string name);
	
	bool alreadyOpenRanking(){ return m_alreadyOpenRanking; }
	void initFirstOpenRanking(std::string myName);
	bool isOverOpponent();
private:
	std::vector<RankingData> getCurRanking();
	RankingData getMyRankingData();
private:
	const int kMaxLength = 4;
	bool m_alreadyOpenRanking;

	std::string m_myName;
};
#endif