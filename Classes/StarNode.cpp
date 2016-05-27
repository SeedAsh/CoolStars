#include "StarNode.h"
#include "StarsLayer.h"
#include "StarUtil.h"
#include "StageModel.h"
using namespace cocos2d;
using namespace std;

static const char s_fire[] = "particle/fire.png";
static const string s_stars[] = {
	"particle/starp1.png",
	"particle/starp2.png",
	"particle/starp3.png",
	"particle/starp4.png",
	"particle/starp5.png"
};

StarNode *StarNode::create(int starType, LogicGrid grid)
{
	StarNode *node = new StarNode(starType,grid);
	node->autorelease();
	node->init();
	return node;
}

StarNode::StarNode(int starType, LogicGrid grid)
: m_starType(starType)
, m_isExploded(false)
, m_grid(grid)
{

}

StarNode::~StarNode()
{

}

bool StarNode::init()
{
	string fileName = g_starFrameNameArray[m_starType][1];
	CCSprite *spr = CCSprite::create(fileName.c_str());
	CCSize size = spr->getContentSize();
	spr->setPosition(ccp(size.width * 0.5, size.height * 0.5f));
	setContentSize(size);

	addChild(spr);
	return true;
}

vector<StarNode *>StarNode::getNeighbours()
{
	StarsLayer *layer = (StarsLayer *)getParent();
	return layer->getStarNeighbours(this);
}

bool StarNode::hasNeighbour()
{
	return false;
}

void StarNode::onClick()
{

}

void StarNode::doMove()
{
	StarsLayer *layer = (StarsLayer *)getParent();
	return layer->moveStar(this);
}

void StarNode::runExplosion(){
	CCParticleExplosion *pEmitter = CCParticleExplosion::create();
	string fileImage = s_stars[m_starType];
	if (fileImage.empty()) return;
	pEmitter->setTexture(CCTextureCache::sharedTextureCache()->addImage(fileImage.c_str()));
	pEmitter->setAutoRemoveOnFinish(true);

	pEmitter->setPosition(getPosition());

	ccColor4F c4Var = { 0, 0, 0, 0.0 };
	ccColor4F c4 = { 1, 1, 1, 1 };
	pEmitter->setStartColor(c4);
	pEmitter->setEndColor(c4);
	pEmitter->setStartColorVar(c4Var);
	pEmitter->setEndColorVar(c4Var);

	pEmitter->setTotalParticles(10);

	pEmitter->setRadialAccel(1);
	pEmitter->setRadialAccelVar(5);

	pEmitter->setSpeed(200);
	pEmitter->setScale(1.2f);
	pEmitter->setGravity(ccp(0, -200));

	getParent()->addChild(pEmitter);
}

void StarNode::doExplodeAction()
{
	if (m_isExploded) return;
	m_isExploded = true;
	runExplosion();

	auto neighbours = getNeighbours();
	for (size_t i = 0; i < neighbours.size(); ++i)
	{
		neighbours[i]->doExplodeAction();
	}
	
	StarsLayer *layer = (StarsLayer *)getParent();
	layer->removeStar(this);
}
