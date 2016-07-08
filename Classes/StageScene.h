#ifndef __STAGESCENE_H__
#define __STAGESCENE_H__
#include "cocos2d.h"
#include "BasePanel.h"
#include "StageSceneState.h"

class StageScene :
	public BasePanel
{
public:
	CREATE_FUNC(StageScene);
	~StageScene();
private:
	StageScene();
	virtual bool init();
private :
	StageStateOwner m_stateOwner;
};
#endif