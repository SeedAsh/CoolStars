#ifndef __STARSLAYER_H__ 
#define __STARSLAYER_H__
#include "cocos2d.h"
#include "StarViewNode.h"
USING_NS_CC;
class StarUtil;

class StarsLayer
	: public CCLayer
{
public:
	StarsLayer();
	~StarsLayer();

	CREATE_FUNC(StarsLayer);
	virtual bool init();

	void initBackground();
	StarViewNode *getStarByGrid(LogicGrid grid);
	void initStars();
	void starInitDone();
	StarViewNode *getClickedStar(CCPoint pos);
	std::vector<StarViewNode *>	getStarNeighbours(StarViewNode *star);
	void moveStars();
	void genNewStars();
	void moveStar(StarViewNode *star);
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	bool isGridEmpty(LogicGrid grid);
	CCPoint getPosByGrid(LogicGrid grid);
	void removeStar(StarViewNode *node);
private:
	StarUtil *m_pStarUtil;
	std::vector<StarViewNode *> m_starsSprite;
};
#endif 