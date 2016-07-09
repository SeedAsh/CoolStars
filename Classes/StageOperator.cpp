#include "StageOperator.h"
#include "PetManager.h"
#include "PetEntity.h"
#include "CommonUtil.h"
#include "LogicGridUtil.h"
#include "StageDataMgr.h"
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
		auto node = StarsController::theModel()->getStarNode(grids[i]);
		if (node)
		{
			node->doRemove();
		}
	}
	StarsController::theModel()->genNewStars();
}

void StageOperator::eraseSameColorStars(const LogicGrid &centerGrids, int distance)
{
	auto centerNode = StarsController::theModel()->getStarNode(centerGrids);
	auto grids = getSquareGrids(centerGrids, distance);

	vector<LogicGrid> targetGrids;
	for (size_t i = 0; i < grids.size(); ++i)
	{
		auto node = StarsController::theModel()->getStarNode(grids[i]);
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
	auto stageInfo = StageDataMgr::theMgr();
	int curStep = stageInfo->getCurStep();
	stageInfo->setCurStep(curStep - amount);
}

void StageOperator::changeColor(const StarAttr &attr)
{
	StarsController::theModel()->replaceStar(attr);
}

void StageOperator::randomChangeColor(int color, int num)
{
	auto stars = StarsController::theModel()->getStarNodes();
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
		auto star = StarsController::theModel()->getStarNode(targetGrids[i]);
		if (star)
		{
			StarAttr targetStarAttr = star->getAttr();
			targetStarAttr.color = color;
			StarsController::theModel()->replaceStar(targetStarAttr);
		}
	}

}

void StageOperator::addPetEnergy(int petId, int value)
{
	PetManager::petMgr()->addPetEnergy(petId, value);
}

void StageOperator::removePetDebuff(int who)
{

}

void StageOperator::chageStarType(int type)
{
	StarAttr attr;
	//init
	StarsController::theModel()->replaceStar(attr);
}

void StageOperator::reOrderStars()
{
	//规则？没有就随机
	auto rowSeq = buildRandomSequence(ROWS_SIZE);
	auto colSeq = buildRandomSequence(COlUMNS_SIZE);

	auto nodes = StarsController::theModel()->getStarNodes();
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
	auto stars = StarsController::theModel()->getStarNodes();
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
		auto star = StarsController::theModel()->getStarNode(targetGrids[i]);
		if (star)
		{
			StarAttr targetStarAttr = star->getAttr();
			targetStarAttr.color = 0;
			targetStarAttr.type = kDiamond;
			StarsController::theModel()->replaceStar(targetStarAttr);
		}
	}
}

void StageOperator::randomReplaceToKey(int num)
{
	auto stars = StarsController::theModel()->getStarNodes();
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
		auto star = StarsController::theModel()->getStarNode(targetGrids[i]);
		if (star)
		{
			StarAttr targetStarAttr = star->getAttr();
			targetStarAttr.color = 0;
			targetStarAttr.type = kKey;
			StarsController::theModel()->replaceStar(targetStarAttr);
		}
	}
}

