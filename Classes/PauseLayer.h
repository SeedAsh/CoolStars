#ifndef __PAUSE_LAYER_H__
#define __PAUSE_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class PauseLayer :
    public CCLayer
{
public:
    PauseLayer(void);
    ~PauseLayer(void);

    // implement the "static node()" method manually
    CREATE_FUNC(PauseLayer);

    virtual bool init();

    virtual void onEnter();
    virtual void onExit();

    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

    inline void setOnSaveListener(CCCallFunc *listener) {
        if (listener)
        {
            m_pOnSaveListener = listener;
            m_pOnSaveListener->retain();
        }
    }

    void menuResumeCallback(CCObject* pSender);
    void menuSaveCallback(CCObject* pSender);

private:
    CCCallFunc *m_pOnSaveListener;
};

#endif //__PAUSE_LAYER_H__