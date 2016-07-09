#ifndef __STAGEPETNODE_H__
#define __STAGEPETNODE_H__
#include "cocos2d.h"
#include "TouchNode.h"
#include <functional>
#include "CocoStudio\Armature\CCArmature.h"

class UiLayout;
class PetEntity;
class StagePetSkillIcon;
class StagePetNode : public TouchNode
{
public:
	static StagePetNode *create(int petId, int touchPriority);
	virtual ~StagePetNode(){}
	virtual bool init();
	//技能查看
	void setTouchHandle(std::function<void(int)> handle){ m_touchHandle = handle; }
	int getColor();
	void updateSkillEnergy();
private:
	StagePetNode(int petId, int touchPriority);
	void initLayout();
	virtual bool onTouchBegan(cocos2d::CCPoint pt, bool isInside);
	void runNormalAction(cocos2d::extension::CCArmature *, cocos2d::extension::MovementEventType, const char *);
private:
	int m_petId;
	const PetEntity *m_model;
	UiLayout *m_layout;
	std::function<void(int)> m_touchHandle;
	cocos2d::extension::CCArmature *m_petAnimation;
	StagePetSkillIcon *m_skillIcon;
};

#endif