#ifndef __GAMERESULTLAYER_H__
#define __GAMERESULTLAYER_H__
#include "ScaleDialog.h"
#include "BasePanel.h"

class UiLayout;

struct GameResultReward
{
	int food;
	int diamond;
	int key;
};

class GameResultLayer
	: public BasePanel
	, public cocos2d::CCTouchDelegate
{
public:
	bool init(std::string xmlFile);
protected:
	virtual void handelConfirm(){}
	virtual void addGameResultReward(){}

private:
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void initLayout();
	void initRewardData();
	void onConfirmBtnClicked(CCObject *pSender);
	virtual void onEnter();
	virtual void onExit();

	void getRuneStoneReward();
	void addFood(int value);
	void addDiamond(int value);
	void addKey(int value);
protected:
	UiLayout *m_layout;
	GameResultReward m_reward;
};

class GameWinLayer : public GameResultLayer
{
public:
	CREATE_FUNC(GameWinLayer);
	bool init();
private:
	void initPanel();
	virtual void handelConfirm();
	void addGameResultReward();
private:
};


class GameFailLayer : public GameResultLayer
{
public:
	CREATE_FUNC(GameFailLayer);
	bool init();
private:
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void initPanel();
	void onBuyPetBtnClicked(CCObject *pSender);
	virtual void handelConfirm();
	void addGameResultReward();
private:

};
#endif