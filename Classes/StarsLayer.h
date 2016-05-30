#ifndef __STARSLAYER_H__ 
#define __STARSLAYER_H__
#include "cocos2d.h"
#include "StarNode.h"
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
	cocos2d::CCNode *createStar(int starType, LogicGrid grid);
	StarNode *getStarByGrid(LogicGrid grid);
	void initStars();
	void starInitDone();
	StarNode *getClickedStar(CCPoint pos);
	std::vector<StarNode *>	getStarNeighbours(StarNode *star);
	void moveStars();
	void genNewStars();
	void moveStar(StarNode *star);
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	bool isGridEmpty(LogicGrid grid);
	CCPoint getPosByGrid(LogicGrid grid);
	void removeStar(StarNode *node);
private:
	StarUtil *m_pStarUtil;
	std::vector<StarNode *> m_starsSprite;
};
#endif 