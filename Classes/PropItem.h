#ifndef __PROPITEM_H__
#define __PROPITEM_H__

struct PropData
{
	int amount;

};

class PropItem
{
protected:
	PropItem();
	~PropItem();
private:
	int m_amount;
};

class PropItemBomb : public PropItem
{
public:
	PropItemBomb(){}
	~PropItemBomb(){}
};


class PropItemBrush : public PropItem
{
public:
	PropItemBrush(){}
	~PropItemBrush(){}
};

class PropItemReOrder : public PropItem
{
public:
	PropItemReOrder(){}
	~PropItemReOrder(){}
};

/*
class PropItemBomb : public PropItem
{
	PropItemBomb(){}
	~PropItemBomb(){}
};
*/
#endif