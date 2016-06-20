#ifndef __PRESTAGEPETSLOT_H__
#define __PRESTAGEPETSLOT_H__
#include "cocos2d.h"

class UiLayout;

class PreStagePetSlot
	: public cocos2d::CCNode
{
public:
	CREATE_FUNC(PreStagePetSlot);
	virtual bool init();
	
private:
	void initLayout();
	void onLeftPetBtnClicked(cocos2d::CCObject* pSender);
private:
	UiLayout *m_layout;
};
#endif