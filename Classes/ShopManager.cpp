#include "ShopManager.h"
#include "DataManager.h"
#include "MyPurchase.h"
#include "UserInfo.h"
USING_NS_CC;
using namespace std;

ShopManager *ShopManager::theMgr()
{
	static ShopManager mgr;
	return &mgr;
}

void ShopManager::purchase(int id)
{
	//调用计费sdk
	MyPurchase::sharedPurchase()->buyItem(id, bind(&ShopManager::onPurchaseSucceed, this, id));
}

void ShopManager::onPurchaseSucceed(int id)
{
	auto data = DataManagerSelf->getShopConfig(id);
	auto theInfo = UserInfo::theInfo();
	theInfo->setDiamond(theInfo->getDiamond() + data.diamond);
}