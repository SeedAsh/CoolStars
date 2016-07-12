#ifndef __LOTTERYMODEL_H__
#define __LOTTERYMODEL_H__
#include "cocos2d.h"
enum LotteryReward
{
	kLotteryLittleStrength,
	kLotteryBagStrength,
	kLotteryLittleDiamond,
	kLotteryBagDiamond,
	kLotteryLittleFood,
	kLotteryBagFood,
	kLotteryPet = 6, //∂‘”¶LotteryOutput±Ì
};

struct LotteryData
{
	int type;
	int param;
};

class LotteryModel
{
public:
	static LotteryModel *theModel();
	LotteryData getLotteryResult();
	void doLottery(const LotteryData &data);
	
private:
	std::vector<int> getPetsCanNotOwn();
	
};
#endif