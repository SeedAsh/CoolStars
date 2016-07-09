#ifndef __STAGEMASKLAYER_H__
#define __STAGEMASKLAYER_H__

#include "cocos2d.h"
#include "StarsController.h"
#include "StageLayersMgr.h"
#include <unordered_map>

enum MaskMode
{
	kMaskModeStar,
	kMaskModePet,
};
class StageMaskLayer
	: public cocos2d::CCNode
	, public cocos2d::CCTouchDelegate
	, public IStageLayer
{
public:
	CREATE_FUNC(StageMaskLayer);
	void initPetViewsInfo(std::unordered_map<int, cocos2d::CCPoint> info);
private:
	StageMaskLayer();
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	virtual void onHighLightStars(int color);
	virtual void onHighLightPets(const std::vector<int> &petIds);

private:
	int m_maskMode;

	std::vector<cocos2d::CCNode *> m_stars;
	cocos2d::CCNode *m_starsContainer;

	std::unordered_map<int, cocos2d::CCPoint> m_petsInfo;
	std::unordered_map<int, cocos2d::CCNode *> m_pets;
	cocos2d::CCNode *m_petsContainer;
};

#endif
