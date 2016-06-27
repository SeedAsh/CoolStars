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
	setPanelId(kStageView);

	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	setContentSize(winSize);

	m_layout = UiLayout::create("layout/stage.xml");
	auto stars = dynamic_cast<EmptyBox *>((m_layout->getChildById(4)));
	StarsLayer *starsLayer = StarsLayer::create(&m_stateOwner);
	stars->setNode(starsLayer);

	auto bkGrid = dynamic_cast<EmptyBox *>((m_layout->getChildById(1)));
	bkGrid->setNode(getBkGrid());

	addChild(m_layout);
	StageUiLayer *uiLayer = StageUiLayer::create(&m_stateOwner);
	addChild(uiLayer);
	
	m_stateOwner.setStarsLayer(starsLayer);
	m_stateOwner.setUiLayer(uiLayer);
	m_stateOwner.init();

	return true;
}

CCNode *StageScene::getBkGrid()
{
	CCNode *node = CCNode::create();
	static const float kSpacing = 2;
	float curX = kSpacing;
	float curY = kSpacing;
	float maxHeight = 0;
	

	for (int row = 0; row < ROWS_SIZE; ++row)
	{
		for (int col = 0; col < COlUMNS_SIZE; ++col)
		{
			auto grid = CCSprite::create("stage/yxjm_di2.png");
			grid->setAnchorPoint(ccp(0, 0));
			auto size = grid->getContentSize();
			node->addChild(grid);
			grid->setPosition(ccp(curX, curY));
			curX += size.width + kSpacing;
			if (maxHeight < size.height)
			{
				maxHeight = size.height;
			}
		}
		curX = kSpacing;
		curY += maxHeight + kSpacing;
	}
	node->setContentSize(m_layout->getChildById(5)->getContentSize());

	/*
	auto color = CCLayerColor::create(ccc4(255, 0, 0, 79));
	node->addChild(color);
	color->setContentSize(node->getContentSize());
	*/
	return node;
}
