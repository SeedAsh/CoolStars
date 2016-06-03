#include "StageModel.h"
#include "StarUtil.h"
#include "DataManager.h"
#include "SqliteHelper.h"
USING_NS_CC;
using namespace std;
StageModel::StageModel()
	: m_isNewStage(true)
	, m_highScore(0)
{
	resetStarsData();
}

StageModel::~StageModel()
{
}

StageModel *StageModel::theModel()
{
	static StageModel model;
	return &model;
}

int StageModel::getCurDirection()
{
	int index = 0;
	if (m_step > 0)
	{
		index = ((m_step - 1) % 12);
	}
	return m_currentStageInfo.content[index];
}

void StageModel::initStarsData()
{
	resetStarsData();
	m_target.initTargets();
	m_currentStageInfo = DataManagerSelf->StagesVec[m_curStage - 1];

	//关卡星星数据是一列列保存的，需要转换
	if (m_isNewStage)
	{
		//数据库
		DataManagerSelf->LoadStageData(m_curStage);

		for (int row = 0; row < ROWS_SIZE; ++row)
		{
			StageData stageStarRow = DataManagerSelf->StageVec[row];
			for (int col = 0; col < COlUMNS_SIZE; ++col)
			{
				StarAttr attr;
				attr.type = (stageStarRow.col[col] - 1) % 5 + 1;
				attr.grid = LogicGrid(col, ROWS_SIZE - row - 1);
				m_starNodes.push_back(StarNode::createNodeFatory(attr));
			}
		}
	}
	else 
	{
		//返回的数据是保存行的
		vector<vector<int>> StageVec;
		SavingHelper::theHelper()->getLastSavedStars(StageVec);

		for (int row = 0; row < ROWS_SIZE; ++row)
		{
			for (int col = 0; col < COlUMNS_SIZE; ++col)
			{
				StarAttr attr;
				attr.type = StageVec[col][row];
				attr.grid = LogicGrid(row, ROWS_SIZE - col - 1);
				m_starNodes.push_back(StarNode::createNodeFatory(attr));
			}
		}
	}
}

void StageModel::resetStarsData()
{
	//reset nodes
	for (auto iter = m_starNodes.begin(); iter != m_starNodes.end(); ++iter)
	{
		delete(*iter);
	}
	m_starNodes.clear();

	m_step = 0;
	m_curStage = DataManagerSelf->getCurState().curStage;
	m_curScore = 0;

	m_target.resetData();
}

StarNode *StageModel::getStarNode(const LogicGrid &grid)
{
	auto iter = find_if(m_starNodes.begin(), m_starNodes.end(), [=](StarNode *node)->bool
	{
		const LogicGrid temp = node->getAttr().grid;
		return grid == temp;
	});

	return iter != m_starNodes.end() ? *iter : NULL;
}

void StageModel::moveStars()
{
	sort(m_starNodes.begin(), m_starNodes.end(), [=](StarNode *node1, StarNode *node2)->bool
	{
		auto grid1 = node1->getAttr().grid;
		auto grid2 = node2->getAttr().grid;
		switch (getCurDirection())
		{
		case kMoveUp:
			return grid1.y > grid2.y;
		case kMoveDown:
			return grid1.y < grid2.y;
		case kMoveLeft :
			return grid1.x < grid2.x;
		case kMoveRight:
			return grid1.x > grid2.x;
		default:
			return false;
		}
	});
	for (auto iter = m_starNodes.begin(); iter != m_starNodes.end(); ++iter)
	{
		moveStar(*iter);
	}
}

bool StageModel::isGridEmpty(const LogicGrid &grid)
{
	auto iter = find_if(m_starNodes.begin(), m_starNodes.end(), [=](StarNode* node)->bool
	{
		return node->getAttr().grid == grid;
	});
	return iter == m_starNodes.end();
}

void StageModel::moveStar(StarNode *node)
{
    int direction = StageModel::theModel()->getCurDirection();
    auto curGrid = node->getAttr().grid;
    auto targetGrid = curGrid;
    switch (direction)
    {
        case kMoveUp :
            for (int i = curGrid.y + 1; i < ROWS_SIZE; ++i)
            {
				LogicGrid temp(curGrid.x, i);
				if (isGridEmpty(temp))
                {
                    targetGrid.y++;
                }
            }
            break;
        case kMoveDown:
            for (int i = 0; i < curGrid.y; ++i)
            {
				LogicGrid temp(curGrid.x, i);
				if (isGridEmpty(temp))
                {
                    targetGrid.y--;
                }
            }
            break;
        case kMoveLeft:
            for (int i = 0; i < curGrid.x; i++)
            {
				LogicGrid temp(i, curGrid.y);
				if (isGridEmpty(temp))
                {
                    targetGrid.x--;
                }
            }
            break;	
        case kMoveRight:
            for (int i = curGrid.x + 1; i < COlUMNS_SIZE; ++i)
            {
				LogicGrid temp(i, curGrid.y);
				if (isGridEmpty(temp))
                {
                    targetGrid.x++;
                    
                }
            }
            break;
    }
	if (targetGrid != node->getAttr().grid)
	{
		node->moveTo(targetGrid);
		node->setLogicGrid(targetGrid);
	}
}

