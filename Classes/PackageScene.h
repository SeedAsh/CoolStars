#ifndef __PACKGESCENE_H__
#define __PACKGESCENE_H__ 
#include "cocos2d.h"

class UiLayout;

class PackageScene :
	public cocos2d::CCLayer
{
public:
	static cocos2d::CCScene* scene();
	CREATE_FUNC(PackageScene);
	virtual bool init();
private:
	PackageScene(){}
	~PackageScene(){}
	void initMainLayout();

	void onLeftPetBtnClicked(cocos2d::CCObject* pSender);
	void onRigthPetBtnClicked(cocos2d::CCObject* pSender);
	void onUpgradeBtnClicked(cocos2d::CCObject* pSender);
private:

	UiLayout *m_mainLayout;

};
#endif