#include "StageScene.h"
#include "StarsLayer.h"
#include "StageUiLayer.h"
#include "VisibleRect.h"
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
	setPanelId(kStageView);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	setContentSize(winSize);

	StarsLayer *starsLayer = StarsLayer::create(&m_stateOwner);
	starsLayer->setAnchorPoint(ccp(0.5f, 0.5f));
	starsLayer->setPosition(ccpMult(winSize, 0.5f));
	addChild(starsLayer);

	StageUiLayer *uiLayer = StageUiLayer::create(&m_stateOwner);
	addChild(uiLayer);
	
	m_stateOwner.setStarsLayer(starsLayer);
	m_stateOwner.setUiLayer(uiLayer);
	m_stateOwner.init();

	return true;
}
