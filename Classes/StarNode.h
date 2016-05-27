#ifndef __STARNODE_H__
#define __STARNODE_H__
#include "cocos2d.h"
//Âß¼­Íø¸ñ£¬×óÏÂ½ÇÎª[0,0]
struct LogicGrid
{
	int x;
	int y;
	LogicGrid(int x = 0, int y = 0) : x(x), y(y){}
};

class StarNode : public cocos2d::CCNode
{
public :
	static StarNode *create(int starType, LogicGrid grid);
	virtual bool init();

	StarNode(int starType, LogicGrid grid);
	StarNode(){}
	~StarNode();
	
	std::vector<StarNode *>getNeighbours();
	
	int getStarType(){ return m_starType; }
	int sameType(int type){ return m_starType == type; }
	LogicGrid getLogicGrid(){ return m_grid; }
	void setLogicGrid(LogicGrid grid){ m_grid = grid; }
	bool hasNeighbour();
	
	void onClick();
	void runExplosion();
	void doExplodeAction();
	void doMove();

protected:
	int m_colorIndex;
	int m_starType;
	LogicGrid m_grid;
	bool m_isExploded;
};


class ColorStar : public StarNode
{
public:
	static ColorStar *create();
	virtual bool init();

private:
	ColorStar(){}
	~ColorStar(){}
};


class StoneNode : public StarNode
{
public:
	static StoneNode *create();
	virtual bool init();

private:
	StoneNode(){}
	~StoneNode(){}
};



class DeadVineNode : public StarNode
{
public:
	static DeadVineNode *create();
	virtual bool init();

private:
	DeadVineNode(){}
	~DeadVineNode(){}
};

class LiveVineNode : public StarNode
{
public:
	static LiveVineNode *create();
	virtual bool init();

private:
	LiveVineNode(){}
	~LiveVineNode(){}
};


class IronNode : public StarNode
{
public:
	static IronNode *create();
	virtual bool init();

private:
	IronNode(){}
	~IronNode(){}
};


class BounceBallNode : public StarNode
{
public:
	static BounceBallNode *create();
	virtual bool init();

private:
	BounceBallNode(){}
	~BounceBallNode(){}
};

class diamantNode : public StarNode
{
public:
	static LiveVineNode *create();
	virtual bool init();

private:
	diamantNode(){}
	~diamantNode(){}
};

class KeyNode : public StarNode
{
public:
	static LiveVineNode *create();
	virtual bool init();

private:
	KeyNode(){}
	~KeyNode(){}
};

class BombNode : public StarNode
{
public:
	static BombNode *create();
	virtual bool init();

private:
	BombNode(){}
	~BombNode(){}
};
#endif
