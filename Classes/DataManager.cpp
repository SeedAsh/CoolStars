#include "DataManager.h"

#define DB_NAME "coolstar.db"
#define DB_FILE_PATH "data/coolstar.db"

DataManager* DataManager::m_pSelf = NULL;

DataManager::DataManager(void)
{

}

DataManager::~DataManager(void)
{
	CC_SAFE_DELETE(m_pSelf);
}

void DataManager::UnzipGameData(bool update)
{
	string path = CCFileUtils::sharedFileUtils()->getWritablePath() + DB_NAME;

	if (CCFileUtils::sharedFileUtils()->isFileExist(path.c_str()) && !update)
	{
		CCLOG("File %s is exist!", path.c_str());
	}
	else
	{
		unsigned long size = 0;
		unsigned char* data = CCFileUtils::sharedFileUtils()->getFileData(DB_FILE_PATH, "rb", &size);

		CCLOG("path is:%s, filis len is:%ld", path.c_str(), size);
		FILE *fp = fopen(path.c_str(), "wb");
	//	fwrite(data, sizeof(char), (_In_ size_t)size, fp); modify by Belion because there is no use and _In_ size_t not exit except win32
		fwrite(data,sizeof(char),size, fp);
		fclose(fp);
		delete[]data;
		data = NULL;
	}
}

void DataManager::LoadData()
{
	/*LoadAchieveData();
	LoadPetData();
	LoadShoptoolsData();
	LoadMoneyshopData();
	loadBallConfigDataEx();*/
	LoadPetlistData();
	loadStageConfigDataEx();
	/*LoadBallQueueDataEx();
	LoadStageViewToolsData();
	LoadLuckyConfigsData();
	loadGuideConfig();
	loadGameString();*/
}

void DataManager::LoadPetData()
{                  //宠物表
	sqlite3 *pDB = NULL;//数据库指针 
	char * errMsg = NULL;//错误信息 
	char **dbResult; //是 char ** 类型，两个*号
	std::string sqlstr;//SQL指令 
	int result;//sqlite3_exec返回值 
	int nRow, nColumn;
	int i, j;
	int index, index2;
	string pathKey;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	pathKey = DB_FILE_PATH;
#else
	pathKey = CCFileUtils::sharedFileUtils()->getWritablePath() + DB_NAME;
#endif


	result = sqlite3_open(pathKey.c_str(), &pDB);
	if (result != SQLITE_OK)
	{

	}

	result = sqlite3_get_table(pDB, "select * from pet", &dbResult, &nRow, &nColumn, &errMsg);
	if (SQLITE_OK == result)
	{
		index2 = index = nColumn; //前面说过 dbResult 前面第一行数据是字段名称，从 nColumn 索引开始才是真正的数据
		for (i = 0; i < nRow; i++)
		{
			for (j = 0; j < nColumn; j++)
			{
				++index; // dbResult 的字段值是连续的，从第0索引到第 nColumn - 1索引都是字段名称，从第 nColumn 索引开始，后面都是字段值，它把一个二维的表（传统的行列表示法）用一个扁平的形式来表示
			}

			PetData ed;

			ed.id = atoi(dbResult[index2]);
			index2++;
			ed.name = dbResult[index2];
			index2++;
			ed.png = dbResult[index2];
			index2++;
			ed.plist = dbResult[index2];
			index2++;
			ed.json = dbResult[index2];
			index2++;
			ed.toolid = atoi(dbResult[index2]);
			index2++;
			ed.paytype = atoi(dbResult[index2]);
			index2++;
			ed.cost = atoi(dbResult[index2]);
			index2++;
			ed.combo_num = atoi(dbResult[index2]);
			index2++;
			ed.probabilty = atoi(dbResult[index2]);
			index2++;
			ed.duration = atoi(dbResult[index2]);
			index2++;

			PetVec.push_back(ed);
		}
	}
	sqlite3_free_table(dbResult);
	sqlite3_close(pDB);
	sqlite3_free(errMsg);  
}

