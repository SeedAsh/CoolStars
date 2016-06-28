#include "StageBaseInfo.h"
#include "DataManager.h"
#include "StageSavingHelper.h"
#include "CommonUtil.h"

StageBaseInfo::StageBaseInfo()
{
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

void StageBaseInfo::reset(int gameType)
{
	m_step = 0;
	m_curScore = 0;
	m_curScoreBonus = 0;

	if (gameType == kNormalType)
	{
		m_curStage = m_topStage;
	}
	else if (gameType == kTreasureType && m_topStage > 1)
	{
		m_curStage = CommonUtil::getRandomValue(1, m_topStage - 1);
	}
}

void StageBaseInfo::init()
{
	StageSavingHelper::LoadLastSavedStageData();
	reset();
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

void StageBaseInfo::getStageStars(std::vector<std::vector<StageStarInfo>> &stars)
{
	DataManagerSelf->getNewStageStarsData(stars, m_curStage);
}

void StageBaseInfo::doSave()
{
	StageSavingHelper::saveCurStageData();
	StageSavingHelper::saveCurStars();
}

void StageBaseInfo::addCurScore(int value)
{ 
	float score = m_curScore * (1 + m_curScoreBonus);
	setCurScore(score + value);
	m_curScoreBonus = 0;
}