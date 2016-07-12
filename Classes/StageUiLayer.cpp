#include "StageUiLayer.h"
#include "VisibleRect.h"
#include "UserInfo.h"
#include "GameData.h"
#include "SoundMgr.h"
#include "MenuScene.h"
#include "PauseDialog.h"
#include "PetManager.h"
#include "StageOperator.h"
#include "CommonUtil.h"
#include "GameResultLayer.h"
#include "PropManager.h"
#include "PropItemView.h"
#include "UiLayout.h"
#include "EmptyBox.h"
#include "StagePetNode.h"
#include "StagePanelUtil.h"
#include "MainScene.h"
#include "StageSceneState.h"
#include "StageTarget.h"
#include "StageTargetView.h"
#include "CommonMacros.h"
#include "StageDataMgr.h"
#include "CCFunctionAction.h"
#include "StageScene.h"
#include "StarsController.h"
#include "StarViewNode.h"

USING_NS_CC;
using namespace std;
using namespace CommonUtil;
StageUiLayer::StageUiLayer()
{
	m_stateOwner = StageScene::theScene()->getStateOwner();
}

StageUiLayer::~StageUiLayer(void)
{
}

StageUiLayer *StageUiLayer::create()
{
	StageUiLayer* layer = new StageUiLayer();
	layer->init();
	layer->autorelease();
	return layer;
}

void StageUiLayer::onEnter()
{
	CCLayer::onEnter();
	StageDataMgr::theMgr()->addView(this);
	StarsController::theModel()->addView(this);
	StageLayersMgr::theMgr()->addLayer(this);
}

void StageUiLayer::onExit()
{
	CCLayer::onExit();
	StageDataMgr::theMgr()->removeView(this);
	StarsController::theModel()->removeView(this);
	StageLayersMgr::theMgr()->removeLayer(this);
}

bool StageUiLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	auto winSize = CCDirector::sharedDirector()->getWinSize();

	m_bottomUi = UiLayout::create("layout/stage_bottom.xml");
	m_bottomUi->setAnchorPoint(ccp(0, 0));
	m_bottomUi->setPosition(ccp(0, 0));
	m_bottomUi->setMenuTouchPriority(kStageUiTouchPriority);
	addChild(m_bottomUi);

	m_topUi = UiLayout::create("layout/stage_top.xml");
	m_topUi->setAnchorPoint(ccp(0, 1));
	m_topUi->setPosition(ccp(0, winSize.height));
	m_topUi->setMenuTouchPriority(kStageUiTouchPriority);
	addChild(m_topUi);


	initTopUi();
	initPets();
	initBottomUi();

    return true;
}

void StageUiLayer::initTopUi()
{
	int targetBoxIds[] = { 18, 19, 20 };
	auto target = StarsController::theModel()->getStageTarget();
	auto leftTarget = target->getEraseStarsLeft();
	assert(leftTarget.size() <= 3);
	for (size_t i = 0; i < leftTarget.size(); ++i)
	{
		StageTargetView *view = StageTargetView::create(leftTarget[i]);
		auto node = dynamic_cast<EmptyBox *>((m_topUi->getChildById(targetBoxIds[i])));
		node->setNode(view);
	}
	
	onStepsChanged();
	onScoreChanged();
}

void StageUiLayer::initPets()
{
	int uiIds[] = { 10, 11, 12, 13};
	auto ids = PetManager::petMgr()->getCurPetIds();
	assert(ids.size() <= 4);
	for (size_t i = 0; i < ids.size(); ++i)
	{
		StagePetNode *petNode = StagePetNode::create(ids[i], kStageUiTouchPriority);
		petNode->setTouchHandle(bind(&StageUiLayer::handlePetClicked, this, placeholders::_1));
		auto node = dynamic_cast<EmptyBox *>((m_topUi->getChildById(uiIds[i])));
		node->setNode(petNode);
		node->setAnchorPoint(ccp(0.5f, 0.5f));
		m_petViews[ids[i]] = petNode;
	}
}

void StageUiLayer::initBottomUi()
{
	auto closeBtn = dynamic_cast<CCMenuItem *>((m_bottomUi->getChildById(2)));
	closeBtn->setTarget(this, menu_selector(StageUiLayer::onPauseBtnClicked));

	for (int i = kPropReorder; i < kPorpTypeAmount; i++)
	{
		auto box = dynamic_cast<EmptyBox *>((m_bottomUi->getChildById(12 + i)));
		auto node = PropItemView::create(i, kStageUiTouchPriority);
		node->setTouchHandle(bind(&StageUiLayer::handlePropsItemClicked, this, placeholders::_1));
		node->setAnchorPoint(ccp(0.5f, 0.5f));
		box->setNode(node);
	}
}

void StageUiLayer::showGameOverHint()
{
	//game over hint
	CCSprite *sp = CCSprite::create("stage_clear.png");
	this->addChild(sp);
}

void StageUiLayer::handlePetClicked(int petId)
{
	m_stateOwner->clickPet(petId);
}

void StageUiLayer::showPetsSkillPanel()
{
	StagePetSkillPanel *panel = StagePetSkillPanel::create(kStageUiTouchPriority - 1);
	auto node = dynamic_cast<EmptyBox *>((m_topUi->getChildById(14)));
	node->setNode(panel);
	node->setAnchorPoint(ccp(0, 1));
}

void StageUiLayer::onStepsChanged()
{
	auto stageInfo = StageDataMgr::theMgr();
	int leftStep = stageInfo->getLeftSteps();
	CCLabelAtlas *stepLabel = dynamic_cast<CCLabelAtlas *>(m_topUi->getChildById(17));
	stepLabel->setString(intToStr(leftStep));
}

