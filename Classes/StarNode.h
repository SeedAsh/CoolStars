#ifndef __STARNODE_H__
#define __STARNODE_H__
#include "cocos2d.h"

enum StarType
{
	kColorStar = 1,
	kStone,
	kDeadVine,
	kLiveVine,
	kIron,
	kBounceBall,
	kdiamant,
	kKey,
	kBomb

};

//Âß¼­Íø¸ñ£¬×óÏÂ½ÇÎª[0,0]
struct LogicGrid
{
	int x;
	int y;
	LogicGrid(int x = 0, int y = 0) : x(x), y(y){}
};

struct StarAttr
{
	int type;
	int color;
};

class StarNode
{
public:
	static StarNode *createNodeFatory(int starIndex);
	virtual ~StarNode(){}
	StarAttr &getAttr(){ return m_attr; }
protected:
	StarNode(){}
	StarNode(StarAttr &attr) : m_attr(attr){}
private:
	StarAttr m_attr;
};

class ColorStar : public StarNode
{
public:
	ColorStar(StarAttr &attr) : StarNode(attr){}
	~ColorStar(){}
};


class StoneNode : public StarNode
{
public:

	StoneNode(){}
	~StoneNode(){}
};



class DeadVineNode : public StarNode
{
public:

	DeadVineNode(){}
	~DeadVineNode(){}
};

class LiveVineNode : public StarNode
{
public:

	LiveVineNode(){}
	~LiveVineNode(){}
};


class IronNode : public StarNode
{
public:

	IronNode(){}
	~IronNode(){}
};


class BounceBallNode : public StarNode
{
public:

	BounceBallNode(){}
	~BounceBallNode(){}
};

class diamantNode : public StarNode
{
public:

	diamantNode(){}
	~diamantNode(){}
};

class KeyNode : public StarNode
{
public:

	KeyNode(){}
	~KeyNode(){}
};

class BombNode : public StarNode
{
public:

	BombNode(){}
	~BombNode(){}
};

#endif