void DataManager::LoadAchieveData()
{                  //成就表
	sqlite3 *pDB = NULL;//数据库指针 
	char * errMsg = NULL;//错误信息 
	char **dbResult; //是 char ** 类型，两个*号
	std::string sqlstr;//SQL指令 
	int result;//sqlite3_exec返回值 
	int nRow, nColumn;
	int i, j;
	int index, index2;
	string pathKey;
	AchieveVec.clear();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	pathKey = DB_FILE_PATH;
#else
	pathKey = CCFileUtils::sharedFileUtils()->getWritablePath() + DB_NAME;
#endif

	result = sqlite3_open(pathKey.c_str(), &pDB);
	if (result != SQLITE_OK)
	{

	}
	//同种类型任务只能出现一个   //"select * from achieve limit 10"
	result = sqlite3_get_table(pDB, "select * from achieve where rowid In (select min(rowid) from (achieve) group by type);", &dbResult, &nRow, &nColumn, &errMsg);
	if (SQLITE_OK == result)
	{
		index2 = index = nColumn; //前面说过 dbResult 前面第一行数据是字段名称，从 nColumn 索引开始才是真正的数据
		for (i = 0; i < nRow; i++)
		{
			for (j = 0; j < nColumn; j++)
			{
				++index; // dbResult 的字段值是连续的，从第0索引到第 nColumn - 1索引都是字段名称，从第 nColumn 索引开始，后面都是字段值，它把一个二维的表（传统的行列表示法）用一个扁平的形式来表示
			}

			AchieveData ed;

			ed.id = atoi(dbResult[index2]);
			index2++;
			ed.type = atoi(dbResult[index2]);
			index2++;
			ed.desc = dbResult[index2];
			index2++;
			ed.param1 = atoi(dbResult[index2]);
			index2++;
			ed.param2 = atoi(dbResult[index2]);
			index2++;
			ed.money = atoi(dbResult[index2]);
			index2++;
			ed.line = atoi(dbResult[index2]);
			index2++;
			ed.hammer = atoi(dbResult[index2]);
			index2++;
			ed.bomb = atoi(dbResult[index2]);
			index2++;
			ed.brush = atoi(dbResult[index2]);
			index2++;
			ed.color = atoi(dbResult[index2]);
			index2++;
			ed.lightning = atoi(dbResult[index2]);
			index2++;
			ed.ironball = atoi(dbResult[index2]);
			index2++;
			ed.has = atoi(dbResult[index2]);
			index2++;

			AchieveVec.push_back(ed);
		}
	}
	sqlite3_free_table(dbResult);
	sqlite3_close(pDB);
	sqlite3_free(errMsg);  
}

void DataManager::updateAchieveData(int id, int count)
{
	sqlite3 *pDB = NULL;//数据库指针 
	std::string sqlstr;//SQL指令 
	int result;//sqlite3_exec返回值 
	string pathKey;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	pathKey = DB_FILE_PATH;
#else
	pathKey = CCFileUtils::sharedFileUtils()->getWritablePath() + DB_NAME;
#endif
	result = sqlite3_open(pathKey.c_str(), &pDB);
	if (result != SQLITE_OK)
	{

	}
	char str[10];
	char str1[10];
	sprintf(str1, "%d", count);
	sqlstr = "update achieve set has=has+? where id =? and has!=param2";
	sqlite3_stmt *statement;
	if (sqlite3_prepare_v2(pDB, sqlstr.c_str(), -1, &statement, NULL) == SQLITE_OK) {
		sqlite3_bind_text(statement, 1, str1, -1, NULL);
		sprintf(str, "%d", id);
		sqlite3_bind_text(statement, 2, str, -1, NULL);
		if (sqlite3_step(statement) != SQLITE_DONE) {
			CCLOG(false, "Upate Data failure.");
		}
	}
	sqlite3_finalize(statement);
	sqlite3_close(pDB);
}

void DataManager::deleteAchieveData(int id)
{
	sqlite3 *pDB = NULL;//数据库指针 
	std::string sqlstr;//SQL指令 
	int result;//sqlite3_exec返回值 
	string pathKey;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	pathKey = DB_FILE_PATH;
#else
	pathKey = CCFileUtils::sharedFileUtils()->getWritablePath() + DB_NAME;
#endif
	result = sqlite3_open(pathKey.c_str(), &pDB);
	if (result != SQLITE_OK)
	{

	}
	char str[10];
	sprintf(str, "%d", id);
	sqlstr = "delete from achieve where id=?";
	result = sqlite3_exec(pDB, sqlstr.c_str(), NULL, NULL, NULL);//1
	if (result != SQLITE_OK)
		CCLOG("delete data failed!");
	sqlite3_stmt *statement;
	if (sqlite3_prepare_v2(pDB, sqlstr.c_str(), -1, &statement, NULL) == SQLITE_OK) {
		sqlite3_bind_text(statement, 1, str, -1, NULL);
		if (sqlite3_step(statement) != SQLITE_DONE) {
			CCLOG(false, "Upate Data failure.");
		}
	}
	sqlite3_finalize(statement);
	sqlite3_close(pDB);
}

void DataManager::LoadShoptoolsData()
{                  //道具表
	sqlite3 *pDB = NULL;//数据库指针 
	char * errMsg = NULL;//错误信息 
	char **dbResult; //是 char ** 类型，两个*号
	std::string sqlstr;//SQL指令 
	int result;//sqlite3_exec返回值 
	int nRow, nColumn;
	int i, j;
	int index, index2;
	string pathKey;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	pathKey = DB_FILE_PATH;
#else
	pathKey = CCFileUtils::sharedFileUtils()->getWritablePath() + DB_NAME;
#endif

	result = sqlite3_open(pathKey.c_str(), &pDB);
	if (result != SQLITE_OK)
	{

	}

	result = sqlite3_get_table(pDB, "select * from shoptools", &dbResult, &nRow, &nColumn, &errMsg);
	if (SQLITE_OK == result)
	{
		index2 = index = nColumn; //前面说过 dbResult 前面第一行数据是字段名称，从 nColumn 索引开始才是真正的数据
		for (i = 0; i < nRow; i++)
		{
			for (j = 0; j < nColumn; j++)
			{
				++index; // dbResult 的字段值是连续的，从第0索引到第 nColumn - 1索引都是字段名称，从第 nColumn 索引开始，后面都是字段值，它把一个二维的表（传统的行列表示法）用一个扁平的形式来表示
			}

			ShoptoolsData ed;

			ed.id = atoi(dbResult[index2]);
			index2++;
			ed.name = dbResult[index2];
			index2++;
			ed.paytype = atoi(dbResult[index2]);
			index2++;
			ed.get = atoi(dbResult[index2]);
			index2++;
			ed.cost = atoi(dbResult[index2]);
			index2++;
			ed.desc = dbResult[index2];
			index2++;

			ShoptoolsVec.push_back(ed);
		}
	}
	sqlite3_free_table(dbResult);
	sqlite3_close(pDB);
	sqlite3_free(errMsg);  
}

