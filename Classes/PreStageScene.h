#ifndef __PRESTAGESCENE_H__
#define __PRESTAGESCENE_H__
#include "cocos2d.h"

class UiLayout;

class PreStageScene
	: public cocos2d::CCNode
{
public:
	static cocos2d::CCScene* scene();
	CREATE_FUNC(PreStageScene);
	virtual bool init();
	
private:
	void initMainLayout();
	void initBottomLayout();
	void toStartGame(cocos2d::CCObject* pSender);
private:
	UiLayout *m_mainLayout;
	UiLayout *m_bottomLayout;
};
#endif