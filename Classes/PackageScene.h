#ifndef __PACKGESCENE_H__
#define __PACKGESCENE_H__ 
#include "cocos2d.h"

class UiLayout;

enum PackageType
{
	kPackageStep,
	kPackageProps,
	kPackageStrength,
	kPackageDiamond,
	kPackPause,
};

class PackageView : public cocos2d::CCNode
{
public:
	static PackageView *create(int type);
	
private:
	PackageView(int type);
	virtual bool init();
	void initLayout();
	void onCancelBtnClicked(cocos2d::CCObject* pSender);
	void onBuyBtnClicked(cocos2d::CCObject* pSender);
private:
	UiLayout *m_layout;
	int m_type;
};

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