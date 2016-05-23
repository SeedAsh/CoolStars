#ifndef __SHOP_LAYER_H__ 
#define __SHOP_LAYER_H__ 
#include "cocos-ext.h"
#include "ConfData.h"
USING_NS_CC_EXT;

class ShopLayer :
    public CCLayer
{
public:
    ShopLayer(void);
    ~ShopLayer(void);
    CREATE_FUNC(ShopLayer);

    virtual bool init();

    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

    virtual void onEnter();
    virtual void onExit();

    void close(CCObject *pSender);
    void purchase(CCObject *pSender);
    void onPayResult();

    void setOnUpdateListener(CCCallFunc *pCallback);

	void payCallBack(CCNode* nouse, int payType, int payResult,int payIntNoUse);
private:
    CCCallFunc *m_pCallback;
	CCLabelTTF *m_pCoinLabel;
};
#endif // __SHOP_LAYER_H__ 
