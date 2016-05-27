#include "StarsLayer.h"
#include "StarUtil.h"
#include "StarNode.h"
#include "StageModel.h"

using namespace cocos2d;
using namespace std;
StarsLayer::StarsLayer()
:m_starsSprite(NULL)
{

}

StarsLayer::~StarsLayer()
{
}

bool StarsLayer::init()
{
	m_pStarUtil = new StarUtil();
	m_pStarUtil->initStarEx();
	showStars();
	return true;
}

CCNode *StarsLayer::createStar(int starType, LogicGrid grid)
{
	StarNode *node = StarNode::create(starType, grid);
	m_starsSprite.push_back(node);
	return node;
}

void StarsLayer::showStars()
{
	//m_pStarUtil->star[][] 中是一列列保存的
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCNode *pStarSprite = NULL;
	Star *pStar = NULL;
	float speed = visibleSize.height / 0.9f;
	for (int col = 0; col < COlUMNS_SIZE; ++col)
	{
		for (int row = 0; row < ROWS_SIZE; ++row) 
		{
			LogicGrid grid(col, ROWS_SIZE - row - 1);
			pStar = &m_pStarUtil->star[col][row];

			pStarSprite = createStar(pStar->color, grid);
			pStarSprite->setAnchorPoint(ccp(0.5f, 0.5f));
			CCPoint targetPos = getPosByGrid(grid);
			CCPoint sourcePos = targetPos;
			//实现梅花间隔掉落
			sourcePos.y = targetPos.y + visibleSize.height + grid.y * STAR_SIZE + (grid.x % 2) * STAR_SIZE;

			pStarSprite->setPosition(sourcePos);
			float duration = (sourcePos.y - targetPos.y) / speed;
			CCMoveTo* move = CCMoveTo::create(duration, targetPos);

			addChild(pStarSprite);
			pStarSprite->runAction(move);
		}
	}
	runAction(CCCallFunc::create(this, callfunc_selector(StarsLayer::starInitDone)));
}

void StarsLayer::starInitDone()
{
	setTouchEnabled(true);
}

StarNode *StarsLayer::getClickedStar(CCPoint pos)
{
	for (size_t i = 0; i < m_starsSprite.size(); ++i)
	{
		StarNode *star = m_starsSprite[i];
		if (star->boundingBox().containsPoint(pos))
		{
			return star;
		}
	}

	return NULL;
}

void StarsLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCPoint touchLocation = (((CCTouch*)(*(pTouches->begin())))->getLocation());
	StarNode *star = getClickedStar(touchLocation);
	if (star == NULL) return;
	
	star->doExplodeAction();
//	genNewStars();
	moveStars();
}

//左下第一个grid为（0，0）
CCPoint StarsLayer::getPosByGrid(LogicGrid grid)
{
	CCPoint pos;
	pos.x = STAR_SIZE * (grid.x + 0.5f);
	pos.y = STAR_SIZE * (grid.y + 0.5f);
	return pos;
}

StarNode *StarsLayer::getStarByGrid(LogicGrid grid)
{
	if (grid.x < 0 || grid.x >= COlUMNS_SIZE || grid.y < 0 || grid.y >= ROWS_SIZE)
		return NULL;

	for (size_t i = 0; i < m_starsSprite.size(); ++i)
	{
		auto temp = m_starsSprite[i]->getLogicGrid();
		if (temp.x == grid.x && temp.y == grid.y)
			return m_starsSprite[i];
	}
	return NULL;
}

vector<StarNode *>	StarsLayer::getStarNeighbours(StarNode *star)
{
	vector<StarNode *> neighbours;
	LogicGrid grid = star->getLogicGrid();
	int arr[4][2] = { { 1, 0 }, { -1, 0 }, { 0, -1 }, { 0, 1 } };
	for (int i = 0; i < 4; ++i)
	{
		auto neighbour = getStarByGrid(LogicGrid(grid.x + arr[i][0], grid.y + arr[i][1]));
		if (neighbour != NULL && neighbour->sameType(star->getStarType()))
		{
			neighbours.push_back(neighbour);
		}
	}
	return neighbours;
}
void StarsLayer::moveStars()
{
	sort(m_starsSprite.begin(), m_starsSprite.end(), [=](StarNode *node1, StarNode *node2)->bool
	{
		int direction = StageModel::theModel()->getCurDirection();
		switch (direction)
		{
		case MOVE_UP:
			return node1->getLogicGrid().y > node2->getLogicGrid().y;
			break;
		case MOVE_DOWN:
			return node1->getLogicGrid().y < node2->getLogicGrid().y;
			break;
		case MOVE_LEFT:
			return node1->getLogicGrid().x < node2->getLogicGrid().x;
			break;
		case MOVE_RIGHT:
			return node1->getLogicGrid().x > node2->getLogicGrid().x;
			break;
		default:
			break;
		}
		
	});
	for (size_t i = 0; i < m_starsSprite.size(); ++i)
	{
		m_starsSprite[i]->doMove();
	}
}

