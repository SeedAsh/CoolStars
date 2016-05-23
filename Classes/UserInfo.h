#ifndef _USERINFO_H_
#define _USERINFO_H_
#include <string>
#include "cocos2d.h"

#define USERINFO_BESTSCORE "key-bestscore"
#define USERINFO_COINS1 "key-coins-one"
#define USERINFO_COINS2 "key-coins-two"
#define USERINFO_FISH_LIBAO "key-show-fishlibao"
#define USERINFO_PRO_BOMB1 "key-pro-bomb-one"
#define USERINFO_PRO_BOMB2 "key-pro-bomb-two"
#define USERINFO_PRO_PAINT1 "key-pro-paint-one"
#define USERINFO_PRO_PAINT2 "key-pro-paint-two"
#define USERINFO_PRO_REFLASH1 "key-pro-reflash-one"
#define USERINFO_PRO_REFLASH2 "key-pro-reflash-two"
#define USERINFO_FIRST_LOGIN "key-first-login"
#define USERINFO_LOGIN_DAYS "key-login-days"
#define USERINFO_LOGIN_LASTTIME "key-login-lasttime"

#define USERINFO_PRO_TYPE_BOMB 1
#define USERINFO_PRO_TYPE_PAINT 2
#define USERINFO_PRO_TYPE_REFLASH 3
#define USERINFO_TYPE_COIN 4

//一天的秒数
#define DAY_SECOND  86400

class UserInfo {
private:
	UserInfo(){};

public:
	static void init();
	static int getBestScore(){
		return s_iBestScore;
	}
    static int getCoins();
    static void addCoins(int coins);
    static bool expendCoins(int coins);
	static void setBestScore(int score);
	static void setFishLiBao();
	static bool getFishLiBao(){
		return s_bShowFishLiBao;
	}
	static void setFirstLogin();
	static bool getFirstLogin(){
		return s_bFirstLogin;
	}
	static int s_nCurrentLevel;
	static bool s_bShowLogin;
	static int s_nShowLoginDays;
	static int getProCount(int proType);
	static void addProByType(int proType,int count);
	static bool useProByType(int proType);
	static void getLoginDays();
	static void setLoginDays();
private:
	static int s_iBestScore;
	static int s_nBombCount;
	static int s_nPaintCount;
	static int s_nReflashCount;
	static bool s_bShowFishLiBao;
	static bool s_bFirstLogin;
};

#endif