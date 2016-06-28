#include "LotteryScene.h"
#include "UiLayout.h"
#include "TitlePanel.h"
#include "ListView.h"
#include "EmptyBox.h"
#include "CommonMacros.h"
#include "MainScene.h"
#include "LotteryModel.h"

USING_NS_CC;
using namespace std;

LotteryNode *LotteryNode::create(int touchPriority)
{
	auto node = new LotteryNode(touchPriority);
	node->init();
	node->autorelease();
	return node;
}

bool LotteryNode::init()
{
	m_layout = UiLayout::create("layout/lottery_node.xml");
	addChild(m_layout);
	setContentSize(m_layout->getContentSize());
	return true;
}
bool LotteryNode::onTouchBegan(cocos2d::CCPoint pt, bool isInside)
{
	if (isInside)
	{
		auto data = LotteryModel::theModel()->doLottery();
		CCLog("type = \"%d\", param = \"%d\"", data.type, data.param);
	}
	return isInside;
}

////////////////////////////////////////////////////////////////
void LotteryScene::onEnter()
{
	BasePanel::onEnter();
}

void LotteryScene::onExit()
{
	BasePanel::onExit();
}

bool LotteryScene::init()
{
	setPanelId(kLotteryPanel);

	auto winSize = CCDirector::sharedDirector()->getWinSize();
	setContentSize(winSize);

	m_layout = UiLayout::create("layout/lottery_panel.xml");
	m_layout->setMenuTouchPriority(m_touchPriority);
	m_layout->setAnchorPoint(ccp(0.5f, 0.5f));
	m_layout->setPosition(ccpMult(winSize, 0.5f));
	addChild(m_layout);

	m_bottomLayout = UiLayout::create("layout/pre_stage_bottom.xml");
	addChild(m_bottomLayout);

	auto titlePanel = TitlePanel::create(m_touchPriority);
	addChild(titlePanel);

	initLayout();
	initBottomLayout();

	return true;
}

void LotteryScene::initLayout()
{
	CCMenuItem * toPetSceneBtn = dynamic_cast<CCMenuItem *>((m_layout->getChildById(16)));
	toPetSceneBtn->setTarget(this, menu_selector(LotteryScene::toPetScene));
	
	int boxIds[] = { 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	for (int i = 0; i < 9; ++i)
	{
		EmptyBox *box = dynamic_cast<EmptyBox *>((m_layout->getChildById(boxIds[i])));
		auto node = LotteryNode::create(m_touchPriority);
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
	MainScene::theScene()->showPanel(kPetPanel);
}

void LotteryScene::startLottery(CCObject* pSender)
{

}
