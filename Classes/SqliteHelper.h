#ifndef __SQLITEHELPER_H__
#define __SQLITEHELPER_H__ 

#include "sqlite3.h"
#include "cocos2d.h"

/*
#define DB_NAME "coolstar.db"
#define DB_FILE_PATH "data/coolstar.db"
*/
#define DB_COOLSTAR "data/coolstar.db"
#define DB_SAVING "data/saving.db"

//对于同一个数据库， 尽量保持只有一个

class SqliteHelper
{
public:
	SqliteHelper(const char* dbPath);
	~SqliteHelper();

	void openDB(const char* dbPath);
	void createTable(const char *sql_str);
	void insertRecordIntoSqlite(const char *sql_str);
	std::vector<std::vector<char *>> readRecord(const char *sql_str);
	void clearTable(const char *tabelName);
	void closeDB();

	void openTransaction(bool open);//事务开启控制，执行大量数据存储时，可以打开
private:
	sqlite3* prepareTableInDB(const char* dbFilename);
private:
	sqlite3 *m_pGameDataBase;
	std::string m_tableName;
};
#endif