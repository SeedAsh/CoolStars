#ifndef __STAGESCENE_H__
#define __STAGESCENE_H__
#include "cocos2d.h"

#define ZORDER_BACKGROUND 0 
#define ZORDER_STARS 10 
#define	ZORDE_UI  20
class StageScene :
	public cocos2d::CCLayer
{
public:
	static cocos2d::CCScene* scene();

	StageScene();
	~StageScene();
	virtual bool init();
	static StageScene* create();

private :
};
#endif