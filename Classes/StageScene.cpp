#include "StageScene.h"
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
	return true;
}