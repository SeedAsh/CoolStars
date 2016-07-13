#ifndef __REDPACKAGEMODULE_H__
#define __REDPACKAGEMODULE_H__
#include "cocos2d.h"

enum RedPackageType
{
	kRedPackageDiamond,
	kRedPackageDiamondPackage,
};

class RedPackageModule
{
public:
	RedPackageModule();
	bool isShowUp();
	int whitchRedPackage();
	void openRedPackage(int type);
private:
	int m_times;
};
#endif