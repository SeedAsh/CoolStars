#include "MyPurchase.h"

using namespace cocos2d;


MyPurchase::MyPurchase()
{

}

MyPurchase* MyPurchase::sharedPurchase()
{
	static MyPurchase model;
	return &model;
}

void MyPurchase::buyItem(int id, std::function<void()> callback)
{
	if (callback)
	{
		callback();
	}
}