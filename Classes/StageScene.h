#ifndef __STAGESCENE_H__
#define __STAGESCENE_H__
#include "cocos2d.h"
class StageScene :
	public cocos2d::CCLayer
{
public:
	StageScene();
	~StageScene();

	virtual bool init();

	static cocos2d::CCScene* scene();

	static StageScene* create();

};
#endif