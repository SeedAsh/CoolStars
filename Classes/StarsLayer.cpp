#include "StarsLayer.h"
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

void StarsLayer::onEnter()
{
	CCLayer::onEnter();
	StageModel::theModel()->addView(this);
}

void StarsLayer::onExit()
{
	CCLayer::onExit();
	StageModel::theModel()->removeView(this);
}

bool StarsLayer::init()
{
	StageModel::theModel()->initStarsData();
	initStars();
	return true;
}

StarViewNode *StarsLayer::createStarByGrid(const LogicGrid &grid)
{
	StarNode *nodeData = StageModel::theModel()->getStarData(grid);
	if (nodeData)
	{
		return StarViewNode::create(nodeData);
	}
	return NULL;
}

void StarsLayer::initStars()
{
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
			pStarSprite = createStarByGrid(grid);
			if (pStarSprite)
			{
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
	StageModel::theModel()->genNewStars();
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

void StarsLayer::removeStar(StarViewNode *node)
{
	node->removeFromParent();
	auto iter = find(m_starsSprite.begin(), m_starsSprite.end(), node);
	if (iter != m_starsSprite.end())
	{
		m_starsSprite.erase(iter);
	}
}

void StarsLayer::createNewStar(StarNode *node)
{
	auto pStarSprite = StarViewNode::create(node);
	auto grid = node->getAttr().grid;
	if (pStarSprite)
	{
		pStarSprite->setAnchorPoint(ccp(0.5f, 0.5f));
		CCPoint pos = getPosByGrid(grid);
		pStarSprite->setPosition(pos);
		addChild(pStarSprite);
		m_starsSprite.push_back(pStarSprite);
	}
}
