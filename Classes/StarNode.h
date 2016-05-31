#ifndef __STARNODE_H__
#define __STARNODE_H__
#include "cocos2d.h"

#define  CONNECT_COUNT 2
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
	//*
	bool operator == (const LogicGrid &grid)const
	{
		return grid.x == x && grid.y == y;
	}
	bool operator != (const LogicGrid &grid)const
	{
		return (x != grid.x || y != grid.y);
	}
};

struct StarAttr
{
	int type;
	int color;
	LogicGrid grid;
};

class StarViewNode;
class StarNode
{
public:
	static StarNode *createNodeFatory(StarAttr &attr);
	virtual ~StarNode(){}
	const StarAttr &getAttr(){ return m_attr; }
	void setLogicGrid(const LogicGrid &grid){ m_attr.grid = grid; }
	void bindView(StarViewNode *view){ m_view = view; }

	void handleClick();
	std::vector<StarNode *> getNeighbours();
	void runExplosion();

    void moveTo(LogicGrid grid);
protected:
	StarNode(){}
    StarNode(StarAttr &attr);
private:
	void getConnectedStars(StarNode *node, std::vector<StarNode *> &connectedNodes);
private:
	StarAttr m_attr;
	StarViewNode *m_view;
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
