#include "StageScene.h"
#include "StarsLayer.h"
#include "StageUiLayer.h"
#include "VisibleRect.h"
using namespace cocos2d;

StageScene::StageScene()
{

}

StageScene::~StageScene()
{

}

CCScene* StageScene::scene()
{
	CCScene *scene = CCScene::create();

	StageScene *layer = StageScene::create();

	scene->addChild(layer);

	return scene;
}

StageScene* StageScene::create()
{
	StageScene *node = new StageScene();
	node->autorelease();
	node->init();
	return node;
}

bool StageScene::init()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	initBackground();
	StarsLayer *starsLayer = StarsLayer::create();
	starsLayer->setPosition(visibleSize.width * 0.1f, visibleSize.height * 0.2f);
	StageUiLayer *uiLayer = StageUiLayer::create();

	addChild(starsLayer, ZORDER_STARS);
	addChild(uiLayer, ZORDE_UI);
	return true;
}

void StageScene::initBackground()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* pStageBg = CCSprite::create("bg_mainscene.jpg");
	pStageBg->setPosition(ccp(winSize.width * 0.5f, winSize.height * 0.5f));
	
	addChild(pStageBg, ZORDER_BACKGROUND);
}

void StageScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	
}