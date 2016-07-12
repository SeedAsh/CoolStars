#include "LotteryScene.h"
#include "UiLayout.h"
#include "TitlePanel.h"
#include "ListView.h"
#include "EmptyBox.h"
#include "CommonMacros.h"
#include "MainScene.h"
#include "LotteryModel.h"
#include "CommonUtil.h"
#include "UserInfo.h"
#include "DataManager.h"
#include "PetManager.h"
#include "CCFunctionAction.h"
#include "StarsController.h"

USING_NS_CC;
using namespace std;

LotteryNode::LotteryNode(int touchPriority)
: TouchNode(touchPriority)
, m_isOpened(false)
{
	m_handle = function<void()>();
}

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
	if (isInside && !m_isOpened)
	{
		m_isOpened = true;
		CCSprite *box = dynamic_cast<CCSprite *>(m_layout->getChildById(1));
		box->initWithFile("lottery/cjjm_baoxiang2.png");
		auto data = LotteryModel::theModel()->getLotteryResult();
		string resPath;
		if (data.type == kLotteryPet)
		{
			auto pet = PetManager::petMgr()->getPetById(data.param);
			resPath = pet->getPetData().petImgRes;
		}
		else
		{
			auto config = DataManagerSelf->getLotteryOutputConfig(data.type);
			resPath = config.resPath;
		}
		CCSprite *rewardImg = CCSprite::create(resPath.c_str());
		auto size = getContentSize();
		rewardImg->setPosition(ccpMult(size, 0.5f));
		addChild(rewardImg);
		rewardImg->runAction(getRewardOutAction(data));
	}
	return isInside;
}

CCAction *LotteryNode::getRewardOutAction(LotteryData data)
{
	CCMoveBy *moveBy = CCMoveBy::create(0.5f, ccp(0, 30));
	auto func = CCFunctionAction::create([=]()
	{
		LotteryModel::theModel()->doLottery(data);
		m_handle();
	});
	return CCSequence::create(CCEaseBackInOut::create(moveBy), func, NULL);
}
////////////////////////////////////////////////////////////////
LotteryScene *LotteryScene::create(int usage)
{
	LotteryScene *scene = new LotteryScene(usage);
	scene->init();
	scene->autorelease();
	return scene;
}

LotteryScene::LotteryScene(int usage)
: m_openedBoxNum(0)
{
	setUsage(usage);
}

void LotteryScene::onEnter()
{
	BasePanel::onEnter();
	UserInfo::theInfo()->addView(this);
}

void LotteryScene::onExit()
{
	BasePanel::onExit();
	UserInfo::theInfo()->removeView(this);
}

bool LotteryScene::init()
{
	setPanelId(kLotteryPanel);

	auto winSize = CCDirector::sharedDirector()->getWinSize();
	setContentSize(winSize);

	m_layout = UiLayout::create("layout/lottery_panel.xml");
	m_layout->setMenuTouchPriority(m_touchPriority);
	m_layout->setAnchorPoint(ccp(0.5f, 0.5f));
	auto sourcePos = ccp(winSize.width * 0.5f, winSize.height * 1.5f);
	auto targetPos = ccpMult(winSize, 0.5f);
	m_layout->setPosition(sourcePos);
	m_layout->runAction(CCEaseBackInOut::create(CCMoveTo::create(0.5f, targetPos)));
	addChild(m_layout);
	initLayout();

	auto titlePanel = TitlePanel::create(m_touchPriority);
	addChild(titlePanel);

	if (m_usage == kLotterySceneFromStageScene)
	{
		m_bottomLayout = UiLayout::create("layout/pre_stage_bottom.xml");
		addChild(m_bottomLayout);
		initBottomLayout();
	}
	refreshUi();
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
		node->setHandle(bind(&LotteryScene::onOpenReward, this));
		box->setNode(node);
	}

	onKeyChanged();
}

void LotteryScene::initBottomLayout()
{
	CCMenuItem *startGameBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(1)));
	startGameBtn->setTarget(this, menu_selector(LotteryScene::onStartBtnClicked));
}

void LotteryScene::refreshUi()
{
	if (m_usage == kLotterySceneFromStageScene)
	{
		int key = UserInfo::theInfo()->getKey();
		m_bottomLayout->getChildById(1)->setVisible(m_openedBoxNum >= kMinOpenBoxNum || key <= 0);
	}
}

void LotteryScene::toPetScene(CCObject* pSender)
{
	MainScene::theScene()->showPanel(kPetPanel);
}

void LotteryScene::onStartBtnClicked(CCObject* pSender)
{
	StarsController::theModel()->resetStage(kNormalType);
	MainScene::theScene()->showPanel(kPreStagePanel);
}

void LotteryScene::onOpenReward()
{
	m_openedBoxNum++;

	if (m_openedBoxNum % kRewardBoxNum == 0)
	{
		auto func = CCFunctionAction::create([=]()
		{
			removeAllChildrenWithCleanup(true);
			init();
		});
		runAction(CCSequence::create(CCDelayTime::create(1.5f), func, NULL));
	}
	refreshUi();
}

void LotteryScene::onKeyChanged()
{
	CCLabelAtlas * keyNum = dynamic_cast<CCLabelAtlas *>((m_layout->getChildById(17)));
	int amount = UserInfo::theInfo()->getKey();
	char str[100] = { 0 };
	sprintf(str, ":%d", amount);
	keyNum->setString(str);
}