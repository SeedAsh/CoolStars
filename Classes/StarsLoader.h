#ifndef __STARSLOADER_H__
#define __STARSLOADER_H__
#include "cocos2d.h"
#include "LogicGridUtil.h"
#include "StarNode.h"
#include "DataConfig.h"
#include <deque>

struct StarsLoaderData
{
	int starType;
	int score;
	int percent;
};

class StarsLoader
{
public:
	StarAttr genNewStars(const LogicGrid &grid);
	void init();
private:
	std::deque<StarsLoaderData> m_loaderDatas;
};
#endif