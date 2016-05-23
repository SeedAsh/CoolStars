#ifndef _MENUSCENE_H
#define _MENUSCENE_H

#include "cocos-ext.h"
#include "ConfData.h"

#if (PAY_PLUGIN_TYPE_JIDI == 1)
#define MENU_COUNT 4
#else
#define MENU_COUNT 3
#endif
#define FADE_COUNT 2

class Menu : public cocos2d::CCLayer 
{
public:  
	//Menu();
	// Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)  
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend to return the class instance pointer  
	static cocos2d::CCScene* scene();  

	// preprocessor macro for "static create()" constructor ( node() deprecated )  
	CREATE_FUNC(Menu); 

private:
	virtual void onEnter();
	virtual void onExit();
	void NewGame(CCObject* sender);
	void ResumeGame(CCObject* sender);
	void EndGame(CCObject* sender);
	void shopClicked( CCObject* sender );
	void helpClicked( CCObject* sender );
	void SwitchSound(CCObject* sender);
	void moreGame(CCObject* sender);
	void showOrHideLiBao(CCObject* sender);
	void showDaLiBao(CCObject* sender);
	void fishLiBaoClickedCallBack(CCObject* sender);
	virtual void keyBackClicked();

	cocos2d::CCMenuItemSprite* CreateMenuItemSprite(const char* frameName, SEL_MenuHandler selector);
	void explodeFire( CCPoint position );
	void startFire();
	void fire(float dt);
	CCPoint getRandomPosForFire();

	void runFadeInAction(CCNode* sprite);
	void nextMenu( CCNode* node, void* data );
	void runMenuAction(int i);

	void removeAllChildByTag(int tag);

	CCScene* getTansitionScene(CCScene* scene);
	void payCallBack(CCNode* nouse, int payType, int payResult,int payIntNoUse);
	void payLiBaoCallBack(CCNode* nouse, int payType, int payResult,int payTag);
private:
	float fireTime;
	CCPoint light1Pos;
	CCPoint light2Pos;
	CCPoint light3Pos;

	CCPoint menuPos[MENU_COUNT];
	CCMenuItem* menuItem[MENU_COUNT];
	CCNode* fadeNode[FADE_COUNT];
	CCMenuItemSprite* m_pMenuFishItem;
	CCLayer* m_pFishShop;
	CCLabelTTF* m_PlayerNameLbl;
	//CCSprite* m_PlayerBg;
	cocos2d::extension::CCScale9Sprite* m_PlayerBg;
};

#endif