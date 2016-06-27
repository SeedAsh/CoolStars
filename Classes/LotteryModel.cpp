#include "LotteryModel.h"
using namespace std;
LotteryModel *LotteryModel::theModel()
{
	static LotteryModel model;
	return &model;
}