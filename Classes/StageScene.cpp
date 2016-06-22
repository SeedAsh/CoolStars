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

bool StageScene::init()
{
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	setContentSize(winSize);

	UiLayout *layout = UiLayout::create("layout/stage.xml");
	addChild(layout);
	auto node = dynamic_cast<EmptyBox *>((layout->getChildById(4)));

	StarsLayer *starsLayer = StarsLayer::create(&m_stateOwner);
	node->setNode(starsLayer);

	StageUiLayer *uiLayer = StageUiLayer::create(&m_stateOwner);
	addChild(uiLayer);
	
	m_stateOwner.setStarsLayer(starsLayer);
	m_stateOwner.setUiLayer(uiLayer);
	m_stateOwner.init();

	return true;
}
