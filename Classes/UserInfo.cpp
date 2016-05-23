#include "UserInfo.h"
#include "cocos2d.h"
#include <time.h>
#include "CCUserDefaultEx.h"
#include "GameData.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "MyPurchase.h"
#endif

USING_NS_CC;

int UserInfo::s_iBestScore = 0;
bool UserInfo::s_bShowFishLiBao = true;
bool UserInfo::s_bFirstLogin = true;
int UserInfo::s_nCurrentLevel = 0;
bool UserInfo::s_bShowLogin = false;
int UserInfo::s_nShowLoginDays = 0;

void UserInfo::setBestScore( int score ){
	if (s_iBestScore > score){
		return;
	}
	s_iBestScore = score;
	CCUserDefaultEx::sharedUserDefault()->setIntegerForKey(USERINFO_BESTSCORE, s_iBestScore);
	CCUserDefaultEx::sharedUserDefault()->flush();
}

void UserInfo::init(){
	int coins1 = CCUserDefaultEx::sharedUserDefault()->getIntegerForKey(USERINFO_COINS1,0);
	int coins2 = CCUserDefaultEx::sharedUserDefault()->getIntegerForKey(USERINFO_COINS2,0,ENC_KEY_TWO);
	if (coins1 != coins2){
		CCUserDefaultEx::sharedUserDefault()->setIntegerForKey(USERINFO_COINS1, 0);
		CCUserDefaultEx::sharedUserDefault()->setIntegerForKey(USERINFO_COINS2, 0,ENC_KEY_TWO);
		CCUserDefaultEx::sharedUserDefault()->flush();
	}
	s_iBestScore = CCUserDefaultEx::sharedUserDefault()->getIntegerForKey(USERINFO_BESTSCORE);
	s_bShowFishLiBao = CCUserDefaultEx::sharedUserDefault()->getBoolForKey(USERINFO_FISH_LIBAO,true);	
#if (PAY_PLUGIN_TYPE_SKY == 1 || HAVE_ONE_CENT == 0)
	s_bShowFishLiBao = false;
#elif (PAY_PLUGIN_TYPE_XINYINHE == 1)
	s_bShowFishLiBao = false;
#elif (PAY_PLUGIN_TYPE_SKYMM == 1 || PAY_PLUGIN_TYPE_SKYMMSTRONG == 1)
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if(MyPurchase::sharedPurchase()->m_nCarrietType == -1){
		MyPurchase::sharedPurchase()->m_nCarrietType = MyPurchase::sharedPurchase()->getCarrietType();
	}
	CCLOG("UserInfo::init() MyPurchase::sharedPurchase()->m_nCarrietType = %d",MyPurchase::sharedPurchase()->m_nCarrietType);
	if (MyPurchase::sharedPurchase()->m_nCarrietType != MyPurchase::CARRIET_TYPE_CM){
		s_bShowFishLiBao = false;
	}
	#endif
#endif
	s_bFirstLogin = CCUserDefaultEx::sharedUserDefault()->getBoolForKey(USERINFO_FIRST_LOGIN,true);	
	getLoginDays();
}

void UserInfo::addCoins( int coins ){
	int currentCoins = getCoins() + coins;
    CCUserDefaultEx::sharedUserDefault()->setIntegerForKey(USERINFO_COINS1, currentCoins);
	CCUserDefaultEx::sharedUserDefault()->setIntegerForKey(USERINFO_COINS2, currentCoins,ENC_KEY_TWO);
    CCUserDefaultEx::sharedUserDefault()->flush();
}

bool UserInfo::expendCoins( int coins ){
	int hasCoins = getCoins();
    if (coins > hasCoins){
        return false;
    }
	addCoins(-coins);
    return true;
}

int UserInfo::getCoins(){
	int coins1 = CCUserDefaultEx::sharedUserDefault()->getIntegerForKey(USERINFO_COINS1,0);
	int coins2 = CCUserDefaultEx::sharedUserDefault()->getIntegerForKey(USERINFO_COINS2,0,ENC_KEY_TWO);
	if (coins1 != coins2){
		CCUserDefaultEx::sharedUserDefault()->setIntegerForKey(USERINFO_COINS1, 0);
		CCUserDefaultEx::sharedUserDefault()->setIntegerForKey(USERINFO_COINS2, 0,ENC_KEY_TWO);
		CCUserDefaultEx::sharedUserDefault()->flush();
		return GameData::getInstance()->m_nDefaultCoin;
	}
	return coins1;
}

void UserInfo::setFishLiBao(){
	s_bShowFishLiBao = false;
	CCUserDefaultEx::sharedUserDefault()->setBoolForKey(USERINFO_FISH_LIBAO,false);
	CCUserDefaultEx::sharedUserDefault()->flush();
}

void UserInfo::setFirstLogin(){
	s_bFirstLogin = false;
	CCUserDefaultEx::sharedUserDefault()->setBoolForKey(USERINFO_FIRST_LOGIN,false);
	CCUserDefaultEx::sharedUserDefault()->flush();
}

