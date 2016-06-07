#include "DataManager.h"
#include "SqliteHelper.h"
#include "StarNode.h"
#include "cocos2d.h"
#include "CommonUtil.h"

DataManager::DataManager(void)
{

}

DataManager::~DataManager(void)
{

}

void DataManager::LoadData()
{
	loadSystemConfig();
	loadStageConfig();
	loadStarsConfig();
	loadCommonPetsConfig();
}

void DataManager::loadStarsConfig()
{
	SqliteHelper helper(DB_COOLSTAR);
	auto result = helper.readRecord("select * from stars");
	for (auto iter = result.begin(); iter != result.end(); ++iter)
	{
		StarsConfig config;
		assert((*iter).size() == 6);

		config.id = atoi((*iter)[0]);
		config.desc = (*iter)[1];
		config.score = atoi((*iter)[2]);
		config.resPath = (*iter)[3];
		config.extra = atoi((*iter)[4]); 
		config.explosionPath = (*iter)[5];

		m_starsConfig.push_back(config);
	}
}

const StarsConfig &DataManager::getStarsConfig(int starType)
{ 
	assert(starType > kEmpty && starType < kStarTypeCount);
	if (starType > kEmpty && starType < kStarTypeCount)
	{
		return m_starsConfig[starType - 1];
	}
	else
	{
		return m_starsConfig[0];
	}
}

void DataManager::loadCommonPetsConfig()
{
	SqliteHelper helper(DB_COOLSTAR);
	auto result = helper.readRecord("select * from common_pets");

	for (auto iter = result.begin(); iter != result.end(); ++iter)
	{
		PetsConfig config;
		assert((*iter).size() == 7);

		config.id = atoi((*iter)[0]);
		config.skillId = atoi((*iter)[4]);
		/*
		config.energy = (*iter)[1];
		config.count = atoi((*iter)[2]);
		config.upgrade = (*iter)[3];
		config.desc = atoi((*iter)[4]);
		*/
		const string path = (*iter)[5];
		char chars[10] = { 0 };
		for (int i = kColorRed; i <= kColorPurple; ++i)
		{
			sprintf(chars, "%d", i);
			string str = path;
			str.replace(str.find("*"), 1, chars);
			config.iconPath.push_back(str);
		}

		m_petsConfig.push_back(config);

	}
}

const PetsConfig &DataManager::getCommonPetsConfig(int petId)
{
	assert(petId > 0 && petId < CommonPetsAmount);
	return m_petsConfig[petId - 1];
}

void DataManager::loadStageConfig()
{
	SqliteHelper sqlHelper(DB_COOLSTAR);
	auto result = sqlHelper.readRecord("select * from stages");
	assert(!result.empty());

	for (auto iter = result.begin(); iter != result.end(); ++iter)
	{
		auto rowData = *iter;
		StageConfig stage;
		stage.id = atoi(rowData[0]);
		stage.tagetType = atoi(rowData[1]);
		stage.targetParam = CommonUtil::parseStrToInts(rowData[2]);
		stage.step= atoi(rowData[3]);
		stage.direction = CommonUtil::parseStrToInts(rowData[4]);

		m_stagesConfig.push_back(stage);
	}
}

const StageConfig &DataManager::getStageConfig(int stage)
{
	assert(stage > 0 && stage <= m_petsConfig.size());
	return m_stagesConfig[stage - 1];
}

void DataManager::getNewStageStarsData(std::vector<std::vector<int>> &stars, int stageNum)
{
	vector<StageConfig> m_stagesConfig;
	SqliteHelper sqlHelper(DB_COOLSTAR);
	
	char str[100] = { 0 };
	sprintf(str, "select * from stage%d", stageNum);
	auto result = sqlHelper.readRecord(str);

	assert(result.size() == ROWS_SIZE);
	for (auto iter = result.begin(); iter != result.end(); ++iter)
	{
		assert((*iter).size() == COlUMNS_SIZE);

		vector<int> oneRow;
		for (size_t i = 0; i < (*iter).size(); ++i)
		{
			oneRow.push_back(atoi((*iter)[i]));
		}
		stars.push_back(oneRow);
	}
	
}

void DataManager::loadSystemConfig()
{
	SqliteHelper sqlHelper(DB_COOLSTAR);
	auto result = sqlHelper.readRecord("select * from system");
	assert(result.size() == 1);

	m_systemConfig.stageAmount = atoi(result[0][0]);
}

const SystemConfig &DataManager::getSystemConfig()
{
	return m_systemConfig;
}
