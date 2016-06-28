#ifndef __STAGETARGETVIEW_H__
#define __STAGETARGETVIEW_H__ 
#include "cocos2d.h"
#include "StageTarget.h"
#include "StageModel.h"

class UiLayout;

class StageTargetView
	: public cocos2d::CCNode
	, public IStageView
{
public:
	static StageTargetView *create(const EraseStarsData &data);
private:
	StageTargetView(const EraseStarsData &data);
	virtual bool init();
	void initLayout();
	virtual void onStepsChanged();
	void refreshNum();
	virtual void onEnter();
	virtual void onExit();
private:
	UiLayout *m_layout;
	EraseStarsData m_targetData;
};
#endif