void StarsLayer::genNewStars()
{
	int direction = 1;
	//移动方向： 上下左右
	int moveDirection[4][2] = { { 0, 1 }, { 0, -1 }, { -1, 0 }, { 1, 0 } };
	int emptyGridX[COlUMNS_SIZE];	//值为x的一列上空格的个数
	int emptyGridY[ROWS_SIZE];		//值为y的一行上空格的个数
	for (int x = 0; x < COlUMNS_SIZE; ++x)
	{
		for (int y = 0; y < ROWS_SIZE; ++y)
		{
			auto iter = find_if(m_starsSprite.begin(), m_starsSprite.end(), [=](StarNode *node)->bool
			{
				auto grid = node->getLogicGrid();
				return  grid.x == x && grid.y == y;
			});
			
			if (iter == m_starsSprite.end())
			{
				emptyGridX[x]++;
				emptyGridY[y]++;
			}
		}
	}

	vector<LogicGrid> newGrid;
	switch (direction)
	{
	case MOVE_UP:
		for (int i = 0; i < COlUMNS_SIZE; ++i)
		{
			for (int j = 0; j < emptyGridX[i]; ++j)
			{
				LogicGrid grid(i, -2 + j);
				newGrid.push_back(grid);
			}
		}
		break;
	case MOVE_DOWN:
		for (int i = 0; i < COlUMNS_SIZE; ++i)
		{
			for (int j = 0; j < emptyGridX[i]; ++j)
			{
				LogicGrid grid(i, ROWS_SIZE + 2 - j);
				newGrid.push_back(grid);
			}
		}
		break;
	case MOVE_LEFT:
		for (int i = 0; i < ROWS_SIZE; ++i)
		{
			for (int j = 0; j < emptyGridY[i]; ++j)
			{
				LogicGrid grid(i, COlUMNS_SIZE + 2 - j);
				newGrid.push_back(grid);
			}
		}
		break;
	case MOVE_RIGHT:
		for (int i = 0; i < ROWS_SIZE; ++i)
		{
			for (int j = 0; j < emptyGridY[i]; ++j)
			{
				LogicGrid grid(i, -2 + j);
				newGrid.push_back(grid);
			}
		}
		break;
	default:
		break;
	}

	int color = ((int)(CCRANDOM_0_1() * 100)) % 5;
	for (size_t i = 0; i < newGrid.size(); ++i)
	{
		auto grid = newGrid[i];
		auto pStarSprite = createStar(color, grid);
		pStarSprite->setAnchorPoint(ccp(0.5f, 0.5f));
		CCPoint targetPos = getPosByGrid(grid);
		addChild(pStarSprite);
	}
}

bool StarsLayer::isGridEmpty(LogicGrid grid)
{
	auto iter = find_if(m_starsSprite.begin(), m_starsSprite.end(), [=](StarNode *node)->bool
	{
		auto temp = node->getLogicGrid();
		return  grid.x == temp.x && grid.y == temp.y;
	});

	return iter == m_starsSprite.end();
}

void StarsLayer::moveStar(StarNode *star)
{
	int direction = StageModel::theModel()->getCurDirection();
	auto curGrid = star->getLogicGrid();
	auto targetGrid = curGrid;
	switch (direction)
	{
	case MOVE_UP :
		for (int i = curGrid.y + 1; i < ROWS_SIZE; ++i)
		{
			if (isGridEmpty(LogicGrid(curGrid.x, i)))
			{
				targetGrid.y++;
			}
		}
		break;
	case MOVE_DOWN:
		for (int i = 0; i < curGrid.y; ++i)
		{
			if (isGridEmpty(LogicGrid(curGrid.x, i)))
			{
				targetGrid.y--;
			}
		}
		break;	
	case MOVE_LEFT:
		for (int i = 0; i < curGrid.x; i++)
			{
			if (isGridEmpty(LogicGrid(i, curGrid.y)))
				{
					targetGrid.x--;
				}
			}
		break;	
	case MOVE_RIGHT:
		for (int i = curGrid.x + 1; i < COlUMNS_SIZE; ++i)
			{
			if (isGridEmpty(LogicGrid(i, curGrid.y)))
				{
					targetGrid.x++;

				}
			}
		break;
	}

	auto targetPos = getPosByGrid(targetGrid);
	auto moveTo = CCMoveTo::create(0.1f, targetPos);
	star->runAction(moveTo);
	star->setLogicGrid(targetGrid);
}

void StarsLayer::removeStar(StarNode *node)
{
	node->removeFromParent();
	auto iter = find(m_starsSprite.begin(), m_starsSprite.end(), node);
	if (iter != m_starsSprite.end())
	{
		m_starsSprite.erase(iter);
	}
}
