#ifndef __PAUSE_LAYER_H__
#define __PAUSE_LAYER_H__

#include "cocos2d.h"
#include <functional>
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

	void setOnSaveListener(std::function<void()> listener){ m_pOnSaveListener = listener; }
 

    void menuResumeCallback(CCObject* pSender);
    void menuSaveCallback(CCObject* pSender);

private:
	std::function<void()>  m_pOnSaveListener;
};

#endif //__PAUSE_LAYER_H__