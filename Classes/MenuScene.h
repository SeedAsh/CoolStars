#ifndef _MENUSCENE_H
#define _MENUSCENE_H
#include "cocos2d.h"

class UiLayout;
class MenuScene : public cocos2d::CCLayer 
{
public:  
	virtual bool init();  
	static cocos2d::CCScene* scene();  
	CREATE_FUNC(MenuScene); 
private:
	virtual void onEnter();
	virtual void onExit();
	void initMainLayout();
	void initSettingLayout();

	void toNormalGame(cocos2d::CCObject* pSender);
	void toTreasureGame(cocos2d::CCObject* pSender);
	void drawLottery(cocos2d::CCObject* pSender);
	void toPetPanel(cocos2d::CCObject* pSender);

	void toSetting(cocos2d::CCObject* pSender);
	void toMute(cocos2d::CCObject* pSender);
	void toHelpPanel(cocos2d::CCObject* pSender);

private:
	UiLayout *m_mainLayout;
	UiLayout *m_settingLayout;
	
};

#endif