#ifndef __STAGETARGET_H__
#define __STAGETARGET_H__
#include "cocos2d.h"
#include <unordered_map>
#include "StarNode.h"

class StageTarget
{
public:
	StageTarget();
	~StageTarget();
	
	void initTargets();
	bool isGameOver();
	bool isReachTarget();
	void recordErasedStars(int starIndex);
	void resetData();
	void getCurTarget();
private:
	bool isGetEnoughScore();
	bool isErasedEnoughStars();
	bool isReachTargetGrid();
private:
	enum winType
	{
		kScore,		//分数
		kStarAmount,//消除特定数目的星星
		kTargetGrid,//护送指定对象到指定位置
	};
private:
	int m_winType;

	int m_targetScore;

	std::unordered_map<int, int> m_records;
	std::vector<std::tuple<int, int>> m_targets;

	LogicGrid m_targetGrid;
};
#endif