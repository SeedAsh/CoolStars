#ifndef __STARNODE_H__
#define __STARNODE_H__
#include "cocos2d.h"

class StarNode : public cocos2d::CCNode
{
public :
	static StarNode *create();
	virtual bool init();

private:
	StarNode(){}
	~StarNode(){}
};
#endif