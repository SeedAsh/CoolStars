#include "StageTarget.h"
#include "StageModel.h"
#include "StageBaseInfo.h"
#include "CommonUtil.h"

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

	auto info = StageModel::theModel()->getStageInfo();
	auto config = DataManagerSelf->getStageConfig(info->getCurStage());
	m_winType = config.tagetType;
	auto param = config.targetParam;
	switch (m_winType)
	{
	case kScore:
	{
		assert(param.size() == 1);
		m_targetScore = param[0];
		break;
	}
	case kStarAmount:
	{
		typedef tuple<int, int> targetType;

		assert(param.size() % 2 == 0);
		for (size_t i = 0; i < param.size(); i += 2)
		{
			targetType target(param[i], param[i + 1]);
			m_targets.push_back(target);
		}
		break;
	}
	case kTargetGrid:
	{
		assert(param.size() == 2);
		m_targetGrid.x = param[0];
		m_targetGrid.x = param[1];
		break;
	}
	default:
		assert(false && "on this kind!");
	}
}

void StageTarget::getCurTarget()
{

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

bool StageTarget::isGameOver()
{
	if (isReachTarget()) return true;

	auto stageInfo = StageModel::theModel()->getStageInfo();
	return stageInfo->getLeftSteps() <= 0;

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
	auto stageInfo = StageModel::theModel()->getStageInfo();
	return stageInfo->getCurScore() >= m_targetScore;
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