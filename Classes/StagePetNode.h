#ifndef __STAGEPETNODE_H__
#define __STAGEPETNODE_H__
#include "cocos2d.h"
#include "TouchNode.h"

class UiLayout;
class PetEntity;
class StagePetNode : public TouchNode
{
public:
	static StagePetNode *create(int petId);
	virtual ~StagePetNode(){}
	virtual bool init();

private:
	StagePetNode(int petId);
	virtual void onTouchBegan();
private:
	int m_petId;
	const PetEntity *m_model;
	UiLayout *m_layout;
};

#endif