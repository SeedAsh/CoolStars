#ifndef __GUIDEVIEW_H__
#define __GUIDEVIEW_H__
#include "cocos2d.h"
class UiLayout;
class GuideView
	: public cocos2d::CCNode
	, public cocos2d::CCTouchDelegate

{
public:
	static GuideView *create(int guideId);

private:
	GuideView(int guideId);
	virtual bool init();

	void initPanel();
	void addMaskLayer();

	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	bool isTargetArea(cocos2d::CCPoint worldPos);
private:
	UiLayout *m_layout;
	int m_guideId;
	cocos2d::CCRect m_targetRect;
};
#endif