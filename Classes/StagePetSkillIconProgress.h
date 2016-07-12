#ifndef __STAGEPETSKILLICON_H__
#define __STAGEPETSKILLICON_H__
#include <functional>
#include "cocos2d.h"
class StagePetSkillIconProgress
	: public cocos2d::CCNode
{
public:
	static StagePetSkillIconProgress *create(int petId);
	void runEnergyAddAction(int oldEnergy, std::function<void()> callback);
private:
	StagePetSkillIconProgress(int petId):m_petId(petId){}
	virtual bool init();
	void setPercentage(float value, bool withAction, std::function<void()> callback = std::function<void()>());
private:
	int m_petId;
	cocos2d::CCProgressTimer *m_progress;
};
#endif