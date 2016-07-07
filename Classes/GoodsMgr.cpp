#include "GoodsMgr.h"
#include "CommonMacros.h"
#include "UserInfo.h"
#include "PropManager.h"
#include "StageModel.h"
#include "StageBaseInfo.h"
using namespace std;
USING_NS_CC;

GoodsMgr *GoodsMgr::theMgr()
{
	static GoodsMgr mgr;
	return &mgr;
}

void GoodsMgr::addGoods(std::vector<int> items)
{
	assert(items.size() % 3 == 0);
	for (size_t i = 0; i < items.size(); i += 3)
	{
		int type = items[i];
		int goodsId = items[i + 1];
		int amount = items[i + 2];
		switch (type)
		{
			case kGoodsDiamond:
			{
			  int diamond = UserInfo::theInfo()->getDiamond();
			  UserInfo::theInfo()->setDiamond(diamond + amount);
			  break;
			}
			case kGoodsFood:
			{
				int food = UserInfo::theInfo()->getFood();
				UserInfo::theInfo()->setFood(food + amount);
				break;
			}
			case kGoodsStrength:
			{
				int strength = UserInfo::theInfo()->getStrength();
				UserInfo::theInfo()->setStrength(strength + amount);
				break;
			}
			case kGoodsRuneStone:
			{
				int runeStone = UserInfo::theInfo()->getRuneStone();
				UserInfo::theInfo()->setRuneStone(runeStone + amount);
				break;
			}
			case kGoodsKey:
			{
				int key = UserInfo::theInfo()->getKey();
				UserInfo::theInfo()->setKey(key + amount);
				break;
			}
			case kGoodsProps:
			{
				int prop = PropManager::propMgr()->getPropItemAmount(goodsId);
				PropManager::propMgr()->setPropItemAmount(goodsId, prop + amount);
				break;
			}
			case kGoodsPets:
			{
				break;
			}
			case kGoodsStep:
			{
				auto stageInfo = StageModel::theModel()->getStageInfo();
				int step = stageInfo->getCurStep() - amount;
				stageInfo->setCurStep(step);
			}
			default:
				break;
		}
	}
}