void DataManager::LoadMoneyshopData()
{                  //金币表
	sqlite3 *pDB = NULL;//数据库指针 
	char * errMsg = NULL;//错误信息 
	char **dbResult; //是 char ** 类型，两个*号
	std::string sqlstr;//SQL指令 
	int result;//sqlite3_exec返回值 
	int nRow, nColumn;
	int i, j;
	int index, index2;
	string pathKey;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	pathKey = DB_FILE_PATH;
#else
	pathKey = CCFileUtils::sharedFileUtils()->getWritablePath() + DB_NAME;
#endif

	result = sqlite3_open(pathKey.c_str(), &pDB);
	if (result != SQLITE_OK)
	{

	}

	result = sqlite3_get_table(pDB, "select * from moneyshop", &dbResult, &nRow, &nColumn, &errMsg);
	if (SQLITE_OK == result)
	{
		index2 = index = nColumn; //前面说过 dbResult 前面第一行数据是字段名称，从 nColumn 索引开始才是真正的数据
		for (i = 0; i < nRow; i++)
		{
			for (j = 0; j < nColumn; j++)
			{
				++index; // dbResult 的字段值是连续的，从第0索引到第 nColumn - 1索引都是字段名称，从第 nColumn 索引开始，后面都是字段值，它把一个二维的表（传统的行列表示法）用一个扁平的形式来表示
			}

			MoneyshopData ed;

			ed.id = atoi(dbResult[index2]);
			index2++;
			ed.name = dbResult[index2];
			index2++;
			ed.get = atoi(dbResult[index2]);
			index2++;
			ed.present = atoi(dbResult[index2]);
			index2++;
			ed.cost = atoi(dbResult[index2]);
			index2++;
			ed.desc = dbResult[index2];
			index2++;

			MoneyshopVec.push_back(ed);
		}
	}
	sqlite3_free_table(dbResult);
	sqlite3_close(pDB);
	sqlite3_free(errMsg);  
}

void DataManager::LoadStageData(int num){             //关卡内容表
	
	sqlite3 *pDB = NULL;//数据库指针 
	char * errMsg = NULL;//错误信息 
	char **dbResult; //是 char ** 类型，两个*号
	std::string sqlstr;//SQL指令 
	int result;//sqlite3_exec返回值 
	int nRow, nColumn;
	int i;
	int index;
	string pathKey;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	pathKey = DB_FILE_PATH;
#else
	pathKey = CCFileUtils::sharedFileUtils()->getWritablePath() + DB_NAME;
#endif

	result = sqlite3_open(pathKey.c_str(), &pDB);
	if (result != SQLITE_OK){
		CCLOG("LoadStageData can not open the database");
		sqlite3_free_table(dbResult);
		sqlite3_close(pDB);
		return;
	}
	
	StageVec.clear();
	char temp[50];
	sprintf(temp, "select * from stage%d", num);
	result = sqlite3_get_table(pDB, temp, &dbResult, &nRow, &nColumn, &errMsg);
	if (result == SQLITE_OK){
		index = nColumn; //dbResult 前面第一行数据是字段名称，从 nColumn 索引开始才是真正的数据
		for (i = 0; i < nRow; i++){
			StageData ed;
			memset(ed.col, 0, sizeof(int)* COlUMNS_SIZE);
			for (int k = 0; k < nColumn && k < COlUMNS_SIZE; k++){
				ed.col[k] = dbResult[index] == NULL ? 0 : atoi(dbResult[index]);
				index++;
			}		
			StageVec.push_back(ed);
		}
	}
	sqlite3_free_table(dbResult);
	sqlite3_close(pDB);
	sqlite3_free(errMsg);  
}

void DataManager::LoadStageconfigData(){                  //关卡表
	sqlite3 *pDB = NULL;//数据库指针 
	char * errMsg = NULL;//错误信息 
	char **dbResult; //是 char ** 类型，两个*号
	std::string sqlstr;//SQL指令 
	int result;//sqlite3_exec返回值 
	int nRow, nColumn;
	int i, j;
	int index, index2;
	string pathKey;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	pathKey = DB_FILE_PATH;
#else
	pathKey = CCFileUtils::sharedFileUtils()->getWritablePath() + DB_NAME;
#endif

	result = sqlite3_open(pathKey.c_str(), &pDB);
	if (result != SQLITE_OK)
	{

	}

	result = sqlite3_get_table(pDB, "select * from stageconfig", &dbResult, &nRow, &nColumn, &errMsg);
	if (SQLITE_OK == result)
	{
		index2 = index = nColumn; //前面说过 dbResult 前面第一行数据是字段名称，从 nColumn 索引开始才是真正的数据
		for (i = 0; i < nRow; i++)
		{
			for (j = 0; j < nColumn; j++)
			{
				++index; // dbResult 的字段值是连续的，从第0索引到第 nColumn - 1索引都是字段名称，从第 nColumn 索引开始，后面都是字段值，它把一个二维的表（传统的行列表示法）用一个扁平的形式来表示
			}

			StageconfigData ed;

			ed.stage = atoi(dbResult[index2]);
			index2++;
			ed.game_mode = atoi(dbResult[index2]);
			index2++;
			ed.falldown_speed = atof(dbResult[index2]);
			index2++;
			ed.timer = atoi(dbResult[index2]);
			index2++;
			ed.score = atoi(dbResult[index2]);
			index2++;
			ed.ball = atoi(dbResult[index2]);
			index2++;
			ed.award_coin = atoi(dbResult[index2]);
			index2++;

			StageconfigVec.push_back(ed);
		}
	}
	sqlite3_free_table(dbResult);
	sqlite3_close(pDB);
	sqlite3_free(errMsg);  
}

