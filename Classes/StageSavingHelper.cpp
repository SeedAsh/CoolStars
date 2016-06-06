#include "StageSavingHelper.h"
#include "ConfData.h"
#include "SqliteHelper.h"
#include "StarNode.h"
#include "StageModel.h"

USING_NS_CC;
using namespace std;
void StageSavingHelper::saveCurStars()
{
	auto stageModel = StageModel::theModel();

	char str[100] = { 0 };
	SqliteHelper helper(DB_SAVING);
	helper.clearTable("save_stars");
	string sql;
	for (int row = ROWS_SIZE - 1; row >= 0; --row)
	{
		vector<string> stars;
		sql.clear();
		sql = "insert into save_stars values("; //只有一条记录 id=1
		for (int col = 0; col < COlUMNS_SIZE; ++col)
		{
			LogicGrid grid(col, row);
			int star = kEmpty;
			auto node = stageModel->getStarNode(grid);
			if (node)
			{
				star = node->getAttr().type;
			}
			sprintf(str, "%d,", star);
			sql += str;
		}
		sql = sql.substr(0, sql.length() - 1); //去掉最后一个逗号
		sql += ");";
		helper.insertRecordIntoSqlite(sql.c_str());
	}
	helper.closeDB();
}

//出错则返回false，直接读新关卡数据
bool StageSavingHelper::getLastSavedStars(std::vector<std::vector<int>> &stars)
{
	SqliteHelper sqlHelper(DB_SAVING);
	auto result = sqlHelper.readRecord("select * from save_stars");

	assert(result.size() == ROWS_SIZE);
	if (result.size() != ROWS_SIZE) return false;


	for (auto iter = result.begin(); iter != result.end(); ++iter)
	{
		assert((*iter).size() == COlUMNS_SIZE);
		if ((*iter).size() != ROWS_SIZE) return false;

		vector<int> oneRow;
		for (size_t i = 0; i < (*iter).size(); ++i)
		{
			oneRow.push_back(atoi((*iter)[i]));
		}
		stars.push_back(oneRow);
	}
	return true;
}




void StageSavingHelper::saveCurStageData()
{
	//保存当前关卡id 分数 最高分
	auto stageModel = StageModel::theModel();
	string sql;
	char str[100] = { 0 };
	SqliteHelper helper(DB_SAVING);

	sql.clear();
	sql = "replace into save_curState values(1, ";
	
	int curStage = stageModel->getCurStage();
	int curScore = stageModel->getCurScore();
	int topScore = stageModel->getTopScore();
	sprintf(str, "%d,%d,%d);", curStage, curScore, topScore);
	
	helper.insertRecordIntoSqlite(sql.c_str());
	helper.closeDB();
}

void StageSavingHelper::LoadLastSavedStageData()
{
	auto stageModel = StageModel::theModel();

	char str[100] = { 0 };
	SqliteHelper helper(DB_SAVING);
	string sql = "select * from save_cur_stage";
	auto result = helper.readRecord(sql.c_str());
	assert(result.size() == 1);

	int curStage = atoi(result[0][0]);
	int curScore = atoi(result[0][1]);
	int topScore = atoi(result[0][2]);
	stageModel->setCurStage(curStage);
	stageModel->setCurScore(curScore);
	stageModel->setTopScore(topScore);
}

