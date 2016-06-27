#ifndef _USERINFO_H_
#define _USERINFO_H_
#include "cocos2d.h"
struct IUserInfoView
{
	virtual void onDiamondChanged(){}
	virtual void onFoodChanged(){}
	virtual void onStrengthChanged(){}
	virtual void onRuneStoneChanged(){}
};
class UserInfo
{
public: 
	static UserInfo *theInfo();

	void loadUserInfo();
	void addView(IUserInfoView *view);
	void removeView(IUserInfoView *view);
public:
	void setDiamond(int value);
	int getDiamond(){ return m_diamond; }

	void setFood(int value);
	int getFood(){ return m_food; }

	void setStrength(int value);
	int getStrength(){ return m_strength; }

	void setRuneStone(int value);
	int getRuneStone(){ return m_runeStone; }
	
private:
	UserInfo(){}
private:
	int m_diamond;
	int m_food;
	int m_strength;
	int m_runeStone; //符石
	std::vector<IUserInfoView *>m_views;

};
#endif