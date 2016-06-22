#ifndef __BASEPANEL_H__
#define __BASEPANEL_H__
#include "cocos2d.h"

class BasePanel
	: public cocos2d::CCNode
{
public:
	virtual bool init();
	virtual ~BasePanel(){}
protected:
	BasePanel();
protected:
	int m_touchPriority;
private:
	
};
#endif