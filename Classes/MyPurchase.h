#ifndef __MY_PURCHASE_H__
#define __MY_PURCHASE_H__

#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
#include <jni.h> 
#include "platform/android/jni/JniHelper.h" 
#endif 
#include <functional>

USING_NS_CC;

class MyPurchaseResult
{
public:
	void onPayResult(int ret, const char* msg){}
	void setHandle(){}
};

class MyPurchase
{
public:
	static MyPurchase* sharedPurchase();
	void buyItem(int id, std::function<void()> callback);
private:
	MyPurchase();
};
#endif