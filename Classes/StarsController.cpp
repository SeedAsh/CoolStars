#include "StarsController.h"
#include "DataManager.h"
#include "SqliteHelper.h"
#include "StageSavingHelper.h"
#include "CommonMacros.h"
#include "StageDataMgr.h"

USING_NS_CC;
using namespace std;
StarsController::StarsController()
{

}

StarsController::~StarsController()
{
}

StarsController *StarsController::theModel()
{
	static StarsController model;
	return &model;
}


void StarsController::initStarsData()
{
	//���ص������Ǳ����е�
	vector<vector<StageStarInfo>> stageVec;
	
	StageDataMgr::theMgr()->getStageStars(stageVec);
	
	for (int row = 0; row < ROWS_SIZE; ++row)
	{
		for (int col = 0; col < COlUMNS_SIZE; ++col)
		{
			StarAttr attr;
			attr.type = stageVec[col][row].starType;
			attr.color = stageVec[col][row].color;
			attr.grid = LogicGrid(row, ROWS_SIZE - col - 1);
			m_starNodes.push_back(StarNode::createNodeFatory(attr));
		}
	}

	m_starsBehavior.onOneRoundBegin();
	StageDataMgr::theMgr()->doSave();
}

void StarsController::resetStage(int gameType)
{
	//reset nodes
	for (auto iter = m_starNodes.begin(); iter != m_starNodes.end(); ++iter)
	{
		delete(*iter);
	}
	StageDataMgr::theMgr()->reset(gameType);
	m_starNodes.clear();
	m_target.init();
	m_starsLoader.init();
}

StarNode *StarsController::getStarNode(const LogicGrid &grid)
{
	auto iter = find_if(m_starNodes.begin(), m_starNodes.end(), [=](StarNode *node)->bool
	{
		const LogicGrid temp = node->getAttr().grid;
		return grid == temp;
	});

	return iter != m_starNodes.end() ? *iter : NULL;
}

void StarsController::moveStars()
{
	sort(m_starNodes.begin(), m_starNodes.end(), [=](StarNode *node1, StarNode *node2)->bool
	{
		auto grid1 = node1->getAttr().grid;
		auto grid2 = node2->getAttr().grid;
		switch (StageDataMgr::theMgr()->getCurDirection())
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

bool StarsController::isGridEmpty(const LogicGrid &grid)
{
	auto iter = find_if(m_starNodes.begin(), m_starNodes.end(), [=](StarNode* node)->bool
	{
		return node->getAttr().grid == grid;
	});
	return iter == m_starNodes.end();
}

void StarsController::moveStar(StarNode *node)
{
	int direction = StageDataMgr::theMgr()->getCurDirection();
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

void StarsController::removeStarNode(StarNode *node)
{
	auto iter = find(m_starNodes.begin(), m_starNodes.end(), node);
	if (iter != m_starNodes.end())
	{
		auto attr = (*iter)->getAttr();
		m_target.starErased(attr.type, attr.color);

		delete *iter;
		m_starNodes.erase(iter);

	}
}

void StarsController::gameOver(bool isWon)
{
	StageSavingHelper::saveCurStageData();
	NOTIFY_VIEWS(onGameOver, isWon);
}

void StarsController::genNewStars()
{
	//�ƶ����� ��������
	int moveDirection[4][2] = { { 0, 1 }, { 0, -1 }, { -1, 0 }, { 1, 0 } };
	int emptyGridX[COlUMNS_SIZE] = {0};	//ֵΪx��һ���Ͽո�ĸ���
	int emptyGridY[ROWS_SIZE] = {0};		//ֵΪy��һ���Ͽո�ĸ���
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

	int kExtraGridOffset = max(COlUMNS_SIZE, ROWS_SIZE);//�´��������ǳ�ʼ ���ķ�����kExtraGridOffset���ĵط�
	vector<LogicGrid> newGrid;
	switch (StageDataMgr::theMgr()->getCurDirection())
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
		auto attr = m_starsLoader.genNewStars(newGrid[i]);
		StarNode *node = StarNode::createNodeFatory(attr);
		m_starNodes.push_back(node);
		NOTIFY_VIEWS(onCreateNewStar, node);
	}
	moveStars();
}

void StarsController::addView(IStarsControlView *view)
{
	auto iter = find(m_views.begin(), m_views.end(), view);
	if (iter == m_views.end())
	{
		m_views.push_back(view);
	}
}

void StarsController::removeView(IStarsControlView *view)
{
	auto iter = find(m_views.begin(), m_views.end(), view);
	if (iter != m_views.end())
	{
		m_views.erase(iter);
	}
}

void StarsController::moveOneStep()
{
	StageDataMgr::theMgr()->addStep();

	if (m_target.isGameOver())
	{
		bool isWon = false;
		if (m_target.isReachTarget())
		{
			isWon = true;
		}
		gameOver(isWon);
	}
}

//����ƶ�һ�����»غϿ�ʼ
void StarsController::onOneRoundBegan()
{
	m_starsBehavior.onOneRoundBegin();
}

void StarsController::onOneRoundEnd()
{
	m_starsBehavior.onOneRoundEnd();
}

void StarsController::addScore(int value)
{
	StageDataMgr::theMgr()->addCurScore(value);
}

void StarsController::replaceStar(const StarAttr &attr)
{
	auto grid = attr.grid;
	StarNode *node = getStarNode(grid);
	if (!node) return;

	node->doRemove(false);
	genStar(attr);
}

void StarsController::genStar(const StarAttr &attr)
{
	auto node = StarNode::createNodeFatory(attr);
	m_starNodes.push_back(node);
	NOTIFY_VIEWS(onCreateNewStar, node);
}

int StarsController::getStageAmount()
{
	return DataManagerSelf->getSystemConfig().stageAmount;
}

void StarsController::highLightStars(int color)
{
	NOTIFY_VIEWS(onHighLightStars, color);
}

void StarsController::toNormalState()
{
	NOTIFY_VIEWS(onToNormalState);
}