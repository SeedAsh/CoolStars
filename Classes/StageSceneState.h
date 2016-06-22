#ifndef __STAGESCENESTATE_H__
#define __STAGESCENESTATE_H__
#include "cocos2d.h"
#include "StarNode.h"
class StarsLayer;
class StageUiLayer;
class StageStateOwner;

class StageSceneState
{
public:
	virtual void doTouch(const LogicGrid &gird) = 0;

protected:
	StageSceneState(StageStateOwner *owner);
protected:
	StarsLayer *m_starsLayer;
	StageUiLayer *m_uiLayer;
	StageStateOwner *m_owner;
};

class StageNormalState : public StageSceneState
{
public:
	StageNormalState(StageStateOwner *owner) : StageSceneState(owner){}
public:
	void doTouch(const LogicGrid &grid);
};


class StagePropsClickState: public StageSceneState
{
public:
	StagePropsClickState(StageStateOwner *owner) : StageSceneState(owner){}
	void setCurProp(int propType){ m_curType = propType; }
public:
	void doTouch(const LogicGrid &grid);
	int m_curType;
};

/*owner*/
class StageStateOwner
{
public:
	StageStateOwner();
	~StageStateOwner();
	void init();
	void setStarsLayer(StarsLayer *starsLayer){ m_starsLayer = starsLayer; }
	void setUiLayer(StageUiLayer *uiLayer){ m_uiLayer = uiLayer; }
	StarsLayer *getStarsLayer(){ return m_starsLayer; }
	StageUiLayer *getUiLayer(){ return m_uiLayer; }
public:
	void enterNormalState();
	void enterPropsClickState(int propType);
public:
	void doTouch(const LogicGrid &grid);
private:
	StarsLayer *m_starsLayer;
	StageUiLayer *m_uiLayer;
	StageSceneState *m_curState;
private:
	StagePropsClickState *m_propsState;
	StageNormalState *m_normalState;
};
#endif