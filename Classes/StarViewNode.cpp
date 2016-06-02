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
    m_model->bindView(this);
}

StarViewNode::~StarViewNode()
{
}
bool StarViewNode::init()
{
	auto config = m_model->getConfig();
	string fileName = config.resPath;
	CCSprite *spr = CCSprite::create(fileName.c_str());
	CCSize size = spr->getContentSize();
	spr->setPosition(ccp(size.width * 0.5, size.height * 0.5f));
	setContentSize(size);
	
	addChild(spr);
	return true;
}

void StarViewNode::onClick()
{
	m_model->handleClick();
}

//左下第一个grid为（0，0）
CCPoint StarViewNode::getPosByGrid(LogicGrid grid)
{
    CCPoint pos;
    pos.x = STAR_SIZE * (grid.x + 0.5f);
    pos.y = STAR_SIZE * (grid.y + 0.5f);
    return pos;
}

void StarViewNode::doMove(LogicGrid targetGrid)
{
	CCPoint pos = getPosByGrid(targetGrid);
    CCMoveTo *moveTo = CCMoveTo::create(0.2f, pos);
    runAction(moveTo);
}

void StarViewNode::runExplosion(){
	CCParticleExplosion *pEmitter = CCParticleExplosion::create();
	auto config = m_model->getConfig();
	string fileImage = config.explosionPath;
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

    StarsLayer *layer = (StarsLayer *)getParent();
    layer->addChild(pEmitter);
    layer->removeStar(this);
    
}
