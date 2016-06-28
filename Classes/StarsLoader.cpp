#include "StarsLoader.h"
#include "StageModel.h"
#include "CommonUtil.h"
using namespace std;
using namespace CommonUtil;
USING_NS_CC;

StarAttr StarsLoader::genNewStars(const LogicGrid &grid)
{
	StarAttr attr;
	attr.grid = grid;
	attr.type = kColorStar;
	attr.color = kColorRandom;

	int curScore = StageModel::theModel()->getStageInfo()->getCurScore();
	int popFrontNum = 0;
	for (auto iter = m_loaderDatas.begin(); iter != m_loaderDatas.end(); ++iter)
	{
		auto data = m_loaderDatas.front();
		//当前得分大于data分数才开始算百分比出现
		if (data.score > curScore)
		{
			break;
		}
		popFrontNum++;
		if (isSelected(data.percent))
		{
			attr.type = data.starType;
			CCLOG("type = %d", data.starType);
			break;
		}
	}
	for (int i = 0; i < popFrontNum; ++i)
	{
		m_loaderDatas.pop_front();
	}

	return attr;
	
}

void StarsLoader::init()
{
	int curStage = StageModel::theModel()->getStageInfo()->getCurStage();
	auto configs = DataManagerSelf->getStarsLoaderConfig(curStage);
	
	m_loaderDatas.clear();
	for (size_t i = 0; i < configs.size(); ++i)
	{
		auto config = configs[i];
		for (int j = 0; j < config.num; ++j)
		{
			StarsLoaderData data;
			data.starType = config.starType;
			data.percent = config.percent;
			data.score = config.score;
			m_loaderDatas.push_back(data);
		}
	}
	sort(m_loaderDatas.begin(), m_loaderDatas.end(), [=](StarsLoaderData data1, StarsLoaderData data2)->bool
	{
		return data1.score < data2.score;
	});
}
