#ifndef __RANKINGSCENE_H__
#define __RANKINGSCENE_H__ 
#include "cocos2d.h"
#include "BasePanel.h"

class UiLayout;

class rankingNode
	: public cocos2d::CCNode
{
public:
	CREATE_FUNC(rankingNode);
	virtual bool init();
private:
	UiLayout *m_layout;
};

class RankingScene 
	: public BasePanel
{
public:
	CREATE_FUNC(RankingScene);
	virtual bool init();
private:
	RankingScene(){}
	~RankingScene(){}
	void initMainLayout();
private:
	UiLayout *m_layout;

};
#endif