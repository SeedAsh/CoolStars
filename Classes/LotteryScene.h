#ifndef __LOTTERYSCENE_H__
#define __LOTTERYSCENE_H__ 
#include "cocos2d.h"
#include "BasePanel.h"
#include "TouchNode.h"

class UiLayout;

class LotteryNode
	: public TouchNode
{
public:
	static LotteryNode *create(int touchPriority);
	virtual bool init();
private:
	LotteryNode(int touchPriority):TouchNode(touchPriority){}
	virtual bool onTouchBegan(cocos2d::CCPoint pt, bool isInside);
private:
	UiLayout *m_layout;
};

class LotteryScene 
	: public BasePanel
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
private:
	UiLayout *m_layout;
	UiLayout *m_bottomLayout;
};
#endif