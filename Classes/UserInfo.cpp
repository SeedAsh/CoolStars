#include "UserInfo.h"
#include "SqliteHelper.h"
#include "CommonMacros.h"
USING_NS_CC;
using namespace std;

UserInfo *UserInfo::theInfo()
{
	static UserInfo info;
	return &info;
}

void UserInfo::loadUserInfo()
{
	char str[100] = { 0 };
	SqliteHelper helper(DB_SAVING);
	string sql = "select * from save_user_info";
	auto result = helper.readRecord(sql.c_str());
	assert(result.size() == 1);

	auto data = result[0];
	m_diamond = atoi(data[1]);
	m_food = atoi(data[2]);
	m_strength = atoi(data[3]);
	m_runeStone = atoi(data[4]);
	m_key = atoi(data[5]);
	m_isFirstPlay = atoi(data[6]) == 1;
	m_firstPlayTime = atoi(data[7]);
	m_lastLoginInTime = data[8];
}

void UserInfo::setDiamond(int value)
{ 
	m_diamond = value; 

	SqliteHelper sqlHelper(DB_SAVING);
	char str[100] = { 0 };
	sprintf(str, "update save_user_info set %s = '%d' where id = 1;", "diamond", m_diamond);
	sqlHelper.executeSql(str);

	NOTIFY_VIEWS(onDiamondChanged);
}

void UserInfo::setFood(int value)
{
	m_food = value;
	
	SqliteHelper sqlHelper(DB_SAVING);
	char str[100] = { 0 };
	sprintf(str, "update save_user_info set %s = '%d' where id = 1;", "food", m_food);
	sqlHelper.executeSql(str);

	NOTIFY_VIEWS(onFoodChanged);
}

void UserInfo::setStrength(int value)
{
	m_strength = value;

	SqliteHelper sqlHelper(DB_SAVING);
	char str[100] = { 0 };
	sprintf(str, "update save_user_info set %s = '%d' where id = 1;", "strength", m_strength);
	sqlHelper.executeSql(str);

	NOTIFY_VIEWS(onStrengthChanged);
}

void UserInfo::setRuneStone(int value)
{
	m_runeStone = value;

	SqliteHelper sqlHelper(DB_SAVING);
	char str[100] = { 0 };
	sprintf(str, "update save_user_info set %s = '%d' where id = 1;", "rune_stone", m_runeStone);
	sqlHelper.executeSql(str);

	NOTIFY_VIEWS(onRuneStoneChanged);
}

void UserInfo::setKey(int value)
{
	m_key = value;

	SqliteHelper sqlHelper(DB_SAVING);
	char str[100] = { 0 };
	sprintf(str, "update save_user_info set %s = '%d' where id = 1;", "key", m_key);
	sqlHelper.executeSql(str);

	NOTIFY_VIEWS(onKeyChanged);
}

void UserInfo::setFirstPlay(bool isFirstPlay)
{
	m_isFirstPlay = isFirstPlay;

	SqliteHelper sqlHelper(DB_SAVING);
	char str[100] = { 0 };
	sprintf(str, "update save_user_info set %s = '%d' where id = 1;", "first_play", m_isFirstPlay ? 1 : 0);
	sqlHelper.executeSql(str);
}

void UserInfo::setFirstPlayTime(int firstPlayTime)
{
	m_firstPlayTime = firstPlayTime;

	SqliteHelper sqlHelper(DB_SAVING);
	char str[100] = { 0 };
	sprintf(str, "update save_user_info set %s = '%d' where id = 1;", "first_play_time", m_firstPlayTime);
	sqlHelper.executeSql(str);
}

void UserInfo::saveCurLoginInTime()
{
	return;
	//m_isFirstOpenRanking = isFirstOpenRanking;
	/*
	SqliteHelper sqlHelper(DB_SAVING);
	char str[100] = { 0 };
	sprintf(str, "update save_user_info set %s = '%d' where id = 1;", "first_open_ranking", m_isFirstOpenRanking ? 1 : 0);
	sqlHelper.executeSql(str);
	*/
}

void UserInfo::addView(IUserInfoView *view)
{
	auto iter = find(m_views.begin(), m_views.end(), view);
	if (iter == m_views.end())
	{
		m_views.push_back(view);
	}
}

void UserInfo::removeView(IUserInfoView *view)
{
	auto iter = find(m_views.begin(), m_views.end(), view);
	if (iter != m_views.end())
	{
		m_views.erase(iter);
	}
}

bool UserInfo::isFirstLoginToday()
{
	return true;
}