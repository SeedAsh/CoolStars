#include "UserInfo.h"
#include "SqliteHelper.h"
#include "CommonMacros.h"
#include "TimeUtil.h"
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
	m_lastLoginInTime = atoi(data[8]);
}

void UserInfo::init()
{
	loadUserInfo();

	if (m_isFirstPlay)
	{
		setFirstPlay(false);
		saveFirstPlayTime();
	}
	saveCurLoginInTime();
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

void UserInfo::saveFirstPlayTime()
{
	m_firstPlayTime = time_util::getCurTime();

	SqliteHelper sqlHelper(DB_SAVING);
	char str[100] = { 0 };
	sprintf(str, "update save_user_info set %s = '%d' where id = 1;", "first_play_time", m_firstPlayTime);
	sqlHelper.executeSql(str);
}

void UserInfo::saveCurLoginInTime()
{
	m_lastLoginInTime = time_util::getCurTime();
	
	SqliteHelper sqlHelper(DB_SAVING);
	char str[100] = { 0 };
	sprintf(str, "update save_user_info set %s = '%d' where id = 1;", "last_login_in", m_lastLoginInTime);
	sqlHelper.executeSql(str);
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
	int curTime = time_util::getCurTime();
	auto curData = time_util::getDate(curTime);
	auto lastLoginInDate = time_util::getDate(m_lastLoginInTime);

	return !(curData->tm_year == lastLoginInDate->tm_year
		&& curData->tm_mon == lastLoginInDate->tm_mon
		&& curData->tm_mday == lastLoginInDate->tm_mday);
}

int UserInfo::getDaysFromFirstPlay()
{
	static const int kDaySecs = 24 * 3600;
	int startTime = m_firstPlayTime / kDaySecs * kDaySecs;
	
	int days = (m_lastLoginInTime - startTime) / kDaySecs + 1;
	return days;
}

void UserInfo::addGoods(std::vector<int> items)
{
	assert(items.size() % 2 == 0);
	for (size_t i = 0; i < items.size(); i += 2)
	{
		int type = items[i];
		int amount = items[i + 1];
		switch (type)
		{
		case kGoodsDiamond:
			setDiamond(m_diamond + amount);
			break;
		case kGoodsFood:
			setFood(m_food + amount);
			break;
		case kGoodsStrength:
			setStrength(m_strength + amount);
			break;
		case kGoodsRuneStone:
			setRuneStone(m_runeStone + amount);
			break;
		case kGoodsKey:
			setKey(m_key + amount);
			break;
		default:
			break;
		}
	}
	
}