#include "LotteryScene.h"
#include "UiLayout.h"
#include "TitlePanel.h"
#include "ListView.h"
#include "EmptyBox.h"

USING_NS_CC;
using namespace std;


bool LotteryNode::init()
{
	m_layout = UiLayout::create("layout/lottery_node.xml");
	addChild(m_layout);
	setContentSize(m_layout->getContentSize());
	return true;
}

bool LotteryScene::init()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	setContentSize(winSize);

	m_layout = UiLayout::create("layout/lottery_panel.xml");
	m_layout->setAnchorPoint(ccp(0.5f, 0.5f));
	m_layout->setPosition(ccpMult(winSize, 0.5f));
	addChild(m_layout);

	auto titlePanel = TitlePanel::create();
	addChild(titlePanel);

	m_bottomLayout = UiLayout::create("layout/pre_stage_bottom.xml");
	addChild(m_bottomLayout);

	initLayout();
	initBottomLayout();

	return true;
}

CCScene* LotteryScene::scene()
{
	CCScene *scene = CCScene::create();
	LotteryNode *layer = LotteryNode::create();
	scene->addChild(layer);
	return scene;
}


void LotteryScene::initLayout()
{
	CCMenuItem * normalBtn = dynamic_cast<CCMenuItem *>((m_layout->getChildById(5)));
	normalBtn->setTarget(this, menu_selector(LotteryScene::toPetScene));
	
	int boxIds[] = { 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	for (int i = 0; i < 9; ++i)
	{
		EmptyBox *box = dynamic_cast<EmptyBox *>((m_layout->getChildById(boxIds[i])));
		auto node = LotteryNode::create();
		box->setNode(node);
	}
}

void LotteryScene::initBottomLayout()
{
	CCMenuItem *startGameBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(1)));
	startGameBtn->setTarget(this, menu_selector(LotteryScene::startLottery));
}

void LotteryScene::toPetScene(CCObject* pSender)
{

}

void LotteryScene::startLottery(CCObject* pSender)
{

}