void StageUiLayer::onScoreChanged()
{
	auto stageInfo = StageDataMgr::theMgr();
	int curScore = stageInfo->getCurScore();
	auto stageTarget = StarsController::theModel()->getStageTarget();
	int targetScore = stageTarget->getTargetScore();

	CCLabelAtlas * curScoreLabel = dynamic_cast<CCLabelAtlas *>(m_topUi->getChildById(15));
	string str = intToStr(curScore);
	str += ";";
	str += intToStr(targetScore);
	
	curScoreLabel->setString(str.c_str());
}

void StageUiLayer::onCoinsChanged()
{

}

void StageUiLayer::onGameOver(int isWon)
{
	CCNode *node = NULL;
	if (isWon)
	{
		MainScene::theScene()->showPanel(kStageWinPanel);
	}
	else
	{
		MainScene::theScene()->showPanel(kStageFailPanel);

	}
	
}

void StageUiLayer::onPauseBtnClicked(CCObject *pSender)
{
	MainScene::theScene()->showDialog(PauseDialog::create());
}

void StageUiLayer::showChangeColorPanel(const LogicGrid &grid)
{
	auto *panel = ChangeStarColorPanel::create(kStageUiTouchPriority - 1);
	panel->setCallback([=](int color)
	{
		PropManager::propMgr()->usePropBrush(grid, color);
		m_stateOwner->enterNormalState();
	});

	panel->setAnchorPoint(ccp(0.5f, 1));
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	panel->setPosition(ccpMult(winSize, 0.5f));

	addChild(panel);
}

void StageUiLayer::handlePropsItemClicked(int type)
{
	if (type == kPropReorder)
	{
		PropManager::propMgr()->usePropReorder();
	}
	else
	{
		m_stateOwner->enterPropsClickState(type);
	}
}

void StageUiLayer::onNormalStarErased(cocos2d::CCPoint pos, int color)
{
	const static float kDuration = 0.8f;
	for (auto iter = m_petViews.begin(); iter != m_petViews.end(); ++iter)
	{
		int petId = iter->first;
		auto petView = iter->second;
		if (petView->getColor() == color)
		{
			auto config = DataManagerSelf->getStarsColorConfig(color);
			auto resPath = config.colorStarRes;
			CCSprite *starSpr = CCSprite::create(resPath.c_str());
			addChild(starSpr);
			starSpr->setPosition(pos);

			auto func = CCFunctionAction::create([=]()
			{
				starSpr->removeFromParent();
				int oldEnergy = PetManager::petMgr()->getPetById(petId)->getPetData().energy;
				int value = DataManagerSelf->getSystemConfig().starPetEnergy;
				PetManager::petMgr()->addPetEnergy(petId, value);
				petView->showSkillEnergyAciton(oldEnergy);
			});
			auto targetPos = petView->getParent()->convertToWorldSpace(petView->getPosition());
			auto move = CCEaseExponentialIn::create(CCMoveTo::create(kDuration, targetPos));
			auto scaleTo = CCScaleTo::create(kDuration, 0.5f);
			auto rotateBy = (CCRotateBy::create(kDuration, 360 * 10));
			starSpr->runAction(CCSequence::create(
				CCSpawn::create(move, scaleTo, rotateBy, NULL),
				func, NULL));
		}
	}
}

void StageUiLayer::onHighLightPets(const std::vector<int> &petIds)
{
	for (auto iter = m_petViews.begin(); iter != m_petViews.end(); ++iter)
	{
		if (find(petIds.begin(), petIds.end(), iter->first) != petIds.end())
		{
			//隐藏需要高亮的宠物,在stagemasklayer里高亮宠物
			iter->second->setVisible(false);
		}
	}
}

unordered_map<int, cocos2d::CCPoint> StageUiLayer::getPetViewsInfo()
{
	unordered_map<int, CCPoint> info;
	for (auto iter = m_petViews.begin(); iter != m_petViews.end(); ++iter)
	{
		auto petView = iter->second;
		auto pos = petView->getParent()->convertToWorldSpace(petView->getPosition());
		info[iter->first] = pos;
	}
	return info;
}

void StageUiLayer::onToNormalState()
{
	//显示pets
	for (auto iter = m_petViews.begin(); iter != m_petViews.end(); ++iter)
	{
		iter->second->setVisible(true);
	}
}

void StageUiLayer::showPetSpreadStarsAction(int petId, const StarAttr &attr, function<void()> callback)
{
	auto iter = m_petViews.find(petId);
	if (iter != m_petViews.end())
	{
		static const float kDutation = 0.3f;

		auto starNode = StarsController::theModel()->getStarNode(attr.grid);
		auto starView = starNode->getView();
		auto targetPos = starView->getParent()->convertToWorldSpace(starView->getPosition());

		auto tempNode = StarNode::createNodeFatory(attr);
		auto petView = iter->second;
		auto sourcePos = petView->getParent()->convertToWorldSpace(petView->getPosition());

		CCSprite *starImg = CCSprite::create(tempNode->getResPath().c_str());
		starImg->setPosition(sourcePos);
		addChild(starImg);
		auto moveTo = CCMoveTo::create(kDutation, targetPos);
		auto func = CCFunctionAction::create([=]()
		{
			starImg->removeFromParent();
			if (callback) callback();
		});
		starImg->runAction(CCSequence::create(CCEaseExponentialInOut::create(moveTo), func, NULL));
	}
}