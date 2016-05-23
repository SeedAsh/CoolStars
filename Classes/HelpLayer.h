#ifndef __HELP_LAYER_H__ 
#define __HELP_LAYER_H__ 
#include "cocos-ext.h"
#include "cocos2d.h"
USING_NS_CC;
USING_NS_CC_EXT;

class HelpLayer :
	public CCLayer
{
public:
	HelpLayer(void);
	~HelpLayer(void);
	CREATE_FUNC(HelpLayer);

	virtual bool init();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	virtual void onEnter();
	virtual void onExit();

	void close(CCObject *pSender);
private:

};
#endif // __SHOP_LAYER_H__ 