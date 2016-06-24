#ifndef __RANKINGPANELUTIL_H__
#define __RANKINGPANELUTIL_H__
#include "cocos2d.h"
#include "ScaleDialog.h"

class UiLayout;

class RankingNameInputPanel
	: public ScaleDialog
{
public:
	CREATE_FUNC(RankingNameInputPanel);
	
private:
	virtual bool init();
	void initLayout();
	void refreshName(std::string name);
	void onGenRandomName(cocos2d::CCObject* pSender);
	void onConfirm(cocos2d::CCObject* pSender);
private:
	UiLayout *m_layout;
};

class RankingNode
	: public cocos2d::CCNode
{
public:
	static RankingNode *create(int id);
private:
	RankingNode(int id) : m_id(id){}
	virtual bool init();
private:
	UiLayout *m_layout;
	int m_id;
};

class RankingOpponentNode
	: public cocos2d::CCNode
{
public:
	static RankingOpponentNode *create();
private:
	RankingOpponentNode(){}
	virtual bool init();
private:
	UiLayout *m_layout;
};


class RankingOpponentUpgradePanel
	: public ScaleDialog
{
public:
	CREATE_FUNC(RankingOpponentUpgradePanel);

private:
	virtual bool init();
	void initLayout();
	void onConfirm(cocos2d::CCObject* pSender);
	void doMoveAction();
private:
	UiLayout *m_layout;
};
#endif