#ifndef __STAGEPETNODE_H__
#define __STAGEPETNODE_H__
#include "cocos2d.h"
#include "TouchNode.h"
#include <functional>

class UiLayout;
class PetEntity;
class StagePetNode : public TouchNode
{
public:
	static StagePetNode *create(int petId);
	virtual ~StagePetNode(){}
	virtual bool init();
	//技能查看
	void setTouchHandle(std::function<void(int)> handle){ m_touchHandle = handle; }
private:
	StagePetNode(int petId);
	virtual bool onTouchBegan(cocos2d::CCPoint pt, bool isInside);
private:
	int m_petId;
	const PetEntity *m_model;
	UiLayout *m_layout;
	std::function<void(int)> m_touchHandle;
};

#endif