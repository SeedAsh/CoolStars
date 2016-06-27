#ifndef __STAGESCENE_H__
#define __STAGESCENE_H__
#include "cocos2d.h"
#include "BasePanel.h"
#include "StageSceneState.h"
class UiLayout;

class StageScene :
	public BasePanel
{
public:
	CREATE_FUNC(StageScene);
	~StageScene();
private:
	StageScene();
	virtual bool init();
	cocos2d::CCNode *getBkGrid();
private :
	StageStateOwner m_stateOwner;
	UiLayout *m_layout;
};
#endif