void UserInfo::addProByType(int proType,int count){
	int pro = getProCount(proType) + count;
	if (proType == USERINFO_PRO_TYPE_BOMB){		
		CCUserDefaultEx::sharedUserDefault()->setIntegerForKey(USERINFO_PRO_BOMB1, pro);
		CCUserDefaultEx::sharedUserDefault()->setIntegerForKey(USERINFO_PRO_BOMB2, pro, ENC_KEY_TWO);
	}else if (proType == USERINFO_PRO_TYPE_REFLASH){
		CCUserDefaultEx::sharedUserDefault()->setIntegerForKey(USERINFO_PRO_REFLASH1, pro);
		CCUserDefaultEx::sharedUserDefault()->setIntegerForKey(USERINFO_PRO_REFLASH2, pro, ENC_KEY_TWO);
	}else{
		CCUserDefaultEx::sharedUserDefault()->setIntegerForKey(USERINFO_PRO_PAINT1, pro);
		CCUserDefaultEx::sharedUserDefault()->setIntegerForKey(USERINFO_PRO_PAINT2, pro, ENC_KEY_TWO);
	}
	CCUserDefaultEx::sharedUserDefault()->flush();
}

int UserInfo::getProCount(int proType){
	if (proType == USERINFO_PRO_TYPE_BOMB){
		int pro1 = CCUserDefaultEx::sharedUserDefault()->getIntegerForKey(USERINFO_PRO_BOMB1,GameData::getInstance()->m_nDefaultBombCount);
		int pro2 = CCUserDefaultEx::sharedUserDefault()->getIntegerForKey(USERINFO_PRO_BOMB2,GameData::getInstance()->m_nDefaultBombCount,ENC_KEY_TWO);
		if (pro1 != pro2){
			pro1 = GameData::getInstance()->m_nDefaultBombCount;
			CCUserDefaultEx::sharedUserDefault()->setIntegerForKey(USERINFO_PRO_BOMB1, GameData::getInstance()->m_nDefaultBombCount);
			CCUserDefaultEx::sharedUserDefault()->setIntegerForKey(USERINFO_PRO_BOMB2, GameData::getInstance()->m_nDefaultBombCount,ENC_KEY_TWO);
			CCUserDefaultEx::sharedUserDefault()->flush();
		}
		return pro1;
	}
	if (proType == USERINFO_PRO_TYPE_PAINT){
		int pro1 = CCUserDefaultEx::sharedUserDefault()->getIntegerForKey(USERINFO_PRO_PAINT1,GameData::getInstance()->m_nDefaultPaintCount);
		int pro2 = CCUserDefaultEx::sharedUserDefault()->getIntegerForKey(USERINFO_PRO_PAINT2,GameData::getInstance()->m_nDefaultPaintCount,ENC_KEY_TWO);
		if (pro1 != pro2){
			pro1 = GameData::getInstance()->m_nDefaultPaintCount;
			CCUserDefaultEx::sharedUserDefault()->setIntegerForKey(USERINFO_PRO_PAINT1, GameData::getInstance()->m_nDefaultPaintCount);
			CCUserDefaultEx::sharedUserDefault()->setIntegerForKey(USERINFO_PRO_PAINT2, GameData::getInstance()->m_nDefaultPaintCount,ENC_KEY_TWO);
			CCUserDefaultEx::sharedUserDefault()->flush();
		}
		return pro1;
	}
	if (proType == USERINFO_PRO_TYPE_REFLASH){
		int pro1 = CCUserDefaultEx::sharedUserDefault()->getIntegerForKey(USERINFO_PRO_REFLASH1,GameData::getInstance()->m_nDefaultReflashCount);
		int pro2 = CCUserDefaultEx::sharedUserDefault()->getIntegerForKey(USERINFO_PRO_REFLASH2,GameData::getInstance()->m_nDefaultReflashCount,ENC_KEY_TWO);
		if (pro1 != pro2){
			pro1 = GameData::getInstance()->m_nDefaultReflashCount;
			CCUserDefaultEx::sharedUserDefault()->setIntegerForKey(USERINFO_PRO_REFLASH1, GameData::getInstance()->m_nDefaultReflashCount);
			CCUserDefaultEx::sharedUserDefault()->setIntegerForKey(USERINFO_PRO_REFLASH2, GameData::getInstance()->m_nDefaultReflashCount,ENC_KEY_TWO);
			CCUserDefaultEx::sharedUserDefault()->flush();
		}
		return pro1;
	}
	return 0;
}

void UserInfo::getLoginDays(){
	s_bShowLogin = false;
#if (SHOW_LGOIN == 1)
	s_nShowLoginDays = CCUserDefaultEx::sharedUserDefault()->getIntegerForKey(USERINFO_LOGIN_DAYS,0);
	long loginTime = CCUserDefaultEx::sharedUserDefault()->getIntegerForKey(USERINFO_LOGIN_LASTTIME,0);
	if ((long)(time(NULL) / DAY_SECOND) > loginTime){
		s_nShowLoginDays += 1;
		s_bShowLogin = true;
	}
	if (s_nShowLoginDays > 7 || s_nShowLoginDays < 1 || GameData::getInstance()->m_nLoginGift[s_nShowLoginDays - 1][0] <= 0){
		s_bShowLogin = false;
	}
#endif
}

void UserInfo::setLoginDays(){
	s_bShowLogin = false;
	CCUserDefaultEx::sharedUserDefault()->setIntegerForKey(USERINFO_LOGIN_DAYS,s_nShowLoginDays);
	CCUserDefaultEx::sharedUserDefault()->setIntegerForKey(USERINFO_LOGIN_LASTTIME,(long)(time(NULL) / DAY_SECOND));
	CCUserDefaultEx::sharedUserDefault()->flush();
}

bool UserInfo::useProByType(int proType){
	addProByType(proType, -1);
	return true;
}

