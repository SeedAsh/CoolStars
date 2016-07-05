#include "RankingOpponent.h"
#include "DataManager.h"
#include "SqliteHelper.h"
#include "UserInfo.h"
#include "CommonUtil.h"
#include "CommonMacros.h"
using namespace std;
using namespace CommonUtil;
USING_NS_CC;

RankingOpponent *RankingOpponent::theOpponent()
{
	static RankingOpponent opponent;
	return &opponent;
}

void RankingOpponent::loadLastSavedData()
{
	SqliteHelper helper(DB_SAVING);
	string sql = "select * from save_opponent_ranking";
	auto result = helper.readRecord(sql.c_str());
	auto data = result[0];

	m_opponentId = atoi(data[1]);
	m_lastDays = atoi(data[2]);

	auto config = DataManagerSelf->getRankingConfig(m_opponentId);
	m_stage = atoi(data[3]);
	m_ownPets = atoi(data[4]);
}

void RankingOpponent::firstInitData(int rankId)
{
	SqliteHelper helper(DB_SAVING);
	char str[256] = { 0 };
	auto config = DataManagerSelf->getRankingConfig(m_opponentId);
	sprintf(str, "update save_opponent_ranking set %s = '%d' where id = 1;", "rank_id", m_opponentId);
	helper.executeSql(str);
	helper.closeDB();

	saveData();
}

void RankingOpponent::saveData()
{
	SqliteHelper helper(DB_SAVING);
	string sql;
	char str[256] = { 0 };
	auto config = DataManagerSelf->getRankingConfig(m_opponentId);
	sprintf(str, "update save_opponent_ranking set %s = '%d'", "last_days", m_lastDays);
	sql += str;
	sprintf(str, ",%s = '%d'", "last_score", m_stage);
	sql += str;
	int ownPetPercent = (int)((float)m_ownPets / PETS_AMOUNT * 100);
	sprintf(str, ",%s = '%d' where id = 1;", "last_own_pet_percent", ownPetPercent);
	sql += str;
	helper.executeSql(sql.c_str());
	helper.closeDB();
}

void RankingOpponent::update()
{
	if (!needUpdate()) return;

	int curdays = UserInfo::theInfo()->getDaysFromFirstPlay();
	m_lastDays = curdays;
	int days = curdays - m_lastDays;
	for (int i = 0; i < days; ++i)
	{
		m_stage += getRandomValue(1, 5);
		m_ownPets += getRandomValue(0, 3);
	}
	saveData();
}

bool RankingOpponent::needUpdate()
{
	int days = UserInfo::theInfo()->getDaysFromFirstPlay();
	return m_lastDays < days;
}

RankingData RankingOpponent::getRankingData()
{
	RankingData data;
	auto config = DataManagerSelf->getRankingConfig(m_opponentId);

	data.name = config.name;
	data.type = kOpponent;
	data.ownPetPercent = (int)((float)m_ownPets / PETS_AMOUNT * 100);
	data.score = m_stage;

	return data;
}