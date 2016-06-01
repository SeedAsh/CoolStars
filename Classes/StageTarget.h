#ifndef __STAGETARGET_H__
#define __STAGETARGET_H__
#include "cocos2d.h"
#include <unordered_map>

class StageTarget
{
public:
	StageTarget();
	~StageTarget();
	
	void initTargets();
	bool isReachTarget();
	void recordErasedStars(int starIndex);
	void resetData();
private:
	enum 
	{
		kScore,
		kStarAmount,
		kTargetGrid,
	};
private:
	std::unordered_map<int, int> m_records;
	std::vector<std::tuple<int, int>> m_targets;
};
#endif