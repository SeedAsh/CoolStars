#include "StageTarget.h"
#include "StageModel.h"

using namespace std;
USING_NS_CC; 

StageTarget::StageTarget()
{
	resetData();
}

StageTarget::~StageTarget()
{

}

void StageTarget::recordErasedStars(int starIndex)
{
	unordered_map<int, int> targets;
	targets[starIndex]++;
}

void StageTarget::initTargets()
{
	resetData();
	typedef tuple<int, int> targetType;

	int indexs[] = { 1, 10, 2, 5 };
	vector<int> targets(indexs, indexs + 4);
	assert(targets.size() % 2 == 0);
	for (size_t i = 0; i < targets.size(); i += 2)
	{
		targetType target(targets[i], targets[i + 1]); 
		m_targets.push_back(target);
	}
}

void StageTarget::resetData()
{
	m_winType = kScore;
	m_targetScore = 0;
	m_targetGrid.x = 0; 
	m_targetGrid.y = 0;

	m_records.clear();
	m_targets.clear();
}

bool StageTarget::isReachTarget()
{
	switch (m_winType)
	{
	case kScore:
		return isGetEnoughScore();
	case kStarAmount:
		return isErasedEnoughStars();
	case kTargetGrid:
		return isReachTargetGrid();
	default:
		return false;
	}
	
}

bool StageTarget::isGetEnoughScore()
{
	return StageModel::theModel()->getCurScore() >= m_targetScore;
}

bool StageTarget::isErasedEnoughStars()
{
	for (size_t i = 0; i < m_targets.size(); ++i)
	{
		int targetIndex = get<0>(m_targets[i]);
		int targetAmount = get<1>(m_targets[i]);
		if (m_records[targetIndex] < targetAmount)
		{
			return false;
		}
	}
	return true;
}

bool StageTarget::isReachTargetGrid()
{
	return false;
}