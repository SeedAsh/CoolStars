#ifndef __LOGIN_LAYER_H__ 
#define __LOGIN_LAYER_H__ 
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class LoginLayer :
public CCLayer
{
public:
	LoginLayer(void);
	~LoginLayer(void);
	CREATE_FUNC(LoginLayer);

	virtual bool init();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	virtual void onEnter();
	virtual void onExit();
	void addLoginGift();
	void loginAni();
	void close(CCObject *pSender);
	void menuClick(CCObject *pSender);
	void payCallBack(CCNode* nouse, int payType, int payResult,int payIntNoUse);
private:
	enum {
		Z_ORDER_LOGIN_BG,
		Z_ORDER_LOGIN_FG, 
		Z_ORDER_LOGIN_BTN
	};
	CCSprite *m_pGetAni;
};

#endif