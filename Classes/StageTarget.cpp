#include "StageTarget.h"
#include "StageModel.h"
#include "StageBaseInfo.h"
#include "CommonUtil.h"

using namespace std;
USING_NS_CC; 

StageTarget::StageTarget()
{
	reset();
}

StageTarget::~StageTarget()
{

}

void StageTarget::starErased(int starType, int color)
{
	for (auto iter = m_eraseStars.begin(); iter != m_eraseStars.end(); ++iter)
	{
		auto data = *iter;
		if (data.starType == starType && data.color == color)
		{
			int left = data.num - 1;
			iter->num = max(left, 0);
		}
	}
}

void StageTarget::init()
{
	reset();

	auto info = StageModel::theModel()->getStageInfo();
	auto config = DataManagerSelf->getStageConfig(info->getCurStage());
	m_winType = config.tagetType;
	m_targetScore = config.targetScore;
	auto param = config.targetParam;

	switch (m_winType)
	{
	case kEraseStars:
	{
		assert(param.size() % 3 == 0);
		for (size_t i = 0; i < param.size(); i += 3)
		{
			EraseStarsData target;
			target.starType = param[i];
			target.color = param[i + 1];
			target.num = param[i + 2];

			m_eraseStars.push_back(target);
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


void StageTarget::reset()
{
	m_winType = kEraseStars;

	m_targetScore = 0;
	m_targetGrid.x = 0; 
	m_targetGrid.y = 0;

	m_eraseStars.clear();
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
	case kEraseStars:
		return isErasedEnoughStars() && isGetEnoughScore();
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
	for (size_t i = 0; i < m_eraseStars.size(); ++i)
	{
		if (m_eraseStars[i].num > 0)
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

vector<EraseStarsData> StageTarget::getEraseStarsLeft()
{
	return m_eraseStars;
}