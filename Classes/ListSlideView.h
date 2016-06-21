#ifndef __LISTSLIDEVIEW_H__
#define __LISTSLIDEVIEW_H__
#include "cocos2d.h"
#include "ListView.h"

class ListSlideView
	: public ListView	
{
public:
	static ListSlideView *create(const cocos2d::CCSize &size);
private:
	ListSlideView(const cocos2d::CCSize &size);
	void update(float dt);
	virtual bool init();

	virtual void onTouchBegan(cocos2d::CCTouch *pTouch);
	virtual void onTouchMoved(cocos2d::CCTouch *pTouch);
	virtual void onTouchEnded(cocos2d::CCTouch *pTouch);
private:
	float m_speed;
	float m_scrollTime;
};
#endif