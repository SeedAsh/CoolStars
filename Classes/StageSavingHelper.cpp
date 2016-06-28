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
	
	helper.openTransaction(true);
	for (int row = ROWS_SIZE - 1; row >= 0; --row)
	{
		vector<string> stars;
		sql.clear();
		sql = "insert into save_stars values("; //ֻ��һ����¼ id=1
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
		sql = sql.substr(0, sql.length() - 1); //ȥ�����һ������
		sql += ");";
		helper.executeSql(sql.c_str());
	}
	helper.openTransaction(false);
	helper.closeDB();
}

//�����򷵻�false��ֱ�Ӷ��¹ؿ�����
bool StageSavingHelper::getLastSavedStars(std::vector<std::vector<int>> &stars)
{
	SqliteHelper sqlHelper(DB_SAVING);
	
	auto temp = stars;
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
		temp.push_back(oneRow);
	}
	stars = temp;
	return true;
}




void StageSavingHelper::saveCurStageData()
{
	//���浱ǰ�ؿ�id ���� ��߷�
	auto stageModel = StageModel::theModel();
	string sql;
	char str[100] = { 0 };
	SqliteHelper helper(DB_SAVING);

	auto stageInfo = stageModel->getStageInfo();
	int curStage = stageInfo->getCurStage();
	int topScore = stageInfo->getTopScore();
	sprintf(str, "replace into save_cur_stage values(1, %d,%d);"
		, curStage, topScore);
	
	helper.executeSql(str);
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

	int curStage = atoi(result[0][1]);
	int topScore = atoi(result[0][2]);

	auto stageInfo = stageModel->getStageInfo();
	stageInfo->setTopStage(curStage);
	stageInfo->setTopScore(topScore);
}

