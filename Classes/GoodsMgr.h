#ifndef __GOODSMGR_H__
#define __GOODSMGR_H__
#include "cocos2d.h"

class GoodsMgr
{
public:
	static GoodsMgr *theMgr();
	void addGoods(std::vector<int> items);
private:
	
};
#endif