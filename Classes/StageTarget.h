#ifndef __STAGETARGET_H__
#define __STAGETARGET_H__
#include "cocos2d.h"

class StageTarget
{
public:
	StageTarget();
	~StageTarget();
	
	bool isReachTarget(){}
private:
	enum 
	{
		kScore,
		kStarAmount,
		kTargetGrid,
	};
};
#endif