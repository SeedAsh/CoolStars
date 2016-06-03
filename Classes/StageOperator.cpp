#include "StageOperator.h"
#include "PetManager.h"
#include "PetEntity.h"
using namespace std;
USING_NS_CC; 

//道具和宠物对stars的操作
StageOperator::StageOperator()
{

}

StageOperator::~StageOperator()
{

}

void StageOperator::eraseStars(vector<LogicGrid> &grids)
{
	for (size_t i = 0; i < grids.size(); ++i)
	{
		auto node = StageModel::theModel()->getStarNode(grids[i]);
		if (node)
		{
			node->runExplosion();
		}
	}
	StageModel::theModel()->moveStars();
}

void StageOperator::addSteps(int amount)
{
	int curStep = StageModel::theModel()->getStep();
	StageModel::theModel()->setStep(curStep + amount);
}

void StageOperator::changeColor(bool isRandom)
{
	StarAttr attr;
	//init
	StageModel::theModel()->replaceStar(attr);
}

void StageOperator::addPetEnergy(int petId, int value)
{
	//假定只改变以上场宠物的能量
	auto pet = PetManager::petMgr()->getCurPetById(petId);
	if (!pet) return;
	
	auto data = pet->getPetData();
	pet->setEnergy(data.energy + value);

}

void StageOperator::removePetDebuff(int who)
{

}

void StageOperator::chageStarType(int type)
{
	StarAttr attr;
	//init
	StageModel::theModel()->replaceStar(attr);
}

LogicGrid randomGridCreater()
{

}

void StageOperator::reOrderStars()
{
	//规则？没有就随机
	auto originNodes = StageModel::theModel()->getStarNodes();

	for (size_t i = 0; i < originNodes.size(); ++i)
	{
		auto node = originNodes[i];
		LogicGrid targetGrid;
		node->moveTo(targetGrid);
		node->setLogicGrid(targetGrid);
	}

}