void StageModel::removeStarNode(StarNode *node)
{
	auto iter = find(m_starNodes.begin(), m_starNodes.end(), node);
	if (iter != m_starNodes.end())
	{
		delete *iter;
		m_starNodes.erase(iter);
	}
}

void StageModel::genNewStars()
{
	//移动方向： 上下左右
	int moveDirection[4][2] = { { 0, 1 }, { 0, -1 }, { -1, 0 }, { 1, 0 } };
	int emptyGridX[COlUMNS_SIZE] = {0};	//值为x的一列上空格的个数
	int emptyGridY[ROWS_SIZE] = {0};		//值为y的一行上空格的个数
	for (int x = 0; x < COlUMNS_SIZE; ++x)
	{
		for (int y = 0; y < ROWS_SIZE; ++y)
		{

			auto iter = find_if(m_starNodes.begin(), m_starNodes.end(), [=](StarNode *node)->bool
			{
				auto grid = node->getAttr().grid;
				return  grid.x == x && grid.y == y;
			});

			if (iter == m_starNodes.end())
			{
				emptyGridX[x]++;
				emptyGridY[y]++;
			}
		}
	}

	int kExtraGridOffset = 2;
	vector<LogicGrid> newGrid;
	switch (getCurDirection())
	{
	case kMoveUp:
		for (int i = 0; i < COlUMNS_SIZE; ++i)
		{
			for (int j = 0; j < emptyGridX[i]; ++j)
			{
				LogicGrid grid(i, 0 - kExtraGridOffset + j);
				newGrid.push_back(grid);
			}
		}
		break;
	case kMoveDown:
		for (int i = 0; i < COlUMNS_SIZE; ++i)
		{
			for (int j = 0; j < emptyGridX[i]; ++j)
			{
				LogicGrid grid(i, ROWS_SIZE  - 1 + kExtraGridOffset - j);
				newGrid.push_back(grid);
			}
		}
		break;
	case kMoveLeft:
		for (int i = 0; i < ROWS_SIZE; ++i)
		{
			for (int j = 0; j < emptyGridY[i]; ++j)
			{
				LogicGrid grid(COlUMNS_SIZE - 1 + kExtraGridOffset - j ,i);
				newGrid.push_back(grid);
			}
		}
		break;
	case kMoveRight:
		for (int i = 0; i < ROWS_SIZE; ++i)
		{
			for (int j = 0; j < emptyGridY[i]; ++j)
			{
				LogicGrid grid(0 - kExtraGridOffset + j, i);
				newGrid.push_back(grid);
			}
		}
		break;
	default:
		break;
	}
	for (size_t i = 0; i < newGrid.size(); ++i)
	{
		//当前只测试 彩色星星 5种
		int startype = ((int)(CCRANDOM_0_1() * 100)) % 5 + 1;
		StarAttr attr;
		attr.grid = newGrid[i];
		attr.type = startype;
		StarNode *node = StarNode::createNodeFatory(attr);
		m_starNodes.push_back(node);
		NOTIFY_VIEWS(createNewStar, node);
	}
	moveStars();
}

void StageModel::addView(IStageView *view)
{
	auto iter = find(m_views.begin(), m_views.end(), view);
	if (iter == m_views.end())
	{
		m_views.push_back(view);
	}
}

void StageModel::removeView(IStageView *view)
{
	auto iter = find(m_views.begin(), m_views.end(), view);
	if (iter != m_views.end())
	{
		m_views.erase(iter);
	}
}

void StageModel::moveOneStep()
{
	m_step++;
	NOTIFY_VIEWS(stepsChanged);
}

void StageModel::doSave()
{
	char str[100] = { 0 };
	SqliteHelper helper(DB_SAVING);
	string sql;
	helper.clearTable("save_stars");
	for (int row = ROWS_SIZE - 1; row >= 0; --row)
	{
		vector<string> stars;
		sql.clear();
		sql = "insert into save_stars values(";
		for (int col = 0; col < COlUMNS_SIZE; ++col)
		{
			LogicGrid grid(col, row);
			int star = kEmpty;
			auto node = getStarNode(grid);
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


	//保存当前关卡id 分数 最高分
	helper.clearTable("save_curState");
	sql.clear();
	sql = "insert into save_curState values(";
	sprintf(str, "%d,", m_curStage);
	sql += str;
	sprintf(str, "%d,", m_curScore);
	sql += str;
	sprintf(str, "%d", m_highScore);
	sql += str;
	sql += ",\"1,6,12\");";
	helper.insertRecordIntoSqlite(sql.c_str());

	helper.closeDB();

}

void StageModel::replaceStar(const StarAttr &attr)
{
	auto grid = attr.grid;
	StarNode *node = getStarNode(grid);
	if (!node) return;

	node->removeSelf();
	m_starNodes.push_back(StarNode::createNodeFatory(attr));
	NOTIFY_VIEWS(createNewStar, node);
}