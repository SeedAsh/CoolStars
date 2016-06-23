#include "StarsLayer.h"
#include "StarViewNode.h"
#include "StageModel.h"
#include "StageSceneState.h"

using namespace cocos2d;
using namespace std;
StarsLayer::StarsLayer(StageStateOwner *stateOwner)
:m_starsSprite(NULL)
, m_stateOwner(stateOwner)
{
	
}

StarsLayer::~StarsLayer()
{
}

StarsLayer *StarsLayer::create(StageStateOwner *stateOwner)
{
	StarsLayer* layer = new StarsLayer(stateOwner);
	layer->init();
	layer->autorelease();
	return layer;
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

	addClippingNode();
	StageModel::theModel()->initStarsData();
	initStars();
	return true;
}

void StarsLayer::addClippingNode()
{
	CCLayerColor *back = CCLayerColor::create(ccc4(125, 0, 0, 255));
	CCSize size = CCSize(STAR_SIZE * COlUMNS_SIZE, STAR_SIZE * ROWS_SIZE);
	back->setContentSize(size);
	//addChild(back);
	
	CCSprite *sp = CCSprite::create("shop/sd_zuanshi2.png");
	sp->setAnchorPoint(ccp(0, 0));
	m_clippingNode = CCClippingNode::create();
	m_clippingNode->setInverted(false);
	m_clippingNode->setAlphaThreshold(1.0f);
	m_clippingNode->setStencil(back);
	addChild(m_clippingNode);
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
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	StarViewNode *pStarSprite = NULL;
	float startHeight = STAR_SIZE * ROWS_SIZE;
	float speed = startHeight / 0.5f;

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
				sourcePos.y = targetPos.y + startHeight + grid.y * STAR_SIZE + (grid.x % 2) * STAR_SIZE;
				pStarSprite->setPosition(sourcePos);
				m_clippingNode->addChild(pStarSprite);
				//addChild(pStarSprite);
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
	
	m_stateOwner->clickStar(star->getGrid());
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
		m_clippingNode->addChild(pStarSprite);
		//addChild(pStarSprite);
		m_starsSprite.push_back(pStarSprite);
	}
}
