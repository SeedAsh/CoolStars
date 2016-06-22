#ifndef __STAGESCENE_H__
#define __STAGESCENE_H__
#include "cocos2d.h"
#include "BasePanel.h"

class StageScene :
	public BasePanel
{
public:
	CREATE_FUNC(StageScene);
	StageScene();
	~StageScene();
	virtual bool init();

private :
};
#endif