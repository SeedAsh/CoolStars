#ifndef __LOTTERYSCENE_H__
#define __LOTTERYSCENE_H__ 
#include "cocos2d.h"

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
	: public cocos2d::CCLayer
{
public:
	static cocos2d::CCScene* scene();
	CREATE_FUNC(LotteryScene);
	virtual bool init();
private:
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