#include "DataManager.h"
#include "SqliteHelper.h"
#include "StarNode.h"
#include "cocos2d.h"
#include "CommonUtil.h"
#include "PropManager.h"

using namespace CommonUtil;
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
	loadStarsColorConfig();
	loadPetCommonConfig();
	loadPetResConfig();
	loadPropsConfig();
	loadRankingConfig();
	loadShopConfig();
	loadPackageConfig();
	loadLotteryPet();
	loadLotteryOutput();
}

void DataManager::loadStarsConfig()
{
	SqliteHelper helper(DB_CONFIG);
	auto result = helper.readRecord("select * from stars");
	for (auto iter = result.begin(); iter != result.end(); ++iter)
	{
		StarsConfig config;
		auto data = (*iter);
		assert(data.size() == 8);

		config.id = atoi(data[0]);
		config.desc = data[1];
		config.score = atoi(data[2]);
		config.bornAnimationRes = data[3];
		config.resPath = data[4];
		config.explosionRes = data[5];
		config.linkStarTypes = CommonUtil::parseStrToInts(data[6]);
		config.eraseTypes = CommonUtil::parseStrToInts(data[7]);

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

void DataManager::loadPetCommonConfig()
{
	SqliteHelper helper(DB_CONFIG);
	auto result = helper.readRecord("select * from pets_common");

	for (auto iter = result.begin(); iter != result.end(); ++iter)
	{
		PetCommonConfig config;

		auto data = *iter;
		config.id = atoi(data[0]);
		config.maxEnergy = parseStrToInts(data[1]);
		assert(config.maxEnergy.size() == MAX_PET_LEVEL);
		config.skillPower = parseStrToInts(data[2]);
		assert(config.skillPower.size() == MAX_PET_LEVEL);
		config.foodToUpgrade = parseStrToInts(data[3]);
		assert(config.foodToUpgrade.size() == MAX_PET_LEVEL);
		config.skillTarget = atoi(data[4]);
		config.desc = atoi(data[5]);
		m_petCommonConfig.push_back(config);
	}
}

const PetCommonConfig &DataManager::getPetCommonConfig(int petCommonId)
{
	assert(petCommonId > 0 && petCommonId <= COMMON_PETS_AMOUNT);
	return m_petCommonConfig[petCommonId - 1];
}

void DataManager::loadPetResConfig()
{
	SqliteHelper helper(DB_CONFIG);
	auto result = helper.readRecord("select * from pets_res");

	for (auto iter = result.begin(); iter != result.end(); ++iter)
	{
		PetResConfig config;

		auto data = *iter;
		config.id = atoi(data[0]);
		config.commonId = atoi(data[1]);
		config.color = atoi(data[2]);
		config.petImgRes = data[3];
		config.skillRes = data[4];
		config.petAnimationRes = data[5];
		m_petResConfig.push_back(config);
	}
}

const PetResConfig &DataManager::getPetResConfig(int petId)
{
	assert(petId > 0 && petId <= PETS_AMOUNT);
	return m_petResConfig[petId - 1];
}

void DataManager::loadStageConfig()
{
	SqliteHelper sqlHelper(DB_STAGE);
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
	assert(stage > 0 && stage <= (int)m_stagesConfig.size());
	return m_stagesConfig[stage - 1];
}

void DataManager::getNewStageStarsData(std::vector<std::vector<StageStarInfo>> &stars, int stageNum)
{
	vector<StageConfig> m_stagesConfig;
	SqliteHelper sqlHelper(DB_STAGE);
	
	char str[100] = { 0 };
	sprintf(str, "select * from stage%d_stars", stageNum);
	auto result = sqlHelper.readRecord(str);

	assert(result.size() == ROWS_SIZE);
	for (auto iter = result.begin(); iter != result.end(); ++iter)
	{
		assert((*iter).size() == COlUMNS_SIZE);

		vector<StageStarInfo> oneRow;
		for (size_t i = 0; i < (*iter).size(); ++i)
		{
			StageStarInfo info;
			auto data = (*iter)[i];
			auto reInts = CommonUtil::parseStrToInts(data);
			info.starType = reInts[0];
			info.color = reInts[1];
			oneRow.push_back(info);
		}
		stars.push_back(oneRow);
	}
}

void DataManager::loadSystemConfig()
{
	SqliteHelper sqlHelper(DB_CONFIG);
	auto result = sqlHelper.readRecord("select * from system");
	assert(result.size() == 1);

	m_systemConfig.stageAmount = atoi(result[0][0]);
}

const SystemConfig &DataManager::getSystemConfig()
{
	return m_systemConfig;
}

void DataManager::loadStarsColorConfig()
{
	SqliteHelper sqlHelper(DB_CONFIG);
	auto result = sqlHelper.readRecord("select * from stars_color");
	assert(!result.empty());

	for (auto iter = result.begin(); iter != result.end(); ++iter)
	{
		auto data = *iter;
		StarsColorConfig config;
		config.id = atoi(data[0]);
		config.colorStarRes = data[1];
		config.colorExplosionRes = data[2];
		config.bounceBallRes = data[3];
		config.bounceBallExplosionRes = data[4];
		config.desc = data[5];

		m_starsColorConfig.push_back(config);
	}
}

const StarsColorConfig &DataManager::getStarsColorConfig(int color)
{
	assert(color > kColorRandom && color <= kColorPurple);
	return m_starsColorConfig[color];
}

void DataManager::loadPropsConfig()
{
	SqliteHelper sqlHelper(DB_CONFIG);
	auto result = sqlHelper.readRecord("select * from props");
	for (auto iter = result.begin(); iter != result.end(); ++iter)
	{
		auto data = *iter;
		PropsConfig config;
		config.id = atoi(data[0]);
		config.resPath = data[1];
		m_propsConfig.push_back(config);
	}
}

const PropsConfig &DataManager::getPropsConfig(int propsId)
{
	assert(0 <= propsId && propsId < kPorpTypeAmount);
	return m_propsConfig[propsId];
}

void DataManager::loadRankingConfig()
{
	SqliteHelper sqlHelper(DB_CONFIG);
	auto result = sqlHelper.readRecord("select * from ranking");
	for (auto iter = result.begin(); iter != result.end(); ++iter)
	{
		auto data = *iter;
		RankingConfig config;
		config.id = atoi(data[0]);
		config.name = data[1];
		config.score = atoi(data[2]);
		config.ownPetPercent = atoi(data[3]);
		m_rankingConfig.push_back(config);
	}
}

const RankingConfig &DataManager::getRankingConfig(int rank)
{
	assert(rank >= 0 && rank < (int)m_rankingConfig.size());
	return m_rankingConfig[rank];
}

void DataManager::loadShopConfig()
{
	SqliteHelper sqlHelper(DB_CONFIG);
	auto result = sqlHelper.readRecord("select * from shop");
	for (auto iter = result.begin(); iter != result.end(); ++iter)
	{
		auto data = *iter;
		ShopConfig config;
		config.id = atoi(data[0]);
		config.cost = atoi(data[1]);
		config.diamond = atoi(data[2]);
		config.iconPath = atoi(data[3]);
		m_shopConfig.push_back(config);
	}
}

const vector<ShopConfig> &DataManager::getShopConfig()
{
	return m_shopConfig;
}

void DataManager::loadPackageConfig()
{
	SqliteHelper sqlHelper(DB_CONFIG);
	auto result = sqlHelper.readRecord("select * from package");
	for (auto iter = result.begin(); iter != result.end(); ++iter)
	{
		auto data = *iter;
		PackageConfig config;
		config.id = atoi(data[0]);
		config.cost = atoi(data[1]);
		config.award = atoi(data[2]);
		config.titlePath = data[3];
		m_packageConfig.push_back(config);
	}
}

const PackageConfig &DataManager::getPackageConfig(int type)
{
	assert(type >= 0 && type < (int)m_packageConfig.size());
	return m_packageConfig[type];
}

void DataManager::loadLotteryPet()
{
	SqliteHelper sqlHelper(DB_CONFIG);
	auto result = sqlHelper.readRecord("select * from lottery_pet");
	for (auto iter = result.begin(); iter != result.end(); ++iter)
	{
		auto data = *iter;
		LotteryPetConfig config;
		config.id = atoi(data[0]);
		config.stage = atoi(data[1]);
		config.petId = atoi(data[2]);

		m_lotteryPetConfig.push_back(config);
	}
	sort(m_lotteryPetConfig.begin(), m_lotteryPetConfig.end(), [=](LotteryPetConfig config1, LotteryPetConfig config2)->bool
	{
		return config1.stage < config2.stage;
	});
}

const LotteryPetConfig *DataManager::getLotteryPetConfigByStage(int stage)
{
	for (auto iter = m_lotteryPetConfig.begin(); iter != m_lotteryPetConfig.end(); ++iter)
	{
		if (iter->stage == stage)
		{
			return &(*iter);
		}
	}
	return NULL;
}

const std::vector<LotteryPetConfig> &DataManager::getLotteryPetConfig()
{
	return m_lotteryPetConfig;
}

void DataManager::loadLotteryOutput()
{
	SqliteHelper sqlHelper(DB_CONFIG);
	auto result = sqlHelper.readRecord("select * from lottery_output");
	for (auto iter = result.begin(); iter != result.end(); ++iter)
	{
		auto data = *iter;
		LotteryOutputConfig config;
		config.id = atoi(data[0]);
		config.amount = atoi(data[1]);
		config.percent = atof(data[2]);
		config.desc = data[3];

		m_lotteryOutputConfig.push_back(config);
	}
}

const vector<LotteryOutputConfig> &DataManager::getLotteryOutputConfig()
{
	return m_lotteryOutputConfig;
}
