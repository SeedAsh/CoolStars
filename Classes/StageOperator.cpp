#include "StageOperator.h"
#include "PetManager.h"
#include "PetEntity.h"
#include "CommonUtil.h"
#include "LogicGridUtil.h"
using namespace std;
using namespace CommonUtil;
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
	StageModel::theModel()->genNewStars();
}

void StageOperator::eraseSameColorStars(const LogicGrid &centerGrids, int distance)
{
	auto centerNode = StageModel::theModel()->getStarNode(centerGrids);
	auto grids = getSquareGrids(centerGrids, distance);

	vector<LogicGrid> targetGrids;
	for (size_t i = 0; i < grids.size(); ++i)
	{
		auto node = StageModel::theModel()->getStarNode(grids[i]);
		if (node && node->getAttr().color == centerNode->getAttr().color)
		{
			targetGrids.push_back(grids[i]);
		}
	}

	eraseStars(targetGrids);
}

void StageOperator::randomErase(int num)
{
	vector<LogicGrid> grids;
	for (size_t i = 0; i < ROWS_SIZE; ++i)
	{
		for (int j = 0; j < COlUMNS_SIZE; ++j)
		{
			grids.push_back(LogicGrid(j, i));
		}
	}

	auto targetGrids = getRandomGrids(grids, num);
	eraseStars(targetGrids);
}

void StageOperator::addSteps(int amount)
{
	auto stageInfo = StageModel::theModel()->getStageInfo();
	int curStep = stageInfo->getCurStep();
	stageInfo->setCurStep(curStep + amount);
}

void StageOperator::changeColor(const StarAttr &attr)
{
	StageModel::theModel()->replaceStar(attr);
}

void StageOperator::randomChangeColor(int color, int num)
{
	auto stars = StageModel::theModel()->getStarNodes();
	vector<LogicGrid> grids;
	for (size_t i = 0; i < stars.size(); ++i)
	{
		auto star = stars[i];
		auto attr = star->getAttr();
		if (attr.type == kColorStar && attr.color != color)
		{
			grids.push_back(attr.grid);
		}
	}

	auto targetGrids = getRandomGrids(grids, num);
	for (size_t i = 0; i < targetGrids.size(); ++i)
	{
		auto star = StageModel::theModel()->getStarNode(targetGrids[i]);
		if (star)
		{
			StarAttr targetStarAttr = star->getAttr();
			targetStarAttr.color = color;
			StageModel::theModel()->replaceStar(targetStarAttr);
		}
	}

}

void StageOperator::addPetEnergy(int petId, int value)
{
	auto petMgr = PetManager::petMgr();
	auto curPetIds = petMgr->getCurPetIds();
	auto iter = find(curPetIds.begin(), curPetIds.end(), petId);
	assert(iter != curPetIds.end());
	if (iter == curPetIds.end()) return;

	auto pet = petMgr->getPetById(petId);
	if (pet)
	{
		auto data = pet->getPetData();
		pet->setEnergy(data.energy + value);
	}
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

void StageOperator::randomReplaceToDiamond(int num)
{
	auto stars = StageModel::theModel()->getStarNodes();
	vector<LogicGrid> grids;
	for (size_t i = 0; i < stars.size(); ++i)
	{
		auto star = stars[i];
		auto attr = star->getAttr();
		if (attr.type == kColorStar)
		{
			grids.push_back(attr.grid);
		}
	}

	auto targetGrids = getRandomGrids(grids, num);
	for (size_t i = 0; i < targetGrids.size(); ++i)
	{
		auto star = StageModel::theModel()->getStarNode(targetGrids[i]);
		if (star)
		{
			StarAttr targetStarAttr = star->getAttr();
			targetStarAttr.color = 0;
			targetStarAttr.type = kDiamond;
			StageModel::theModel()->replaceStar(targetStarAttr);
		}
	}
}

void StageOperator::randomReplaceToKey(int num)
{
	auto stars = StageModel::theModel()->getStarNodes();
	vector<LogicGrid> grids;
	for (size_t i = 0; i < stars.size(); ++i)
	{
		auto star = stars[i];
		auto attr = star->getAttr();
		if (attr.type == kColorStar)
		{
			grids.push_back(attr.grid);
		}
	}

	auto targetGrids = getRandomGrids(grids, num);
	for (size_t i = 0; i < targetGrids.size(); ++i)
	{
		auto star = StageModel::theModel()->getStarNode(targetGrids[i]);
		if (star)
		{
			StarAttr targetStarAttr = star->getAttr();
			targetStarAttr.color = 0;
			targetStarAttr.type = kKey;
			StageModel::theModel()->replaceStar(targetStarAttr);
		}
	}
}

