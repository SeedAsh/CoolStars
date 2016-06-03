#ifndef __STAGEOPERATOR_H__
#define __STAGEOPERATOR_H__
#include "cocos2d.h"
#include "StageModel.h"

class StageOperator
{
public:
	StageOperator();
	~StageOperator();
public:
	void eraseStars(std::vector<LogicGrid> &grids);
	void addSteps(int amount);
	void changeColor(bool isRandom);
	void addPetEnergy(int petId, int value);
	void removePetDebuff(int who);
	void chageStarType(int type);
	void reOrderStars();
};
#endif