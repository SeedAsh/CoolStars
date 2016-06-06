#include "StageBaseInfo.h"
#include "DataManager.h"
#include "StageSavingHelper.h"

StageBaseInfo::StageBaseInfo()
{
	init();
}

int StageBaseInfo::getCurDirection()
{
	int index = 0;
	auto config = DataManagerSelf->getStageConfig(m_curStage);
	auto dirs = config.direction;
	if (m_step > 0)
	{
		index = ((m_step - 1) % dirs.size());
	}
	return dirs[index];
}

int StageBaseInfo::getLeftStep()
{
	auto config = DataManagerSelf->getStageConfig(m_curStage);
	int leftStep = config.step - m_step;
	return max(leftStep, 0);
}

void StageBaseInfo::init()
{
	m_step = 0;
	m_curScore = 0;

	if (m_isNewStage)
	{
		m_curStage = 1;
	}
	else
	{
		StageSavingHelper::LoadLastSavedStageData();
	}

}

void StageBaseInfo::setCurScore(int score)
{
	if (score > m_topScore)
	{
		m_topScore = score;
	}

	m_curScore = score;
}

void StageBaseInfo::toNextStage()
{
	if (!isTheLastStage())
	{
		m_curStage++;
	}
}

bool StageBaseInfo::isTheLastStage()
{
	auto config = DataManagerSelf->getSystemConfig();
	return m_curStage >= config.stageAmount;
}