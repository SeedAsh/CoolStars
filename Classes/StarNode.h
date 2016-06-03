#ifndef __STARNODE_H__
#define __STARNODE_H__
#include "cocos2d.h"
#include "DataManager.h"
#include "CommonMacros.h"
#define  CONNECT_COUNT 2

enum StarType
{
	kEmpty,

	kRedStar,
	kYellowStar,
	kBlueStar,
	kGreenStar,
	kPurpleStar,

	kStone,
	kDeadVine,
	kLiveVine,

	kIron,
	kdiamond,
	kKey,
	kBomb,

	kBounceRedBall,
	kBounceYellowBall,
	kBounceBlueBall,
	kBounceGreenBall,
	kBouncePurpleBall,

	kRandomColorStar,
	kRandomBounceBall,
	
	kStarTypeCount,
};
//逻辑网格，左下角为[0,0]
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
	LogicGrid grid;
};

class StarViewNode;
class StarNode
{
public:
	static StarNode *createNodeFatory(const StarAttr &attr);
	virtual ~StarNode(){}
	const StarAttr &getAttr(){ return m_attr; }
	void setLogicGrid(const LogicGrid &grid){ m_attr.grid = grid; }
	void bindView(StarViewNode *view){ m_view = view; }

	void handleClick();
	std::vector<StarNode *> getNeighbours();
	void runExplosion();
	void removeSelf();//没有爆炸特效
    void moveTo(LogicGrid grid);

	const StarsConfig &getConfig();

public:
	virtual bool isNeighbour(int type){ return false; }
protected:
	StarNode(){}
    StarNode(StarAttr &attr);
private:
	void getConnectedStars(StarNode *node, std::vector<StarNode *> &connectedNodes);
protected:
	StarAttr m_attr;
	StarViewNode *m_view;
};

class ColorStar : public StarNode
{
public:
	ColorStar(StarAttr &attr, int color) : StarNode(attr), m_color(color){}
	~ColorStar(){}
public:
	virtual bool isNeighbour(int type);
private:
	int m_color;
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

class diamondNode : public StarNode
{
public:

	diamondNode(){}
	~diamondNode(){}
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
