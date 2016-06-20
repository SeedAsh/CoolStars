#ifndef __LISTVIEW_H__
#define __LISTVIEW_H__
#include "cocos2d.h"
#include "TouchNode.h"

class ListView
	: public cocos2d::CCNode
	, public cocos2d::CCTouchDelegate
{
public:
	static ListView *create(const cocos2d::CCSize &size);
	void setTouchPriority(int touchPriority){ m_touchPriority = touchPriority; }
	int addNode(cocos2d::CCNode *node);
	void removeNode(int index);
	cocos2d::CCNode *getNode(int index);
	int count(){ return m_nodes.size(); }
	void setSpacing(float spacing){ m_spacing = spacing; }
	void clear();
private:
	ListView(const cocos2d::CCSize &size);
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

private:
	cocos2d::CCNode *m_content;
	cocos2d::CCClippingNode *m_clippingNode;
	std::vector<cocos2d::CCNode *> m_nodes;
	cocos2d::CCSize m_size;
	int m_touchPriority;
	float m_spacing;

	cocos2d::CCPoint m_beganPt;
};
#endif