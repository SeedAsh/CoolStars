#include "StageModel.h"
#include "StarUtil.h"
#include "DataManager.h"
USING_NS_CC;
using namespace std;
StageModel::StageModel()
	: m_direction(3)
	, m_curStage(1)
	, m_isNewStage(true)
{
	resetStarsData();
}

StageModel::~StageModel()
{

}
StageModel *StageModel::theModel()
{
	static StageModel model;
	return &model;
}

void StageModel::initStarsData()
{
	releaseStarsData();

	//关卡星星数据是一列列保存的，需要转换
	if (m_isNewStage)
	{
		StageInfo m_sCurrentStageInfo = DataManagerSelf->StagesVec[m_curStage];
		DataManagerSelf->LoadStageData(m_curStage);

		for (int row = 0; row < ROWS_SIZE; ++row)
		{
			StageData stageStarRow = DataManagerSelf->StageVec[row];
			for (int col = 0; col < COlUMNS_SIZE; ++col)
			{
				m_starNodes[col][ROWS_SIZE - row - 1] = StarNode::createNodeFatory(stageStarRow.col[col]);
			}
		}
	}
	else 
	{
		vector<vector<int>> StageVec = m_savingHelper.getLastState();
		for (int col = 0; col < COlUMNS_SIZE; ++col)
		{
			for (int row = 0; row < ROWS_SIZE; ++row)
			{
				m_starNodes[col][ROWS_SIZE - row - 1] = StarNode::createNodeFatory(StageVec[col][row]);
			}
		}
	}
	
	
}

void StageModel::resetStarsData()
{
	//reset nodes
	for (int row = 0; row < ROWS_SIZE; ++row)
	{
		for (int col = 0; col < COlUMNS_SIZE; ++col)
		{
			m_starNodes[row][col] = NULL;
		}
	}
}

void StageModel::releaseStarsData()
{
	for (int row = 0; row < ROWS_SIZE; ++row)
	{
		for (int col = 0; col < COlUMNS_SIZE; ++col)
		{
			auto node = m_starNodes[row][col];
			if (node != NULL)
			{
				delete node;
				m_starNodes[row][col] = NULL;
			}
		}
	}
}

StarNode *StageModel::getStarData(LogicGrid &grid)
{
	return m_starNodes[grid.x][grid.y];
}
