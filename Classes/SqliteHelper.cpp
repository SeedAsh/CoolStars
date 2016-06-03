#include "SqliteHelper.h"
#include <unordered_map>
USING_NS_CC;
using namespace std;

SqliteHelper::SqliteHelper(const char* dbPath)
{
	/*
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	dbPath = DB_FILE_PATH;
#else
	dbPath = CCFileUtils::sharedFileUtils()->getWritablePath() + DB_NAME;
#endif
*/
	m_pGameDataBase = prepareTableInDB(dbPath);
}

SqliteHelper::~SqliteHelper()
{
	closeDB();
}

vector<vector<char *>> SqliteHelper::readRecord(const char *sql_str)
{
	//���ڴ����ݣ�������ƿ��
	vector<vector<char *>> record;
		char * errMsg = NULL;//������Ϣ
	int result;//sqlite3_exec����ֵ
	char **dbResult; //�� char ** ���ͣ�����*��
	int nRow, nColumn;

	result = sqlite3_get_table(m_pGameDataBase, sql_str, &dbResult, &nRow, &nColumn, &errMsg);
	if (SQLITE_OK == errMsg)
	{
		//row ��1��ʼ ��Ϊ0��һ��������
		for (int row = 1; row <= nRow; ++row)
		{
			auto begin = dbResult + nColumn * row;
			vector<char *> rowValues(begin, begin + nColumn);
			record.push_back(rowValues);
		}
		CCLOG("succeed!!!");
	}
	else
	{
		CCLOG("read table failed\n");
	}

	return record;
}

sqlite3* SqliteHelper::prepareTableInDB(const char* dbFilename)
{
	sqlite3 *splite2Data = 0;
	char *errMsg = 0;

	if (SQLITE_OK != sqlite3_open(dbFilename, &splite2Data)) {
		CCLOG("Open the Game Data Table falied\n");
		return 0;
	}

	return splite2Data;
}

void SqliteHelper::createTable(const char *sql_str)
{
	//std::string string_sql = "create table if not exists " + std::string(table) + "(  id int unsigned auto_increment primary key,  name varchar(50),  age int,  sex varchar(10))";
	char *errMsg = 0;
	sqlite3_exec(m_pGameDataBase,
		sql_str,
		NULL,
		NULL,
		&errMsg); // create a table;  

	if (errMsg != 0) {
		CCLOG("Create the Data table failed\n");
	}
	{
		CCLOG("create table succeed");
	}
}

void SqliteHelper::insertRecordIntoSqlite(const char *sql_str)
{
	char *perrMsg = 0;
	int info = sqlite3_exec(m_pGameDataBase,
		sql_str,
		0,
		0,
		&perrMsg);
	do{
		if (perrMsg != 0) { // execute the instruct failed  
			CCLOG("insert a record into the table failed\n");
			CCLOG("reason: %d, Error Message: %s \n", info, perrMsg);
			break;
		}
		else
		{
			CCLOG("insert succeed");
		}

	} while (0);
}

void SqliteHelper::clearTable(const char *tabelName)
{
	string sql_str = "delete from ";
	sql_str += tabelName;
	sql_str += " ;";
	char *perrMsg = 0;
	int info = sqlite3_exec(m_pGameDataBase,
		sql_str.c_str(),
		0,
		0,
		&perrMsg);

	if (perrMsg != 0) {
		CCLOG("clear table data failed\n");
	}
	{
		CCLOG("clear table data succeed");
	}
}

void SqliteHelper::openDB(const char* dbPath)
{
	closeDB();
	m_pGameDataBase = prepareTableInDB(dbPath);
}


void SqliteHelper::closeDB()
{
	if (m_pGameDataBase)
	{
		sqlite3_close(m_pGameDataBase);
		m_pGameDataBase = NULL;
	}
}

/*
//ʹ�ûص�������ȡ������ķ���
//����һ
sqlite3_exec(m_pGameDataBase,
read_sql_.c_str(),
readFromSQLite,
NULL,
&perrMsg);

int  readFromSQLite(void *anyParam, int iColumn, char **pColumnValue, char **pColumnName) {
int icolumenCount = iColumn;
for (int i = 0; i < icolumenCount; ++i) {
CCLOG("%s: %s \n", pColumnName[i], pColumnValue[i]);
}
return 0;
}


//������
char * errMsg = NULL;//������Ϣ
int result;//sqlite3_exec����ֵ
char **dbResult; //�� char ** ���ͣ�����*��
int nRow, nColumn;
int result = sqlite3_get_table(pDB, "select * from pet", &dbResult, &nRow, &nColumn, &errMsg);
*/

/*
//ʹ�÷���
SqliteHelper helper;
helper.readRecord("select * from stages");
helper.insertRecordIntoSqlite("insert into MyGame3 values(123, \"aaa\", 26, \"man\")");
string sql = "create table if not exists MyGame3 (id int unsigned auto_increment primary key, name varchar(50), age int, sex varchar(10))";
helper.createTable(sql.c_str());
return;
*/