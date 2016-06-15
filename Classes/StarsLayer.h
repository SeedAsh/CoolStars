#ifndef __STARSLAYER_H__ 
#define __STARSLAYER_H__
#include "cocos2d.h"
#include "StarViewNode.h"
#include "StageModel.h"
#include "StageLayersMgr.h"
USING_NS_CC;
class StarUtil;

class StarsLayer
	: public CCLayer
	, public IStageView
	, public IStageLayer
{
public:
	StarsLayer();
	~StarsLayer();

	CREATE_FUNC(StarsLayer);
	virtual bool init();

	void initBackground();
	void initStars();
	void starInitDone();
	StarViewNode *getClickedStar(CCPoint pos);
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	CCPoint getPosByGrid(LogicGrid grid);
	void removeStar(StarViewNode *node);
	StarViewNode *createStarByGrid(const LogicGrid &grid);
private:
	virtual void onCreateNewStar(StarNode *node);
	virtual void onEnter();
	virtual void onExit();
	void addClippingNode();
private:
	StarUtil *m_pStarUtil;
	std::vector<StarViewNode *> m_starsSprite;
	cocos2d::CCClippingNode *m_clippingNode;
};
#endif 