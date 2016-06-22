#ifndef __PROPMANAGER_H__
#define __PROPMANAGER_H__
#include "cocos2d.h"
#include "StarNode.h"

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
	
	void usePropBomb(const LogicGrid &grid);
	void usePropBrush(const LogicGrid &grid, int color);
	void usePropReorder();
private: 
	PropManager(){}

private:
	std::vector<int> m_propAmount;
};
#endif