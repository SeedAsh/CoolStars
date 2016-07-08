#ifndef __STAGETARGETVIEW_H__
#define __STAGETARGETVIEW_H__ 
#include "cocos2d.h"
#include "StageTarget.h"
#include "StarsController.h"
#include "StageDataMgr.h"

class UiLayout;

class StageTargetView
	: public cocos2d::CCNode
	, public IStageDataView
{
public:
	static StageTargetView *create(const EraseStarsData &data);
private:
	StageTargetView(const EraseStarsData &data);
	virtual bool init();
	void initLayout();
	void refreshNum();
	virtual void onEnter();
	virtual void onExit();
private:
	virtual void onStepsChanged();
private:
	UiLayout *m_layout;
	EraseStarsData m_targetData;
};
#endif