#ifndef __CONFIRM_LAYER_H__ 
#define __CONFIRM_LAYER_H__

#include "ConfData.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;

#define CONFIRM_SURE_BTN_TAG 1
#define CONFIRM_CLOSE_BTN_TAG 2

class ConfirmLayer :
	public CCLayer
{
public:
	ConfirmLayer(void);
	~ConfirmLayer(void);
	CREATE_FUNC(ConfirmLayer);

	virtual bool init();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	virtual void onEnter();
	virtual void onExit();

	void menuClicked(CCObject *pSender);
	void setPayCallBack(CCObject *target,MyPayProducts product, SEL_CallFuncN3I selector = NULL );
private:
	SEL_CallFuncN3I m_pCallback;
	CCObject* m_pCallbackTarget;
	int m_nCurrentPayType;
};






#endif