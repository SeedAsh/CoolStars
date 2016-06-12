#ifndef __PETVIEW_H__
#define __PETVIEW_H__
#include "cocos2d.h"
#include "TouchNode.h"

class PetEntity;
class PetView : public TouchNode
{
public:
	static PetView *create(int petId);
	virtual ~PetView(){}
	virtual bool init();

private:
	PetView(int petId);
	virtual void onTouchBegan();
private:
	int m_petId;
	const PetEntity *m_model;
};

//ø’∏Òpet Œ¥…œ≥°
class PetEmptyView : public TouchNode
{
public:
	static PetEmptyView *create();
	virtual bool init();
private:
	PetEmptyView(){}
	virtual void onTouchBegan();

};
#endif