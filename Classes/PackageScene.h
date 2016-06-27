#ifndef __PACKGESCENE_H__
#define __PACKGESCENE_H__ 
#include "cocos2d.h"
#include "BasePanel.h"
#include "ScaleDialog.h"
#include <functional>

class UiLayout;

enum PackageType
{
	kPackPause,
	kPackageStrength,
	kPackageStep,
	kPackageProps,
	kPackageDiamond,
};

class PackageView: public cocos2d::CCNode
{
public:
	static PackageView *create(int type, int touchPriority);
	void setBtnHanle(std::function<void()> handle){ m_handle = handle; }

private:
	PackageView(int type,int touchPriority);
	virtual bool init();
	void initLayout();
	void onCancelBtnClicked(cocos2d::CCObject* pSender);
	void onBuyBtnClicked(cocos2d::CCObject* pSender);
	
private:
	UiLayout *m_layout;
	std::function<void()> m_handle;
	int m_type;
	int m_touchPriority;
};

class PackageScene : public BasePanel
{
public:
	CREATE_FUNC(PackageScene);
	
private:
	virtual bool init();
};



class PackageDialog : public ScaleDialog
{
public:
	static PackageDialog *create(int type);
private:
	PackageDialog(int type) :m_type(type){}
	virtual bool init();
private:
	int m_type;
};
#endif