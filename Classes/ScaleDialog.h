#ifndef __SCALEDIALOG_H__
#define __SCALEDIALOG_H__
#include "cocos2d.h"

class ScaleDialog
	: public cocos2d::CCLayer
{
public:
	void runScale();
	virtual ~ScaleDialog(){}
	virtual bool init();
protected:
	ScaleDialog(int touchPriority = 0){}
	void onClose(){}
	CCNode* getMaskLayer();
private:
	virtual void onEnter();
	virtual void onExit();
	void closeCallback(cocos2d::CCObject *pSender);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
private:
	int m_touchPriority;
};
#endif