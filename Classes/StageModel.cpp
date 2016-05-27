#include "StageModel.h"
StageModel::StageModel()
: m_direction(3)
{

}

StageModel::~StageModel()
{

}
StageModel *StageModel::theModel()
{
	static StageModel model;
	return &model;
}