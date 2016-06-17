#ifndef __STAGESCENE_H__
#define __STAGESCENE_H__
#include "cocos2d.h"

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