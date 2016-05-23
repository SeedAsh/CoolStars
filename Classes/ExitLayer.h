#ifndef __EXIT_LAYER_H__
#define __EXIT_LAYER_H__

#include "ConfData.h"

#define EXIT_MENU_BUY_TAG 1
#define EXIT_MENU_CLOSE_TAG 2
#define EXIT_MENU_CANCEL_TAG 3


class Exit : public cocos2d::CCLayer 
{
public:  
	//Menu();
	// Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)  
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend to return the class instance pointer  
	static cocos2d::CCScene* scene();  

	// preprocessor macro for "static create()" constructor ( node() deprecated )  
	CREATE_FUNC(Exit); 

private:
	virtual void onEnter();
	virtual void onExit();
	virtual void keyBackClicked();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void onMenuBtnCallBack(CCObject* pSender);
	void payCallBack(CCNode* nouse, int payType, int payResult,int payIntNoUse);
	void exitGame();
};
#endif