#ifndef __STAGEPETSKILLICON_H__
#define __STAGEPETSKILLICON_H__
#include <functional>
#include "cocos2d.h"
class StagePetSkillIcon
	: public cocos2d::CCNode
{
public:
	static StagePetSkillIcon *create(int petId);
	void refresh(std::function<void()> callback);
private:
	StagePetSkillIcon(int petId):m_petId(petId){}
	virtual bool init();
	void setPercentage(int value, bool withAction, std::function<void()> callback = std::function<void()>());
private:
	int m_petId;
	cocos2d::CCProgressTimer *m_progress;
};
#endif