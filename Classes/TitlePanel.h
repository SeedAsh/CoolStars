#ifndef __TITLEPANEL_H__
#define __TITLEPANEL_H__
#include "cocos2d.h"
#include "UserInfo.h"

class UiLayout;

enum TitlePanelUi
{
	kTitlePanelStrength,
	kTitlePanelFood,
	kTitlePanelDiamond,
	kTitlePanelBackHome,
};

class TitlePanel
	: public cocos2d::CCNode
	, public IUserInfoView
{
public:
	static TitlePanel *create(int touchPriority);
	virtual bool init();
	void setUiVisible(int who, bool isVisible);
private:
	virtual void onEnter();
	virtual void onExit();

	TitlePanel(int touchPriority): m_touchPriority(touchPriority){}
	void initTopLayout();
	void initBottomLayout();

	void onAddStrengthBtnClicked(cocos2d::CCObject* pSender);
	void onAddDiamondBtnClicked(cocos2d::CCObject* pSender);

	void onBackHomeBtnClicked(cocos2d::CCObject* pSender);
private:
	virtual void onDiamondChanged();
	virtual void onFoodChanged();
	virtual void onStrengthChanged();
	cocos2d::CCAction *getScaleAction();
private:
	UiLayout *m_topLayout;
	UiLayout *m_bottomLayout;
	int m_touchPriority;
};
#endif