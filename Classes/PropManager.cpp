#include "PropManager.h"
#include "SqliteHelper.h"
#include "CommonUtil.h"
USING_NS_CC;
using namespace std;
using namespace CommonUtil;

void PropManager::save()
{
	SqliteHelper sqlHelper(DB_SAVING);
	char str[100] = { 0 };
	string sql = "replace into save_prop values(1,\"";
	for (size_t i = 0; i < m_propAmount.size(); ++i)
	{
		sprintf(str, "%d,", m_propAmount[i]);
		sql += str;
	}
	if (m_propAmount.size() > 0)
	{
		sql = sql.substr(0, sql.length() - 1);
	}
	sql += "\");";
	sqlHelper.insertRecordIntoSqlite(sql.c_str());
}


void PropManager::loadPropData()
{
	SqliteHelper sqlHelper(DB_SAVING);
	string sql = "select * from save_prop;";
	auto result = sqlHelper.readRecord(sql.c_str());
	assert(result.size() == 1);

	m_propAmount = parseStrToInts(result[0][1]);
}

int PropManager::getPropItemAmount(int type)
{
	assert(type >= 0 && type < kPorpTypeAmount);
	return m_propAmount[type];
}

void PropManager::setPropItemAmount(int type, int amount)
{
	assert(type >= 0 && type < kPorpTypeAmount);
	if (type >= 0 && type < kPorpTypeAmount)
	{
		m_propAmount[type] = amount;
		save();
	}
}

PropManager *PropManager::propMgr()
{
	static PropManager mgr;
	return &mgr;
}