void DataManager::loadBallConfigDataEx()
{
	sqlite3 *pDB = NULL;//数据库指针 
	char * errMsg = NULL;//错误信息 
	char **dbResult; //是 char ** 类型，两个*号
	std::string sqlstr;//SQL指令 
	int result;//sqlite3_exec返回值 
	int nRow, nColumn;
	int i;
	int index;
	string pathKey;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	pathKey = DB_FILE_PATH;
#else
	pathKey = CCFileUtils::sharedFileUtils()->getWritablePath() + DB_NAME;
#endif

	result = sqlite3_open(pathKey.c_str(), &pDB);
	if (result != SQLITE_OK)
	{
		CCLOG("loadBallConfigDataEx can not open the database");
		sqlite3_free_table(dbResult);
		sqlite3_close(pDB);
		return;
	}

	result = sqlite3_get_table(pDB, "select * from balls", &dbResult, &nRow, &nColumn, &errMsg);
	if (SQLITE_OK == result){
		index = nColumn; //dbResult 前面第一行数据是字段名称，从 nColumn 索引开始才是真正的数据
		for (i = 0; i < nRow; i++){
			Ball ball;
			ball.id = atoi(dbResult[index++]);
			ball.ballType = atoi(dbResult[index++]);
			ball.score = atoi(dbResult[index++]);
			ball.extra = atoi(dbResult[index++]);
			ball.reward = atoi(dbResult[index++]);
			ball.content = atoi(dbResult[index++]);
			ball.state = BALL_STATE_DEFAULT;
			BallsVec.push_back(ball);
		}
	}
	sqlite3_free_table(dbResult);
	sqlite3_close(pDB);
	sqlite3_free(errMsg);  
}

void DataManager::loadStageConfigDataEx()
{
	sqlite3 *pDB = NULL;//数据库指针 
	char * errMsg = NULL;//错误信息 
	char **dbResult; //是 char ** 类型，两个*号
	std::string sqlstr;//SQL指令 
	int result;//sqlite3_exec返回值 
	int nRow, nColumn;
	int i;
	int index;
	string pathKey;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	pathKey = DB_FILE_PATH;
#else
	pathKey = CCFileUtils::sharedFileUtils()->getWritablePath() + DB_NAME;
#endif

	result = sqlite3_open(pathKey.c_str(), &pDB);
	if (result != SQLITE_OK)
	{
		CCLOG("loadBallConfigDataEx can not open the database");
		sqlite3_free_table(dbResult);
		sqlite3_close(pDB);
		return;
	}

	result = sqlite3_get_table(pDB, "select * from stages", &dbResult, &nRow, &nColumn, &errMsg);
	if (SQLITE_OK == result)
	{
		index = nColumn; //dbResult 前面第一行数据是字段名称，从 nColumn 索引开始才是真正的数据
		for (i = 0; i < nRow; i++)
		{
			StageInfo stage;
			memset(&stage,0,sizeof(StageInfo));

			stage.stageId = atoi(dbResult[index++]);
			stage.stageType = atoi(dbResult[index++]);

			char tmp[128];
			char* p;			
			char*  tmpStr = dbResult[index++];
			if (tmpStr != NULL)
			{
				memset(tmp, 0, sizeof(char)* 128);
				sprintf(tmp, "%s", tmpStr);
				p = strtok(tmp, ",");
				int j = 0;
				stage.params[j++] = atoi(p);
				while (p && j < 3)
				{
					p = strtok(NULL, ",");
					if (p)
					{
						stage.params[j++] = atoi(p);
					}
				}
			}
			stage.step = atoi(dbResult[index++]);
			stage.petId = atoi(dbResult[index++]);
			stage.extraReward = atoi(dbResult[index++]);

			tmpStr = dbResult[index++];
			if (tmpStr != NULL){
				memset(tmp ,0,sizeof(char) * 128);
				sprintf(tmp, "%s", tmpStr);
				p = strtok(tmp, ",");
				int j = 0;
				stage.content[j++] = atoi(p);
				while (p/* && j < 7*/){
					p = strtok(NULL, ",");
					if (p){
						stage.content[j++] = atoi(p);
					}
				}
			}

			tmpStr = dbResult[index++];
			if (tmpStr != NULL)
			{
				memset(tmp ,0,sizeof(char) * 128);
				sprintf(tmp, "%s", tmpStr);
				p = strtok(tmp, ",");
				int j = 0;
				stage.starPre[j++] = atoi(p);
				while (p && j < 2)
				{
					p = strtok(NULL, ",");
					if (p){
						stage.starPre[j++] = atoi(p);
					}
				}
			}
			else
			{
				stage.starPre[0] = 90;
				stage.starPre[1] = 60;
			}
			
			stage.starCount = atoi(dbResult[index++]);
			StagesVec.push_back(stage);
		}
	}
	sqlite3_free_table(dbResult);
	sqlite3_close(pDB);
	sqlite3_free(errMsg);  
}

