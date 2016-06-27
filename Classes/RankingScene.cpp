#include "RankingScene.h"
#include "UiLayout.h"
#include "TitlePanel.h"
#include "ListView.h"
#include "ListSlideView.h"
#include "RankingPanelUtil.h"
#include "CommonMacros.h"

USING_NS_CC;
using namespace std;

bool RankingScene::init()
{
	setPanelId(kRankingPanel);

	auto winSize = CCDirector::sharedDirector()->getWinSize();
	setContentSize(winSize);

	auto titlePanel = TitlePanel::create(m_touchPriority);
	addChild(titlePanel);

	m_layout = UiLayout::create("layout/ranking_panel.xml");
	m_layout->setMenuTouchPriority(m_touchPriority);
	m_layout->setAnchorPoint(ccp(0.5f, 0.5f));
	m_layout->setPosition(ccpMult(winSize, 0.5f));

	addChild(m_layout);

	initMainLayout();
	return true;
}

void RankingScene::initMainLayout()
{
	auto pos = m_layout->getChildById(7)->getPosition();
	ListSlideView *rankList = ListSlideView::create(ccp(350, 400));
	addChild(rankList);
	rankList->setAnchorPoint(ccp(0, 1));
	rankList->setPosition(pos);
	rankList->setSpacing(10);
	/*
	sort(configs.begin(), configs.end(), [=](ShopConfig config1, ShopConfig config2)->bool
	{
		return config1.diamond > config2.diamond;
	});
	*/
	for (int i = 10; i >= 0; --i)
	{
		rankList->addNode(RankingNode::create(i));
	}
	
}


