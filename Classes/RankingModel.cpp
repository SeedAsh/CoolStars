#include "RankingModel.h"
#include "CommonUtil.h"
#include "SqliteHelper.h"
#include "DataManager.h"
#include "StageModel.h"
#include "StageBaseInfo.h"
#include "PetManager.h"
#include "UserInfo.h"
USING_NS_CC;
using namespace std;
using namespace CommonUtil;

RankingModel *RankingModel::theModel()
{
	static RankingModel model;
	return &model;
}

static char getRandomLetter()
{
	bool isLowCase = getRandomValue(0, 1) == 1 ? true : false;
	int letterIndex = getRandomValue(0, 25);
	char letter = isLowCase ? letterIndex + 'a' : letterIndex + 'A';
	return letter;
}

string RankingModel::getRandomName()
{
	string name;

	//第一位必然是字母
	name += getRandomLetter();
	for (int i = 0; i < kMaxLength - 1; ++i)
	{
		bool isExit = getRandomValue(0, 1) == 1 ? true : false;
		if (isExit)
		{
			name += getRandomLetter();
		}
	}

	//字母不够kMaxLength的补数字
	for (int i = name.size(); i < kMaxLength; ++i)
	{
		bool isExit = getRandomValue(0, 1) == 1 ? true : false;
		char numLetter = getRandomValue(0, 9) + '0';
		if(isExit)
		{
			name += numLetter;
		}
	}
	
	return name;
}

static bool isLetter(char ch)
{
	return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

static bool isNumber(char ch)
{
	return ch >= '0' && ch <= '9';
}

bool RankingModel::isValidName(string name)
{
	if (name.empty()) return false;
	if (name.size() > kMaxLength) return false;

	for (auto i = 0; i < name.size(); ++i)
	{
		if (!isLetter(name[i]) && !isNumber(name[i]))
		{
			return false;
		}
	}
	return true;
}

void RankingModel::loadData()
{
	SqliteHelper helper(DB_SAVING);
	string sql = "select * from save_ranking";
	auto result = helper.readRecord(sql.c_str());
	auto data = result[0];

	m_alreadyOpenRanking = atoi(data[1]) == 1;

	if (m_alreadyOpenRanking)
	{
		m_myName = data[2];
		RankingOpponent::theOpponent()->loadLastSavedData();
	}
}

void RankingModel::initFirstOpenRanking(string myName)
{
	SqliteHelper sqlHelper(DB_SAVING);
	char str[100] = { 0 };

	m_alreadyOpenRanking = true;
	sprintf(str, "update save_ranking set %s = '%d' where id = 1;", "first_open_ranking", m_alreadyOpenRanking ? 1 : 0);
	sqlHelper.executeSql(str);

	m_myName = myName;
	sprintf(str, "update save_ranking set %s = '%s' where id = 1;", "my_name", m_myName.c_str());
	sqlHelper.executeSql(str);
	//排序表数据
	auto datas = DataManagerSelf->getRankingConfigs();
	sort(datas.begin(), datas.end(), [=](RankingConfig data1, RankingConfig data2)->bool
	{
		if (data1.score > data2.score) return true;
		else if (data1.score == data2.score)
		{
			return data1.ownPetPercent > data2.ownPetPercent;
		}
		return false;
	});

	//根据 最高得分 和 宠物拥有比 计算排名。对手的排名在玩家之前
	int topScore = StageModel::theModel()->getStageInfo()->getTopScore();
	int ownPetNum = PetManager::petMgr()->getOwnedPetIds().size();
	int ownPetPercent = int((float)ownPetNum / PETS_AMOUNT * 100);
	auto iter = find_if(datas.begin(), datas.end(), [=](RankingConfig data)->bool
	{
		if (topScore == data.score)
		{
			return ownPetNum > data.ownPetPercent;
		}
		return topScore > data.score;
	});

	int opponentId = datas.size();
	//如果玩家不是最后一名
	if (iter != datas.end())
	{
		int temp = iter->id - 1;
		//如果玩家不是第一名
		if (temp != 0)
		{
			opponentId = temp;
		}
	}

	RankingOpponent::theOpponent()->firstInitData(opponentId);
}

bool RankingModel::isOverOpponent()
{
	return false;
}

RankingData RankingModel::getMyRankingData()
{
	int stage = StageModel::theModel()->getStageInfo()->getTopStage();
	int ownPetNum = PetManager::petMgr()->getOwnedPetIds().size();
	int ownPetPercent = int((float)ownPetNum / PETS_AMOUNT * 100);

	RankingData data;
	data.name = m_myName;
	data.stage = stage;
	data.type = kPlayer;
	data.ownPetPercent = ownPetPercent;
}

vector<RankingData> RankingModel::getCurRanking()
{
	auto configs = DataManagerSelf->getRankingConfigs();
	for (size_t i = 0; i < configs.size(); ++i)
	{
		RankingData data;
		data.type = kData;
		data.name = configs[i].name;
		data.stage = configs[i].score;
	}

}