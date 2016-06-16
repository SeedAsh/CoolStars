#include "StageBaseInfo.h"
#include "DataManager.h"
#include "StageSavingHelper.h"

StageBaseInfo::StageBaseInfo()
{
	reset();
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

int StageBaseInfo::getLeftSteps()
{
	auto config = DataManagerSelf->getStageConfig(m_curStage);
	int leftStep = config.step - m_step;
	return max(leftStep, 0);
}

void StageBaseInfo::reset()
{
	m_step = 0;
	m_curScore = 0;
}

void StageBaseInfo::init()
{
	reset();
	StageSavingHelper::LoadLastSavedStageData();
}

void StageBaseInfo::toNextStage()
{
	reset();
	if (!isTheLastStage())
	{
		m_curStage++;
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

bool StageBaseInfo::isTheLastStage()
{
	auto config = DataManagerSelf->getSystemConfig();
	return m_curStage >= config.stageAmount;
}

void StageBaseInfo::getStageStars(std::vector<std::vector<stageStarInfo>> &stars)
{
	DataManagerSelf->getNewStageStarsData(stars, m_curStage);
}

void StageBaseInfo::doSave()
{
	StageSavingHelper::saveCurStageData();
	StageSavingHelper::saveCurStars();
}