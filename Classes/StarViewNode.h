#ifndef __STARViewNode_H__
#define __STARViewNode_H__
#include "cocos2d.h"
#include "StarNode.h"
class StarViewNode : public cocos2d::CCNode
{
public :
	static StarViewNode *create(StarNode *node);
	virtual bool init();

	StarViewNode(StarNode *node);
	StarViewNode(){}
	~StarViewNode();
	
	int getStarType(){ return m_starType; }
	int sameType(int type){ return m_starType == type; }
	LogicGrid getLogicGrid(){ return m_grid; }
	void setLogicGrid(LogicGrid grid){ m_grid = grid; }
	bool hasNeighbour();
	
	void onClick();
	void runExplosion();
	void doMove(LogicGrid grid);
    cocos2d::CCPoint getPosByGrid(LogicGrid grid);

protected:
	int m_colorIndex;
	int m_starType;
	LogicGrid m_grid;



	bool m_isExploded;
	StarNode *m_model;
};


class ColorStarViewNode : public StarViewNode
{
public:
	static ColorStarViewNode *create();
	virtual bool init();

private:
	ColorStarViewNode(){}
	~ColorStarViewNode(){}
};


class StoneViewNode : public StarViewNode
{
public:
	static StoneViewNode *create();
	virtual bool init();

private:
	StoneViewNode(){}
	~StoneViewNode(){}
};



class DeadVineViewNode : public StarViewNode
{
public:
	static DeadVineViewNode *create();
	virtual bool init();

private:
	DeadVineViewNode(){}
	~DeadVineViewNode(){}
};

class LiveVineViewNode : public StarViewNode
{
public:
	static LiveVineViewNode *create();
	virtual bool init();

private:
	LiveVineViewNode(){}
	~LiveVineViewNode(){}
};


class IronViewNode : public StarViewNode
{
public:
	static IronViewNode *create();
	virtual bool init();

private:
	IronViewNode(){}
	~IronViewNode(){}
};


class BounceBallViewNode : public StarViewNode
{
public:
	static BounceBallViewNode *create();
	virtual bool init();

private:
	BounceBallViewNode(){}
	~BounceBallViewNode(){}
};

class diamantViewNode : public StarViewNode
{
public:
	static LiveVineViewNode *create();
	virtual bool init();

private:
	diamantViewNode(){}
	~diamantViewNode(){}
};

class KeyViewNode : public StarViewNode
{
public:
	static LiveVineViewNode *create();
	virtual bool init();

private:
	KeyViewNode(){}
	~KeyViewNode(){}
};

class BombViewNode : public StarViewNode
{
public:
	static BombViewNode *create();
	virtual bool init();

private:
	BombViewNode(){}
	~BombViewNode(){}
};
#endif
