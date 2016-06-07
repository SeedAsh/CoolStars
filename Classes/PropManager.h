#ifndef __PROPMANAGER_H__
#define __PROPMANAGER_H__
#include "cocos2d.h"

enum PropType
{
	kPropBomb,
	kPropBrush,
	kPropReorder,

	kPorpTypeAmount,
};

class PropManager
{
public:
	~PropManager(){}
	static PropManager *propMgr();
	void loadPropData();
	void save();
	
	int getPropItemAmount(int type);
	void setPropItemAmount(int type, int amount);
private: 
	PropManager(){}

private:
	std::vector<int> m_propAmount;
};
#endif