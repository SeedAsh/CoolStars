#ifndef __SHOPSCENE_H__ 
#define __SHOPSCENE_H__ 
#include "cocos2d.h"

class UiLayout;

class ShopNode
	: public cocos2d::CCNode
{
public:
	CREATE_FUNC(ShopNode);
private:
	void onBtnClicked(cocos2d::CCObject* pSender);
	virtual bool init();
private:
	UiLayout *m_layout;
};


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
private:
	UiLayout *m_layout;

};
#endif