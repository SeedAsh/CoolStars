#include "StarViewNode.h"
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

StarViewNode *StarViewNode::create(StarNode *node)
{
	StarViewNode *ViewNode = new StarViewNode(node);
	ViewNode->autorelease();
	ViewNode->init();
	return ViewNode;
}

StarViewNode::StarViewNode(StarNode *node)
: m_model(node)
, m_isExploded(false)
{

}

bool StarViewNode::init()
{
	auto attr = m_model->getAttr();
	string fileName = g_starFrameNameArray[attr.color - 1][1];
	CCSprite *spr = CCSprite::create(fileName.c_str());
	CCSize size = spr->getContentSize();
	spr->setPosition(ccp(size.width * 0.5, size.height * 0.5f));
	setContentSize(size);
	
	addChild(spr);
	return true;
}

vector<StarViewNode *>StarViewNode::getNeighbours()
{
	StarsLayer *layer = (StarsLayer *)getParent();
	return layer->getStarNeighbours(this);
}


void StarViewNode::onClick()
{
	m_model->handleClick();
}

void StarViewNode::doMove()
{
	StarsLayer *layer = (StarsLayer *)getParent();
	return layer->moveStar(this);
}

void StarViewNode::runExplosion(){
	CCParticleExplosion *pEmitter = CCParticleExplosion::create();
	auto attr = m_model->getAttr();
	string fileImage = s_stars[attr.color - 1];
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

void StarViewNode::doExplodeAction()
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