void DataManager::LoadBallconfigData()
{                  //球属性表
	sqlite3 *pDB = NULL;//数据库指针 
	char * errMsg = NULL;//错误信息 
	char **dbResult; //是 char ** 类型，两个*号
	std::string sqlstr;//SQL指令 
	int result;//sqlite3_exec返回值 
	int nRow, nColumn;
	int i, j;
	int index, index2;
	string pathKey;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	pathKey = DB_FILE_PATH;
#else
	pathKey = CCFileUtils::sharedFileUtils()->getWritablePath() + DB_NAME;
#endif

	result = sqlite3_open(pathKey.c_str(), &pDB);
	if (result != SQLITE_OK)
	{

	}

	result = sqlite3_get_table(pDB, "select * from ball_config", &dbResult, &nRow, &nColumn, &errMsg);
	if (SQLITE_OK == result)
	{
		index2 = index = nColumn; //前面说过 dbResult 前面第一行数据是字段名称，从 nColumn 索引开始才是真正的数据
		for (i = 0; i < nRow; i++)
		{
			for (j = 0; j < nColumn; j++)
			{
				++index; // dbResult 的字段值是连续的，从第0索引到第 nColumn - 1索引都是字段名称，从第 nColumn 索引开始，后面都是字段值，它把一个二维的表（传统的行列表示法）用一个扁平的形式来表示
			}

			BallconfigData ed;
			
			ed.index = atoi(dbResult[index2]);
			index2++;
			
			ed.ball_num = atoi(dbResult[index2]);
			index2++;
			
			index2++;
			
			ed.appear = atoi(dbResult[index2]);
			index2++;

			ed.h_timer = atoi(dbResult[index2]);
			index2++;

			ed.ishave_yang = atoi(dbResult[index2]);
			index2++;
			
			BallconfigVec.push_back(ed);
		}
	}
	sqlite3_free_table(dbResult);
	sqlite3_close(pDB);
	sqlite3_free(errMsg);  
}

void DataManager::LoadBallQueueDataEx(){
	sqlite3 *pDB = NULL;//数据库指针 
	char * errMsg = NULL;//错误信息 
	char **dbResult; //是 char ** 类型，两个*号
	std::string sqlstr;//SQL指令 
	int result;//sqlite3_exec返回值 
	int nRow, nColumn;
	int index;
	string pathKey;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	pathKey = DB_FILE_PATH;
#else
	pathKey = CCFileUtils::sharedFileUtils()->getWritablePath() + DB_NAME;
#endif

	result = sqlite3_open(pathKey.c_str(), &pDB);
	if (result != SQLITE_OK){
		CCLOG("LoadBallQueueDataEx can not open the database");
		sqlite3_free_table(dbResult);
		sqlite3_close(pDB);
		return;
	}
	BallsQueueVec.clear();
	result = sqlite3_get_table(pDB, "select * from ball_queue", &dbResult, &nRow, &nColumn, &errMsg);
	if (result == SQLITE_OK){
		index =  nColumn; //dbResult 前面第一行数据是字段名称，从 nColumn 索引开始才是真正的数据
		for (int i = 0; i < nRow; i++){
			BallQueue ed;
			char tmp[256];
			int flag = 0;
			char* p;

			ed.queueId = atoi(dbResult[index]);
			index++;
			memset(tmp, 0, 256);
			memset(ed.bqueue, -1, BALL_QUEUE_SIZE * sizeof(int));
			sprintf(tmp, "%s", dbResult[index]);
			p = strtok(tmp, ",");
			ed.bqueue[flag] = atoi(p);
			flag++;
			while (p){
				p = strtok(NULL, ",");
				if (p){
					ed.bqueue[flag] = atoi(p);
					flag++;
				}
			}
			index++;
			BallsQueueVec.push_back(ed);
		}
	}
	sqlite3_free_table(dbResult);
	sqlite3_close(pDB);
	sqlite3_free(errMsg);  
}

