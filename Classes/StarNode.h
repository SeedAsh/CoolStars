#ifndef __STARNODE_H__
#define __STARNODE_H__
#include "cocos2d.h"
#include "DataManager.h"
#include "CommonMacros.h"
#include "LogicGridUtil.h"
#define  CONNECT_COUNT 2

enum StarType
{
	kEmpty,
	kColorStar,
	kBounceBall,
	kDeadVine,
	kLiveVine,
	kStone,
	kBomb,
	kIron,
	kDiamond,
	kKey,
	
	kStarTypeCount,
};
//Âß¼­Íø¸ñ£¬×óÏÂ½ÇÎª[0,0]

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
	static StarNode *createNodeFatory(const StarAttr &attr);
	virtual ~StarNode(){}
	const StarAttr &getAttr(){ return m_attr; }
	void setLogicGrid(const LogicGrid &grid){ m_attr.grid = grid; }
	void bindView(StarViewNode *view){ m_view = view; }

	void handleClick();
	std::vector<StarNode *> getNeighbours();
	std::vector<StarNode *> getLinkNeighbours();
	void doRemove(bool withExplosion = true);
	void removeNeighbours();
    void moveTo(LogicGrid grid);

	bool canLink(int type, int color);
public:
	virtual std::string getResPath();
	virtual std::string getExplosionPath();
	virtual std::string getBornAnimationPath();
	virtual void onRemove(){}
protected:
    StarNode(const StarAttr &attr);
private:

	const StarsConfig &getConfig();
	void getConnectedStars(StarNode *node, std::vector<StarNode *> &connectedNodes);
protected:
	StarAttr m_attr;
	StarViewNode *m_view;
private:
};

class ColorStar : public StarNode
{
public:
	ColorStar(const StarAttr &attr);
	~ColorStar();
	virtual std::string getResPath();
	virtual std::string getExplosionPath();
};

class BounceBallNode : public StarNode
{
public:

	BounceBallNode(const StarAttr &attr);
	~BounceBallNode(){}
	virtual std::string getResPath();
	virtual std::string getExplosionPath();
};

class StoneNode : public StarNode
{
public:

	StoneNode(const StarAttr &attr) : StarNode(attr){}
	~StoneNode(){}
};


class DeadVineNode : public StarNode
{
public:
	DeadVineNode(const StarAttr &attr);
	~DeadVineNode(){}
	virtual std::string getResPath();
	virtual std::string getExplosionPath();
	virtual void onRemove();
};

class LiveVineNode : public StarNode
{
public:
	LiveVineNode(const StarAttr &attr);
	~LiveVineNode(){}
	virtual std::string getResPath();
	virtual std::string getExplosionPath();
	virtual void onRemove();
};


class IronNode : public StarNode
{
public:

	IronNode(const StarAttr &attr) : StarNode(attr){}
	~IronNode(){}
};

class DiamondNode : public StarNode
{
public:

	DiamondNode(const StarAttr &attr) : StarNode(attr){}
	~DiamondNode(){}
};

class KeyNode : public StarNode
{
public:

	KeyNode(const StarAttr &attr) : StarNode(attr){}
	~KeyNode(){}
};

class BombNode : public StarNode
{
public:

	BombNode(const StarAttr &attr) : StarNode(attr){}
	~BombNode(){}
};

#endif
