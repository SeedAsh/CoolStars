#ifndef __QUICKBUY_SCENE_H__
#define __QUICKBUY_SCENE_H__

#include "ConfData.h"

#define QUICK_MENU_BUY_TAG 1
#define QUICK_MENU_CLOSE_TAG 2

class QuickBuyLayer :
	public CCLayer{
public:
	QuickBuyLayer(void);
	~QuickBuyLayer(void);

	// implement the "static node()" method manually
	CREATE_FUNC(QuickBuyLayer);
	static QuickBuyLayer* create(int stage);
	virtual bool init();
	bool init(int stage);
	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	void setCallbackListener(CCObject *target,SEL_CallFuncN3I pListener = NULL);

	void onMenuBtnCallBack(CCObject* pSender);
	void autoBuy(float dt);
private:
	SEL_CallFuncN3I m_pCallback;
	CCObject *m_pCallbackTarget;
	int m_pCurrentStage;
};
#endif