#include "RankingModel.h"
#include "CommonUtil.h"
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
	const int kMaxLength = 4;

	name += getRandomLetter();
	for (int i = 0; i < kMaxLength - 1; ++i)
	{
		bool isExit = getRandomValue(0, 1) == 1 ? true : false;
		if (isExit)
		{
			name += getRandomLetter();
		}
	}
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