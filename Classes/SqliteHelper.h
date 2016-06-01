#ifndef __SQLITEHELPER_H__
#define __SQLITEHELPER_H__ 

#include "sqlite3.h"
#include "cocos2d.h"

#define DB_NAME "coolstar.db"
#define DB_FILE_PATH "data/coolstar.db"

//对于同一个数据库， 尽量保持只有一个

class SqliteHelper
{
public:
	SqliteHelper();
	~SqliteHelper();

	sqlite3* prepareTableInDB(const char* table, const char* dbFilename);
	void createTable(const char *sql_str);
	void insertRecordIntoSqlite(const char *sql_str);
	std::vector<std::vector<char *>> readRecord(const char *sql_str);
	void closeDB();
private:
	sqlite3 *m_pGameDataBase;
	std::string m_tableName;
};
#endif