void DataManager::LoadBallqueueData(){                  //球属性表
	sqlite3 *pDB = NULL;//数据库指针 
	char * errMsg = NULL;//错误信息 
	char **dbResult; //是 char ** 类型，两个*号
	std::string sqlstr;//SQL指令 
	int result;//sqlite3_exec返回值 
	int nRow, nColumn;
	int i, j;
	int index, index2;
	string pathKey;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	pathKey = DB_FILE_PATH;
#else
	pathKey = CCFileUtils::sharedFileUtils()->getWritablePath() + DB_NAME;
#endif

	result = sqlite3_open(pathKey.c_str(), &pDB);
	if (result != SQLITE_OK)
	{

	}

	result = sqlite3_get_table(pDB, "select * from ball_queue", &dbResult, &nRow, &nColumn, &errMsg);
	if (SQLITE_OK == result)
	{
		index2 = index = nColumn; //前面说过 dbResult 前面第一行数据是字段名称，从 nColumn 索引开始才是真正的数据
		for (i = 0; i < nRow; i++)
		{
			for (j = 0; j < nColumn; j++)
			{
				++index; // dbResult 的字段值是连续的，从第0索引到第 nColumn - 1索引都是字段名称，从第 nColumn 索引开始，后面都是字段值，它把一个二维的表（传统的行列表示法）用一个扁平的形式来表示
			}

			BallqueueData ed;

			char tmp[256];
			int flag = 0;
			char* p;

			ed.stage = atoi(dbResult[index2]);
			index2++;
			//1
			memset(tmp, 0, 256);
			memset(ed.bqueue, -1, 100 * sizeof(int));
			sprintf(tmp, "%s", dbResult[index2]);
			p = strtok(tmp, ",");
			ed.bqueue[flag] = atoi(p);
			flag++;
			while (p)
			{
				p = strtok(NULL, ",");
				if (p)
				{
					ed.bqueue[flag] = atoi(p);
					flag++;
					
				}
			}
			flag = 0;
			index2++;
			
			BallqueueVec.push_back(ed);
		}
	}
	sqlite3_free_table(dbResult);
	sqlite3_close(pDB);
	sqlite3_free(errMsg);  
}

void DataManager::LoadPetlistData()
{
	sqlite3 *pDB = NULL;//数据库指针 
	char * errMsg = NULL;//错误信息 
	char **dbResult; //是 char ** 类型，两个*号
	std::string sqlstr;//SQL指令 
	int result;//sqlite3_exec返回值 
	int nRow, nColumn;
	int i, j;
	int index2;
	string pathKey;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	pathKey = DB_FILE_PATH;
#else
	pathKey = CCFileUtils::sharedFileUtils()->getWritablePath() + DB_NAME;
#endif

	result = sqlite3_open(pathKey.c_str(), &pDB);
	if (result != SQLITE_OK)
	{
		CCLOG("LoadBOSSlistData sqlite3_open Error! result = %d",result);
	}

	result = sqlite3_get_table(pDB, "select * from pets", &dbResult, &nRow, &nColumn, &errMsg);
	if (SQLITE_OK == result)
	{
		index2 = nColumn; //前面说过 dbResult 前面第一行数据是字段名称，从 nColumn 索引开始才是真正的数据
		for (i = 0; i < nRow; i++)
		{
			PetConfig ed;
			char tmp[256];
			int flag = 0;
			char* p;

			ed.id = atoi(dbResult[index2]);
			index2++;
			//energy
			memset(tmp, 0, 256);
			memset(ed.energy, -1, 5 * sizeof(int));
			sprintf(tmp, "%s", dbResult[index2]);
			p = strtok(tmp, ",");
			ed.energy[flag] = atoi(p);
			flag++;
			while (p)
			{
				p = strtok(NULL, ",");
				if (p)
				{
					ed.energy[flag] = atoi(p);
					flag++;
				}
			}
			flag = 0;
			index2++;			
			//count
			memset(ed.count, -1, 5 * sizeof(int));
			sprintf(tmp, "%s", dbResult[index2]);
			p = strtok(tmp, ",");
			ed.count[flag] = atoi(p);
			flag++;
			while (p)
			{
				p = strtok(NULL, ",");
				if (p)
				{
					ed.count[flag] = atoi(p);
					flag++;
				}
			}
			flag = 0;
			index2++;
			//upgrade
			memset(ed.upgrade, -1, 5 * sizeof(int));
			sprintf(tmp, "%s", dbResult[index2]);
			p = strtok(tmp, ",");
			ed.upgrade[flag] = atoi(p);
			flag++;
			while (p)
			{
				p = strtok(NULL, ",");
				if (p)
				{
					ed.upgrade[flag] = atoi(p);
					flag++;
				}
			}
			flag = 0;
			index2++;
			CCLOG("desc==========================================%s", dbResult[index2]);
			index2++;

			PetListVec.push_back(ed);
		}
	}
	sqlite3_free_table(dbResult);
	sqlite3_close(pDB);
	sqlite3_free(errMsg);  
}

void DataManager::setStateStarCount(int stageIndex,int starCount)
{
	sqlite3 *pDB = NULL;//数据库指针 
	char *errMsg = NULL;//错误信息 
	int result;//sqlite3_exec返回值 
	string pathKey;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	pathKey = DB_FILE_PATH;
#else
	pathKey = CCFileUtils::sharedFileUtils()->getWritablePath() + DB_NAME;
#endif
	//const char* sqlstr = CCString::createWithFormat("UPDATE stages set starCount = '%d',bossId = '300' where stageId = '%d';",starCount,stageIndex)->getCString();//SQL指令 
	const char* sqlstr = CCString::createWithFormat("UPDATE stages set starCount = '%d' where stageId = '%d';",starCount,stageIndex)->getCString();//SQL指令 
	result = sqlite3_open(pathKey.c_str(), &pDB);
	if (result != SQLITE_OK)
	{
		CCLOG("setStateStarCount error ,sqlite3_open error! result = %d",result);
		sqlite3_close(pDB);
		return;
	}

	result = sqlite3_exec(pDB, sqlstr,NULL,NULL,&errMsg);

	if (result != SQLITE_OK)
	{
		CCLOG("setStateStarCount error ,sqlite3_exec error! stageIndex = %d, starCount = %d, errMsg = %s",stageIndex,starCount,errMsg);
	}
	
	sqlite3_close(pDB);
	sqlite3_free(errMsg);  
}

