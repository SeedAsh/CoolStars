#include "StarsLayer.h"
#include "StarUtil.h"
using namespace cocos2d;
StarsLayer::StarsLayer()
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



void StarsLayer::showStars()
{
	//m_pStarUtil->star[][] 中是一列列保存的
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite *pStarSprite = NULL;
	Star *pStar = NULL;
	float speed = visibleSize.height / 0.9f;
	for (int col = 0; col < COlUMNS_SIZE; col++)
	{
		for (int row = 0; row < ROWS_SIZE; row++)
		{
			pStar = &m_pStarUtil->star[col][row];

			pStarSprite = CCSprite::create(g_starFrameNameArray[pStar->color][1].c_str());
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

}

void StarsLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{

}
