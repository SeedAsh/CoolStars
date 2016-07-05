#ifndef __DATACONFIG_H__
#define __DATACONFIG_H__

#include "cocos2d.h"
#include <vector>
#include <string.h>

using namespace std;
USING_NS_CC;

struct StarsConfig
{
	int id;
	string desc;
	int score;
	string resPath;
	string bornAnimationRes;
	string explosionRes;
	vector<int> linkStarTypes;
	vector<int> eraseTypes;
};

struct PetCommonConfig
{
	int id;
	vector<int> maxEnergy;
	vector<int> skillPower;
	vector<int> foodToUpgrade;
	int skillTarget;
	string desc;
};

struct PetResConfig
{
	int id;
	int commonId;
	int color;
	string petImgRes;
	string skillRes;
	string petAnimationRes;
	string petNameRes;
};

struct PetColorConfig
{
	int id;
	string preStageSlotBg;
	string skillTitle;
	string skillLvLabel;
	string numRes;
};

struct StageConfig
{
	int id;
	int tagetType;
	int targetScore;
	vector<int> targetParam;
	int step;
	vector<int> direction;
};

struct StarsLoaderConfig
{
	int id;
	int stageId;
	int starType;
	int score;
	int percent;
	int num;
};

struct SystemConfig
{
	int id;
	int stageAmount;
};

struct StarsColorConfig
{
	int id;
	std::string colorStarRes;
	std::string colorExplosionRes;
	std::string bounceBallRes;
	std::string bounceBallExplosionRes;
	std::string desc;
};

struct StageStarInfo
{
	int starType;
	int color;
};

struct PropsConfig
{
	int id;
	std::string resPath;
};

struct RankingConfig
{
	int id;
	std::string name;
	int stage;
	int ownPetPercent;
};

struct ShopConfig
{
	int id;
	int cost;
	int diamond;
	std::string iconPath;
};

struct PackageConfig
{
	int id;
	int cost;
	int award;
	std::string titlePath;
};

struct LotteryPetConfig
{
	int id;
	int stage;
	int petId;
};

struct LotteryOutputConfig
{
	int id;
	int amount;
	float percent;
	std::string desc;
};

struct GuideConfig
{
	int id;
	int stage;
	int startAction;
	int endAction;
	bool showGuideView;
	std::vector<float>targetRect;
	bool showMask;
	bool showFinger;
	std::string dialogText;
	bool showTextDialog;
	std::string desc;
};
#endif