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
	//��ָ���ؿ���,��Ȼ�鵽ĳ�����ӦlotteryPet��
	auto curStage = StageModel::theModel()->getStageInfo()->getCurStage();
	auto lotteryPetConfig = DataManagerSelf->getLotteryPetConfigByStage(curStage);
	if (lotteryPetConfig && !PetManager::petMgr()->ownThisPet(lotteryPetConfig->petId))
	{
		data.type = kLotteryPet;
		data.param = lotteryPetConfig->petId;
	}
	else
	{
		//���հٷֱȻ�ȡ�������ݣ���Ӧ��lotteryOutput��
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
			//δ��õĳ��� - ���ܻ�ȡ�ĳ������ؿ���ȻҪ��ȡ�ĳ���,�������ڲ��ܻ�ã���lotteryPet���
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

//���ܻ�ȡ�ĳ���id
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