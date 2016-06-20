#include "StageOperator.h"
#include "PetManager.h"
#include "PetEntity.h"
using namespace std;
USING_NS_CC; 

//道具和宠物对stars的操作
StageOperator *StageOperator::theOperator()
{
	static StageOperator op;
	return &op;
}

void StageOperator::eraseStars(vector<LogicGrid> &grids)
{
	for (size_t i = 0; i < grids.size(); ++i)
	{
		auto node = StageModel::theModel()->getStarNode(grids[i]);
		if (node)
		{
			node->doRemove();
		}
	}
	StageModel::theModel()->moveStars();
}

void StageOperator::addSteps(int amount)
{
	auto stageInfo = StageModel::theModel()->getStageInfo();
	int curStep = stageInfo->getCurStep();
	stageInfo->setCurStep(curStep + amount);
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
	auto pet = PetManager::petMgr()->getPetById(petId);
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

//生成 [0 , length-1] 的随机序列
static vector<int> buildRandomSequence(int length) {
	vector<int> seq;
	for (int i = 0; i < length; ++i)
	{
		seq.push_back(i);
	}
	int index = 0;
	int tmp = 0;
	for (int i = length - 1; i > 0; i--) {
		index = (int(CCRANDOM_0_1() * 100)) % i;

		tmp = seq[i];
		seq[i] = seq[index];
		seq[index] = tmp;
	}
	
	return seq;
}

void StageOperator::reOrderStars()
{
	//规则？没有就随机
	auto rowSeq = buildRandomSequence(ROWS_SIZE);
	auto colSeq = buildRandomSequence(COlUMNS_SIZE);

	auto nodes = StageModel::theModel()->getStarNodes();
	assert(nodes.size() <= ROWS_SIZE * COlUMNS_SIZE);

	for (size_t i = 0; i < nodes.size(); ++i)
	{
		auto node =nodes[i];
		LogicGrid targetGrid;
		
		targetGrid.x = colSeq[i % COlUMNS_SIZE];
		targetGrid.y = rowSeq[i / ROWS_SIZE];

		node->moveTo(targetGrid);
		node->setLogicGrid(targetGrid);
	}

}


