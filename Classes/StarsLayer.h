#ifndef __STARSLAYER_H__ 
#define __STARSLAYER_H__
#include "cocos2d.h"
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
	void showStars();
	void starInitDone();
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
//	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
//	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
//	virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);

//	virtual void setTouchEnabled(bool value);
private:
	StarUtil *m_pStarUtil;
};
#endif 