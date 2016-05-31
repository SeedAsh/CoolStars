#ifndef __PROPMANAGER_H__
#define __PROPMANAGER_H__

class PropManager
{
public:
	static PropManager *propMgr();
	void loadPropData();
private: 
	PropManager();
	~PropManager();
private:
};
#endif