#ifndef __STARNODE_H__
#define __STARNODE_H__
#include "cocos2d.h"

class StarNode : public cocos2d::CCNode
{
public :
	static StarNode *create();
	virtual bool init();

	StarNode(){}
	~StarNode(){}
	
	CCNode *getNeighbours(){}
	void onClick(){}

protected:
	int colorIndex;
	
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
