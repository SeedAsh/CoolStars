#include "LotteryModel.h"
#include "DataManager.h"
#include "StageModel.h"
#include "PetManager.h"
#include "CommonUtil.h"
using namespace std;
using namespace CommonUtil;

LotteryModel *LotteryModel::theModel()
{
	static LotteryModel model;
	return &model;
}

LotteryData LotteryModel::doLottery()
{
	LotteryData data;
	//在指定关卡里,必然抽到某宠物（对应lotteryPet表）
	auto curStage = StageModel::theModel()->getStageInfo()->getCurStage();
	auto lotteryPetConfig = DataManagerSelf->getLotteryPetConfigByStage(curStage);
	if (lotteryPetConfig && !PetManager::petMgr()->ownThisPet(lotteryPetConfig->petId))
	{
		data.type = kLotteryPet;
		data.param = lotteryPetConfig->petId;
	}
	else
	{
		//按照百分比获取宝箱内容（对应于lotteryOutput表）
		vector<float> percents;
		auto lotteryOutputConfig = DataManagerSelf->getLotteryOutputConfig();
		for (size_t i = 0; i < lotteryOutputConfig.size(); ++i)
		{
			percents.push_back(lotteryOutputConfig[i].percent);
		}
		int result = getResultByPercent(percents);
		data.type = result;
		if (result == kLotteryPet)
		{
			//未获得的宠物 - 不能获取的宠物（后面关卡必然要获取的宠物,所以现在不能获得，在lotteryPet表里）
			auto notOwnedPets = PetManager::petMgr()->getNotOwnedPetIds();
			auto canOwnPets = getDifference(notOwnedPets, getPetsCanNotOwn());
			if (canOwnPets.empty())
			{
				return doLottery();
			}
			auto index = getRandomValue(0, canOwnPets.size() - 1);
			data.param = canOwnPets[index];
		}
		else
		{
			data.param = lotteryOutputConfig[result].amount;
		}
	}

	return data;
}

//不能获取的宠物id
std::vector<int> LotteryModel::getPetsCanNotOwn()
{
	vector<int> ids;
	auto curStage = StageModel::theModel()->getStageInfo()->getCurStage();
	auto config = DataManagerSelf->getLotteryPetConfig();
	for (auto iter = config.begin(); iter != config.end(); ++iter)
	{
		if (iter->stage > curStage)
		{
			ids.push_back(iter->petId);
		}
	}

	return ids;
}