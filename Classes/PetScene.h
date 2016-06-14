#ifndef __PETSCENE_H__
#define __PETSCENE_H__ 
#include "cocos2d.h"

class UiLayout;

class PetScene :
	public cocos2d::CCLayer 
{
public:
	static cocos2d::CCScene* scene();
	CREATE_FUNC(PetScene);
	virtual bool init();
private:
	PetScene(){}
	~PetScene(){}
	void initMainLayout();
	void initBottomLayout();

	void onLeftPetBtnClicked(cocos2d::CCObject* pSender);
	void onRigthPetBtnClicked(cocos2d::CCObject* pSender);
	void onUpgradeBtnClicked(cocos2d::CCObject* pSender);

	void onBackHomeBtnClicked(cocos2d::CCObject* pSender);
	void onGreenPetBtnClicked(cocos2d::CCObject* pSender);
	void onPurplePetBtnClicked(cocos2d::CCObject* pSender);
	void onRedPetBtnClicked(cocos2d::CCObject* pSender);
	void onBluePetBtnClicked(cocos2d::CCObject* pSender);
	void onYellowPetBtnClicked(cocos2d::CCObject* pSender);

private:
	UiLayout *m_bottomLayout;
	UiLayout *m_mainLayout;
};
#endif