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

struct PetsConfig
{
	int id;
	int skillId;
	vector<int> energy;
	vector<int> count;
	vector<int> upgrade;
	vector<string> iconPaths;
	string skillIcon;
	string desc;
};

struct StageConfig
{
	int id;
	int tagetType;
	vector<int> targetParam;
	int step;
	vector<int> direction;
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

struct stageStarInfo
{
	int starType;
	int color;
};
#endif