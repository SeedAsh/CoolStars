#include "StageScene.h"
#include "StarsLayer.h"
#include "StageUiLayer.h"
#include "VisibleRect.h"
#include "UiLayout.h"
#include "EmptyBox.h"
#include "BackgroundLayer.h"
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
	
	BackgroundLayer *bk = BackgroundLayer::create();
	addChild(bk);

	UiLayout *layout = UiLayout::create("layout/stage.xml");
	addChild(layout);
	auto node = dynamic_cast<EmptyBox *>((layout->getChildById(4)));

	StarsLayer *starsLayer = StarsLayer::create();
	node->setNode(starsLayer);

	StageUiLayer *uiLayer = StageUiLayer::create();
	addChild(uiLayer);
	return true;
}
