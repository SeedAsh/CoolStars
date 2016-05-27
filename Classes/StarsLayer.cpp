#include "StarsLayer.h"
#include "StarUtil.h"
#include "StarNode.h"
using namespace cocos2d;
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
	for (int col = 0; col < COlUMNS_SIZE; col++)
	{
		for (int row = 0; row < ROWS_SIZE; row++)
		{
			pStar = &m_pStarUtil->star[col][row];

			pStarSprite = createStar(pStar->color, LogicGrid(col, row));
			pStarSprite->setAnchorPoint(ccp(0.5f, 0.5f));
			CCPoint targetPos = ccp(STAR_SIZE * 0.5f + col * STAR_SIZE,
				STAR_SIZE * (ROWS_SIZE - 0.5f - row));
			CCPoint sourcePos = targetPos;

			float deltaHeight = STAR_SIZE * 2;
			sourcePos.y = targetPos.y + visibleSize.height + deltaHeight * (ROWS_SIZE - row) +col % 2 * (deltaHeight + STAR_SIZE)* 0.5f;
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
}

//左下第一个grid为（0，0）
CCPoint StarsLayer::getPosByGrid(LogicGrid grid)
{
	CCPoint pos;
	pos.x = STAR_SIZE * (grid.GridY + 0.5f);
	pos.y = STAR_SIZE * (grid.GridX + 0.5f);
	return pos;
}

StarNode *StarsLayer::getStarByGrid(LogicGrid grid)
{
	if (grid.GridX < 0 || grid.GridX >= COlUMNS_SIZE || grid.GridY < 0 || grid.GridY >= ROWS_SIZE)
		return NULL;

	for (size_t i = 0; i < m_starsSprite.size(); ++i)
	{
		auto temp = m_starsSprite[i]->getLogicGrid();
		if (temp.GridX == grid.GridX && temp.GridY == grid.GridY)
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
		auto neighbour = getStarByGrid(LogicGrid(grid.GridX + arr[i][0], grid.GridY + arr[i][1]));
		if (neighbour != NULL && neighbour->sameType(star->getStarType()))
		{
			neighbours.push_back(neighbour);
		}
	}
	return neighbours;
}