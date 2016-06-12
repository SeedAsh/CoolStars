#include "StarsLayer.h"
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
	StageLayersMgr::theMgr()->addLayers(this);
}

void StarsLayer::onExit()
{
	CCLayer::onExit();
	StageModel::theModel()->removeView(this);
	StageLayersMgr::theMgr()->addLayers(this);

}

bool StarsLayer::init()
{
	StageModel::theModel()->initStarsData();
	initStars();
	return true;
}

StarViewNode *StarsLayer::createStarByGrid(const LogicGrid &grid)
{
	StarNode *nodeData = StageModel::theModel()->getStarNode(grid);
	if (nodeData)
	{
		return StarViewNode::create(nodeData);
	}
	return NULL;
}

void StarsLayer::initStars()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	StarViewNode *pStarSprite = NULL;
	float speed = visibleSize.height / 0.9f;
	float maxDuration = 0;
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
				maxDuration = max(maxDuration, kDuration);
				CCMoveTo *moveTo = CCMoveTo::create(kDuration, targetPos);
				pStarSprite->runAction(moveTo);
			}
		}
	}
	runAction(CCSequence::create(CCDelayTime::create(maxDuration)
		, CCCallFunc::create(this, callfunc_selector(StarsLayer::starInitDone)),NULL));
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

void StarsLayer::removeStar(StarViewNode *node)
{
	node->removeFromParent();
	auto iter = find(m_starsSprite.begin(), m_starsSprite.end(), node);
	if (iter != m_starsSprite.end())
	{
		m_starsSprite.erase(iter);
	}
}

void StarsLayer::onCreateNewStar(StarNode *node)
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
