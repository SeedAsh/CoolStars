#ifndef __STAGESCENE_H__
#define __STAGESCENE_H__
#include "cocos2d.h"

#define ZORDER_BACKGROUND 0 
#define	ZORDE_UI  10
#define ZORDER_STARS	20
class StageScene :
	public cocos2d::CCLayer
{
public:
	static cocos2d::CCScene* scene();

	StageScene();
	~StageScene();
	virtual bool init();
	static StageScene* create();

	void initBackground();
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
private :
};
#endif