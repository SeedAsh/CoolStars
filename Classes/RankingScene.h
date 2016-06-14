#ifndef __RANKINGSCENE_H__
#define __RANKINGSCENE_H__ 
#include "cocos2d.h"

class UiLayout;

class RankingScene :
	public cocos2d::CCLayer
{
public:
	static cocos2d::CCScene* scene();
	CREATE_FUNC(RankingScene);
	virtual bool init();
private:
	RankingScene(){}
	~RankingScene(){}
	void initMainLayout();

	void onLeftPetBtnClicked(cocos2d::CCObject* pSender);
	void onRigthPetBtnClicked(cocos2d::CCObject* pSender);
	void onUpgradeBtnClicked(cocos2d::CCObject* pSender);
private:

	UiLayout *m_mainLayout;

};
#endif