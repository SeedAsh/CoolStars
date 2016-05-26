#ifndef __STARSLAYER_H__ 
#define __STARSLAYER_H__
#include "cocos2d.h"
USING_NS_CC;

class StarsLayer
	: public CCLayer
{
public:
	StarsLayer();
	~StarsLayer();

	CREATE_FUNC(StarsLayer);
	virtual bool init();

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
//	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
//	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
//	virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);

//	virtual void setTouchEnabled(bool value);

};
#endif 