#ifndef __PRESTAGEPETSLOT_H__
#define __PRESTAGEPETSLOT_H__
#include "cocos2d.h"
#include "PreStageModel.h"

class UiLayout;
class ListPetView;

class PreStagePetSlot
	: public cocos2d::CCNode
	, public IPreStageView
{
public:
	static PreStagePetSlot *create(int petId);
	virtual bool init();
	
private:
	PreStagePetSlot(int petId): m_curPetId(petId){}
	void initLayout();
	void refresh();
	void onSelectItemCallback(int index);
	virtual void onEnter();
	virtual void onExit();
	virtual void onPetSelect();
private:
	UiLayout *m_layout;
	ListPetView *m_listView;
	std::vector<int> m_itemsIndex;
	int m_curPetId;
};
#endif