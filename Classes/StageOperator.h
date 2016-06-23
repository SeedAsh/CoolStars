#ifndef __STAGEOPERATOR_H__
#define __STAGEOPERATOR_H__
#include "cocos2d.h"
#include "StageModel.h"
#include "StarNode.h"

#define StageOp StageOperator::theOperator()
class StageOperator
{
public:
	static StageOperator *theOperator();
	~StageOperator(){}
public:
	void eraseStars(std::vector<LogicGrid> &grids);
	void eraseSameColorStars(const LogicGrid &centerGrids, int distance);
	void randomErase(int num);

	void addSteps(int amount);

	void changeColor(const StarAttr &attr);
	void randomChangeColor(int color, int num);
	void randomReplaceToDiamond(int num);
	void randomReplaceToKey(int num);

	void addPetEnergy(int petId, int value);
	void removePetDebuff(int who);
	void chageStarType(int type);
	void reOrderStars();
private:
};
#endif