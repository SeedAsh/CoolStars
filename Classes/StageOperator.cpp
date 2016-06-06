#include "StageOperator.h"
#include "PetManager.h"
#include "PetEntity.h"
using namespace std;
USING_NS_CC; 

//���ߺͳ����stars�Ĳ���
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
			node->removeSelf();
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
	//�ٶ�ֻ�ı����ϳ����������
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

//���� [0 , length-1] ���������
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
	//����û�о����
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


