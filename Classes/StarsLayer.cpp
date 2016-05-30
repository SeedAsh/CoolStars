﻿#include "StarsLayer.h"
#include "StarUtil.h"
#include "StarViewNode.h"
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
	StageModel::theModel()->initStarsData();
	initStars();
	return true;
}

void StarsLayer::initStars()
{
	//m_pStarUtil->star[][] 中是一列列保存的
	auto starUtil = new StarUtil();
	starUtil->initStarEx();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	StarViewNode *pStarSprite = NULL;
	Star *pStar = NULL;
	float speed = visibleSize.height / 0.9f;
	for (int col = 0; col < COlUMNS_SIZE; ++col)
	{
		for (int row = 0; row < ROWS_SIZE; ++row) 
		{
			LogicGrid grid(col, row);
			StarNode *nodeData = StageModel::theModel()->getStarData(grid);
			if (nodeData)
			{
				pStarSprite = StarViewNode::create(nodeData);
				pStarSprite->setAnchorPoint(ccp(0.5f, 0.5f));
				CCPoint targetPos = getPosByGrid(grid);
				CCPoint sourcePos = targetPos;
				//实现梅花间隔掉落
				sourcePos.y = targetPos.y + visibleSize.height + grid.y * STAR_SIZE + (grid.x % 2) * STAR_SIZE;
				pStarSprite->setPosition(sourcePos);
				addChild(pStarSprite);
				m_starsSprite.push_back(pStarSprite);

				float kDuration = (sourcePos.y - targetPos.y) / speed;
				CCMoveTo *moveTo = CCMoveTo::create(kDuration, targetPos);
				pStarSprite->runAction(moveTo);
			}

		}
	}
	runAction(CCCallFunc::create(this, callfunc_selector(StarsLayer::starInitDone)));
}

void StarsLayer::starInitDone()
{
	setTouchEnabled(true);
}

StarViewNode *StarsLayer::getClickedStar(CCPoint pos)
{
	for (size_t i = 0; i < m_starsSprite.size(); ++i)
	{
		StarViewNode *star = m_starsSprite[i];
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
	CCPoint pos = convertToNodeSpace(touchLocation);
	StarViewNode *star = getClickedStar(pos);
	if (star == NULL) return;
	
	star->onClick();
    StageModel::theModel()->moveStars();
}

//左下第一个grid为（0，0）
CCPoint StarsLayer::getPosByGrid(LogicGrid grid)
{
	CCPoint pos;
	pos.x = STAR_SIZE * (grid.x + 0.5f);
	pos.y = STAR_SIZE * (grid.y + 0.5f);
	return pos;
}

StarViewNode *StarsLayer::getStarByGrid(LogicGrid grid)
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
        
			auto iter = find_if(m_starsSprite.begin(), m_starsSprite.end(), [=](StarViewNode *node)->bool
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
		auto pStarSprite = StarViewNode::create(NULL);
		pStarSprite->setAnchorPoint(ccp(0.5f, 0.5f));
		addChild(pStarSprite);
	}
}

void StarsLayer::removeStar(StarViewNode *node)
{
	node->removeFromParent();
	auto iter = find(m_starsSprite.begin(), m_starsSprite.end(), node);
	if (iter != m_starsSprite.end())
	{
		m_starsSprite.erase(iter);
	}
}
