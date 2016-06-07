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
	int extra;
	string explosionPath;
};

struct PetsConfig
{
	int id;
	int skillId;
	vector<int> energy;
	vector<int> count;
	vector<int> upgrade;
	vector<string> iconPath;
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
	int stageAmount;
};

#endif