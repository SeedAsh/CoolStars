#include "PropManager.h"
PropManager::PropManager()
{

}

PropManager::~PropManager()
{

}

void PropManager::loadPropData()
{

}

PropManager *PropManager::propMgr()
{
	static PropManager mgr;
	return &mgr;
}

