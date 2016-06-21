#ifndef __PRESTAGEMODEL_H__
#define __PRESTAGEMODEL_H__
#include "cocos2d.h"

struct IPreStageView
{
	virtual void onPetSelect(){}
};

class PreStageModel
{
public:
	static PreStageModel *theModel();
	void addView(IPreStageView *view);
	void removeView(IPreStageView *view);

	void selectPet(int petId);
	std::vector<int> getPetsCanSelect();

private:
	std::vector<int> m_selectedPets;
	std::vector<IPreStageView *>m_views;
};
#endif