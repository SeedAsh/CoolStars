#ifndef __STARNODE_H__
#define __STARNODE_H__
#include "cocos2d.h"

#define  CONNECT_COUNT 3
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

//�߼��������½�Ϊ[0,0]
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
	LogicGrid grid;
};

class StarViewNode;
class StarNode
{
public:
	static StarNode *createNodeFatory(StarAttr &attr);
	virtual ~StarNode(){}
	StarAttr &getAttr(){ return m_attr; }
	void bindView(StarViewNode *view){ m_view = view; }

	void handleClick();
	std::vector<StarNode *> getNeighbours();
	void runExplosion();
protected:
	StarNode(){}
	StarNode(StarAttr &attr) : m_attr(attr), m_isExploded(false){}
private:
	void getConnectedStars(StarNode *node, std::vector<StarNode *> &connectedNodes);
private:
	StarAttr m_attr;
	StarViewNode *m_view;
	bool m_isExploded;
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
