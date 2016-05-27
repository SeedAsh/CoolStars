#ifndef __STARSLAYER_H__ 
#define __STARSLAYER_H__
#include "cocos2d.h"
USING_NS_CC;
class StarUtil;
class StarNode;
struct LogicGrid;
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
	StarNode *StarsLayer::getStarByGrid(LogicGrid grid);
	void showStars();
	void starInitDone();
	StarNode *getClickedStar(CCPoint pos);
	std::vector<StarNode *>	getStarNeighbours(StarNode *star);
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);

	CCPoint getPosByGrid(LogicGrid grid);
private:
	StarUtil *m_pStarUtil;
	std::vector<StarNode *> m_starsSprite;
};
#endif 