#include "SavingHelper.h"
#include "ConfData.h"
#include "SqliteHelper.h"
#include "StarNode.h"

USING_NS_CC;
using namespace std;
SavingHelper::SavingHelper()
{
}

SavingHelper::~SavingHelper()
{

}

void SavingHelper::saveCurStars()
{
}

void SavingHelper::getLastSavedStars(std::vector<std::vector<int>> &stars)
{
	SqliteHelper sqlHelper(DB_SAVING);
	auto result = sqlHelper.readRecord("select * from save_stars");

	assert(result.size() == ROWS_SIZE);
	//要做出错处理，出错则直接读新关卡数据
	for (auto iter = result.begin(); iter != result.end(); ++iter)
	{
		assert((*iter).size() == COlUMNS_SIZE);
		vector<int> line;
		for (size_t i = 0; i < (*iter).size(); ++i)
		{
			line.push_back(atoi((*iter)[i]));
		}
		stars.push_back(line);
	}
}

void SavingHelper::setPetsData()
{

}

PetData SavingHelper::getPetsData(int petId)
{
	SqliteHelper sqlHelper(DB_SAVING);
	char str[100] = { 0 };
	sprintf(str, "select * from save_pets where id = %d;", petId);
	auto result = sqlHelper.readRecord(str);
	assert(result.size() == 1);

	PetData data;
	data.petId = atoi(result[0][0]);
	data.commonid = atoi(result[0][1]);
	data.color = atoi(result[0][2]);
	data.level = atoi(result[0][3]);
	data.exp = atoi(result[0][4]);
	data.energy = atoi(result[0][5]);
	return data;
	
}

SavingHelper *SavingHelper::theHelper()
{
	static SavingHelper helper;
	return &helper;
}