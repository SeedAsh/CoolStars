#ifndef __PropItemView_H__
#define __PropItemView_H__
#include "cocos2d.h"
#include "TouchNode.h"


class PropItemView : public TouchNode
{
public:
	static PropItemView *create(int type);
	virtual ~PropItemView(){}
protected:
	PropItemView();
	virtual bool init();

private:
	virtual void onTouchBegan();
	void runScale();
	virtual void onClick() = 0;
protected:
	std::string m_iconPath;
	int m_type;
private:
	cocos2d::CCLabelTTF *m_label;
};

class PropItemViewBomb : public PropItemView
{
public:
	CREATE_FUNC(PropItemViewBomb);
private:
	virtual bool init();
	virtual void onClick();
};


class PropItemViewBrush : public PropItemView
{
public:
	CREATE_FUNC(PropItemViewBrush);
	virtual bool init();
	virtual void onClick();
};

class PropItemViewReOrder : public PropItemView
{
public:
	CREATE_FUNC(PropItemViewReOrder);
	virtual bool init();
	virtual void onClick();
};


#endif