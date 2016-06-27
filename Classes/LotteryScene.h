#ifndef __LOTTERYSCENE_H__
#define __LOTTERYSCENE_H__ 
#include "cocos2d.h"
#include "BasePanel.h"

class UiLayout;

class LotteryNode
	: public cocos2d::CCNode
{
public:
	CREATE_FUNC(LotteryNode);
	virtual bool init();
private:
	UiLayout *m_layout;
};

class LotteryScene 
	: public BasePanel
	, cocos2d::CCTouchDelegate
{
public:
	CREATE_FUNC(LotteryScene);
	virtual bool init();
private:
	virtual void onEnter();
	virtual void onExit();
	LotteryScene(){}
	~LotteryScene(){}
	void initLayout();
	void initBottomLayout();
	void toPetScene(cocos2d::CCObject* pSender);
	void startLottery(cocos2d::CCObject* pSender);
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
private:
	UiLayout *m_layout;
	UiLayout *m_bottomLayout;

};
#endif