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
	bool isReachTarget();
	void recordErasedStars(int starIndex);
	void resetData();
private:
	bool isGetEnoughScore();
	bool isErasedEnoughStars();
	bool isReachTargetGrid();
private:
	enum winType
	{
		kScore,		//����
		kStarAmount,//�����ض���Ŀ������
		kTargetGrid,//����ָ������ָ��λ��
	};
private:
	int m_winType;

	int m_targetScore;

	std::unordered_map<int, int> m_records;
	std::vector<std::tuple<int, int>> m_targets;

	LogicGrid m_targetGrid;
};
#endif