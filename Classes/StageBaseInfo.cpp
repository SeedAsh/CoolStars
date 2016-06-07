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

int StageBaseInfo::getLeftStep()
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
	//初始化加载上次游戏
	resumeGame();
}

void StageBaseInfo::resumeGame()
{
	reset();
	m_isNewStage = false;
	StageSavingHelper::LoadLastSavedStageData();
}

void StageBaseInfo::newGame()
{
	reset();
	m_isNewStage = true;
	m_curStage = 1;
}

void StageBaseInfo::toNextStage()
{
	reset();
	if (!isTheLastStage())
	{
		m_curStage++;
		m_isNewStage = true;
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

void StageBaseInfo::getStageStars(std::vector<std::vector<int>> &stars)
{
	do
	{
		if (!m_isNewStage)
		{
			bool isSucceed = StageSavingHelper::getLastSavedStars(stars);
			if (isSucceed) break;
		}

		DataManagerSelf->getNewStageStarsData(stars, m_curStage);

	} while (0);
}

void StageBaseInfo::doSave()
{
	if (m_isNewStage)
	{
		StageSavingHelper::saveCurStageData();
		StageSavingHelper::saveCurStars();
	}
}