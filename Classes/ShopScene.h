#ifndef __SHOPSCENE_H__ 
#define __SHOPSCENE_H__ 
#include "cocos2d.h"

class UiLayout;

class ShopScene :
	public cocos2d::CCLayer
{
public:
	static cocos2d::CCScene* scene();
	CREATE_FUNC(ShopScene);
	virtual bool init();
private:
	ShopScene(){}
	~ShopScene(){}
	void initPanel();

	void onLeftPetBtnClicked(cocos2d::CCObject* pSender);
	void onRigthPetBtnClicked(cocos2d::CCObject* pSender);
	void onUpgradeBtnClicked(cocos2d::CCObject* pSender);
private:

	UiLayout *m_layout;

};
#endif