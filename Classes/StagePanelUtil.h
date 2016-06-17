#ifndef __STAGEPANELUTIL_H__
#define __STAGEPANELUTIL_H__

#include "cocos2d.h"
#include "TouchNode.h"

class UiLayout;
class StagePetSkillPanel: public TouchNode
{
public:
	static StagePetSkillPanel *create(int touchPriority);
	StagePetSkillPanel(int touchPriority) : TouchNode(touchPriority){}
	virtual bool init();
	
	virtual bool onTouchBegan(cocos2d::CCPoint pt, bool isInside);
private:
	UiLayout *m_layout;
};

class ChangeStarColorPanel:public TouchNode
{
public:
	static ChangeStarColorPanel *create(int touchPriority);
	ChangeStarColorPanel(int touchPriority) : TouchNode(touchPriority){}
	virtual bool init();

	virtual bool onTouchBegan(cocos2d::CCPoint pt, bool isInside);
private:
	UiLayout *m_layout;

};

#endif