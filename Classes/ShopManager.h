#ifndef __SHOPMANAGER_H__
#define __SHOPMANAGER_H__
#include "cocos2d.h"

class ShopManager
{
public:
	static ShopManager *theMgr();
	void purchase(int id);
private:
	ShopManager(){}
	void onPurchaseSucceed(int id);
	
};
#endif