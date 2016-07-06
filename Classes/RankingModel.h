#ifndef __RANKINGMODEL_H__
#define __RANKINGMODEL_H__
#include "cocos2d.h"
#include "RankingOpponent.h"
#include <unordered_map>
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
	
	bool operator >(RankingData data) const
	{
		if (stage == data.stage)
		{
			return ownPetPercent > data.ownPetPercent;
		}
		else
		{
			return stage > data.stage;
		}
	}
	
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
	std::unordered_map<int, RankingData> getNeighboursRanking();
private:
	std::vector<RankingData> getCurRanking();
	RankingData getMyRankingData();
private:
	static const int kMaxLength = 4;
	bool m_alreadyOpenRanking;

	std::string m_myName;
};
#endif