#ifndef __PETSCENE_H__
#define __PETSCENE_H__ 
#include "cocos2d.h"
#include "ScaleDialog.h"
class PetScene :
	public ScaleDialog 
{
public:
	//static cocos2d::CCScene* scene();
	CREATE_FUNC(PetScene);
	virtual bool init();
private:
	PetScene(){}
	~PetScene(){}
private:
};
#endif