void DataManager::LoadStageViewToolsData()
{
	sqlite3 *pDB = NULL;//数据库指针 
	char * errMsg = NULL;//错误信息 
	char **dbResult; //是 char ** 类型，两个*号
	std::string sqlstr;//SQL指令 
	int result;//sqlite3_exec返回值 
	int nRow, nColumn;
	int i, j;
	int index, index2;
	string pathKey;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	pathKey = DB_FILE_PATH;
#else
	pathKey = CCFileUtils::sharedFileUtils()->getWritablePath() + DB_NAME;
#endif

	result = sqlite3_open(pathKey.c_str(), &pDB);
	if (result != SQLITE_OK)
	{

	}

	result = sqlite3_get_table(pDB, "select * from startviewtools", &dbResult, &nRow, &nColumn, &errMsg);
	if (SQLITE_OK == result)
	{
		index2 = index = nColumn; //前面说过 dbResult 前面第一行数据是字段名称，从 nColumn 索引开始才是真正的数据
		for (i = 0; i < nRow; i++)
		{
			for (j = 0; j < nColumn; j++)
			{
				++index; // dbResult 的字段值是连续的，从第0索引到第 nColumn - 1索引都是字段名称，从第 nColumn 索引开始，后面都是字段值，它把一个二维的表（传统的行列表示法）用一个扁平的形式来表示
			}

			StartViewTools ed;

			char tmp[20];
			int flag = 0;
			char* p;

			ed.stage = atoi(dbResult[index2]);
			index2++;
			//1
			memset(tmp, 0, 20);
			memset(ed.tools, -1, 4 * sizeof(int));
			sprintf(tmp, "%s", dbResult[index2]);
			p = strtok(tmp, ",");
			ed.tools[flag] = atoi(p);
			flag++;
			while (p)
			{
				p = strtok(NULL, ",");
				if (p)
				{
					ed.tools[flag] = atoi(p);
					flag++;

				}
			}
			flag = 0;
			index2++;

			StartToolsVec.push_back(ed);
		}
	}
	sqlite3_free_table(dbResult);
	sqlite3_close(pDB);
	sqlite3_free(errMsg);
}

void DataManager::LoadLuckyConfigsData(){                  //转盘配置信息加载
	sqlite3 *pDB = NULL;//数据库指针 
	char * errMsg = NULL;//错误信息 
	char **dbResult; //是 char ** 类型，两个*号
	std::string sqlstr;//SQL指令 
	int result;//sqlite3_exec返回值 
	int nRow, nColumn;
	int i, j;
	int index;
	string pathKey;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	pathKey = DB_FILE_PATH;
#else
	pathKey = CCFileUtils::sharedFileUtils()->getWritablePath() + DB_NAME;
#endif

	result = sqlite3_open(pathKey.c_str(), &pDB);
	if (result != SQLITE_OK)
	{

	}

	result = sqlite3_get_table(pDB, "select * from lucky_config", &dbResult, &nRow, &nColumn, &errMsg);
	if (SQLITE_OK == result)
	{
		index = nColumn; 
		for (i = 0; i < nRow; i++)
		{
			LuckyConfigs lc;
			char tmp[256];
			char* p;

			lc.id = atoi(dbResult[index]);
			index++;
			lc.A = atoi(dbResult[index]);
			index++;
			lc.B = atoi(dbResult[index]);
			index++;
			lc.X = atoi(dbResult[index]);
			index++;
			memset(tmp, 0, 256);
			//hint
			//memset(lc.hint, -1, 20 * sizeof(int));
			sprintf(tmp, "%s", dbResult[index]);
			p = strtok(tmp, ",");
			lc.hint[0] = atoi(p);
			p = strtok(NULL, ",");
			lc.hint[1] = atoi(p);
			index++;
			//hammer
			//memset(lc.hammer, -1, 20 * sizeof(int));
			sprintf(tmp, "%s", dbResult[index]);
			p = strtok(tmp, ",");
			lc.hammer[0] = atoi(p);
			p = strtok(NULL, ",");
			lc.hammer[1] = atoi(p);
			index++;
			//bomb
			//memset(lc.bomb, -1, 20 * sizeof(int));
			sprintf(tmp, "%s", dbResult[index]);
			p = strtok(tmp, ",");
			lc.bomb[0] = atoi(p);
			p = strtok(NULL, ",");
			lc.bomb[1] = atoi(p);
			index++;
			//brush
			//memset(lc.brush, -1, 20 * sizeof(int));
			sprintf(tmp, "%s", dbResult[index]);
			p = strtok(tmp, ",");
			lc.brush[0] = atoi(p);
			p = strtok(NULL, ",");
			lc.brush[1] = atoi(p);
			index++;
			//anycolor
			//memset(lc.anycolor, -1, 20 * sizeof(int));
			sprintf(tmp, "%s", dbResult[index]);
			p = strtok(tmp, ",");
			lc.anycolor[0] = atoi(p);
			p = strtok(NULL, ",");
			lc.anycolor[1] = atoi(p);
			index++;
			//removecolor
			//memset(lc.removecolor, -1, 20 * sizeof(int));
			sprintf(tmp, "%s", dbResult[index]);
			p = strtok(tmp, ",");
			lc.removecolor[0] = atoi(p);
			p = strtok(NULL, ",");
			lc.removecolor[1] = atoi(p);
			index++;
			//steel
			//memset(lc.steel, -1, 20 * sizeof(int));
			sprintf(tmp, "%s", dbResult[index]);
			p = strtok(tmp, ",");
			lc.steel[0] = atoi(p);
			p = strtok(NULL, ",");
			lc.steel[1] = atoi(p);
			index++;
			//moneysmall
			//memset(lc.moneysmall, -1, 20 * sizeof(int));
			sprintf(tmp, "%s", dbResult[index]);
			p = strtok(tmp, ",");
			lc.moneysmall[0] = atoi(p);
			p = strtok(NULL, ",");
			lc.moneysmall[1] = atoi(p);
			index++;
			//moneybig
			//memset(lc.moneybig, -1, 20 * sizeof(int));
			sprintf(tmp, "%s", dbResult[index]);
			p = strtok(tmp, ",");
			lc.moneybig[0] = atoi(p);
			p = strtok(NULL, ",");
			lc.moneybig[1] = atoi(p);
			index++;

			LuckyConfigsVec.push_back(lc);
		}
	}
	sqlite3_free_table(dbResult);
	sqlite3_close(pDB);
	sqlite3_free(errMsg);
}

void DataManager::loadGuideConfig()
{
	sqlite3 *pDB = NULL;//数据库指针 
	char * errMsg = NULL;//错误信息 
	char **dbResult; //是 char ** 类型，两个*号
	std::string sqlstr;//SQL指令 
	int result;//sqlite3_exec返回值 
	int nRow, nColumn;
	int i;
	int index;
	string pathKey;
	char tmp[256];

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	pathKey = DB_FILE_PATH;
#else
	pathKey = CCFileUtils::sharedFileUtils()->getWritablePath() + DB_NAME;
#endif

	result = sqlite3_open(pathKey.c_str(), &pDB);
	if (result != SQLITE_OK)
	{
		CCLOG("loadBallConfigDataEx can not open the database");
		sqlite3_free_table(dbResult);
		sqlite3_close(pDB);
		return;
	}

	result = sqlite3_get_table(pDB, "select * from guide_config", &dbResult, &nRow, &nColumn, &errMsg);
	if (SQLITE_OK == result){
		index = nColumn; //dbResult 前面第一行数据是字段名称，从 nColumn 索引开始才是真正的数据
		for (i = 0; i < nRow; i++){
			GideConfig config;
			char* p;
			config.type = atoi(dbResult[index++]);
			config.level = atoi(dbResult[index++]);
			sprintf(tmp, "%s", dbResult[index++]);
			p = strtok(tmp, ",");
			if (p)
			{
				config.extral[0] = atoi(p);
			}
			else
			{
				config.extral[0] = 0;
			}
			p = strtok(NULL, ",");
			if (p)
			{
				config.extral[1] = atoi(p);
			}
			else
			{
				config.extral[1] = 0;
			}
			p = strtok(NULL, ",");
			if (p)
			{
				config.extral[2] = atoi(p);
			}
			else
			{
				config.extral[2] = 0;
			}
			index++;
			GuideConfigVec.push_back(config);
		}
	}
	sqlite3_free_table(dbResult);
	sqlite3_close(pDB);
	sqlite3_free(errMsg);
}

void DataManager::loadGameString()
{
	sqlite3 *pDB = NULL;//数据库指针 
	char * errMsg = NULL;//错误信息 
	char **dbResult; //是 char ** 类型，两个*号
	std::string sqlstr;//SQL指令 
	int result;//sqlite3_exec返回值 
	int nRow, nColumn;
	int i;
	int index;
	string pathKey;
	char tmp[256];

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	pathKey = DB_FILE_PATH;
#else
	pathKey = CCFileUtils::sharedFileUtils()->getWritablePath() + DB_NAME;
#endif

	result = sqlite3_open(pathKey.c_str(), &pDB);
	if (result != SQLITE_OK)
	{
		CCLOG("loadGameString can not open the database");
		sqlite3_free_table(dbResult);
		sqlite3_close(pDB);
		return;
	}

	result = sqlite3_get_table(pDB, "select * from strings", &dbResult, &nRow, &nColumn, &errMsg);
	if (SQLITE_OK == result){
		index = nColumn; //dbResult 前面第一行数据是字段名称，从 nColumn 索引开始才是真正的数据
		for (i = 0; i < nRow; i++){
			GameString config;
			config.desc = dbResult[index++];
			GameStringVec.push_back(config);
		}
	}
	sqlite3_free_table(dbResult);
	sqlite3_close(pDB);
	sqlite3_free(errMsg);
}