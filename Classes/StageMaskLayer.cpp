#include "StageMaskLayer.h"
#include "CommonMacros.h"
#include "DataManager.h"
#include "StarNode.h"
#include "StarViewNode.h"
#include "StageLayersMgr.h"
#include "StageScene.h"
#include "StagePetNode.h"
USING_NS_CC;
using namespace std;

StageMaskLayer::StageMaskLayer()
: m_maskMode(kMaskModeStar)
{

}

bool StageMaskLayer::init()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	setContentSize(winSize);

	CCLayerColor *mask = CCLayerColor::create(ccc4(0, 0, 0, 175));
	mask->setContentSize(winSize);
	addChild(mask);
	m_starsContainer = CCNode::create();
	addChild(m_starsContainer);
	m_petsContainer = CCNode::create();
	addChild(m_petsContainer);
	
	setVisible(false);
	return true;
}

void StageMaskLayer::onEnter()
{
	CCNode::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kStageMaskTouchPriority, true);
	StageLayersMgr::theMgr()->addLayer(this);
}

void StageMaskLayer::onExit()
{
	CCNode::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	StageLayersMgr::theMgr()->removeLayer(this);

}

bool StageMaskLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (!isVisible()) return false;

	setVisible(false);
	auto pos = convertToNodeSpace(pTouch->getLocation());
	for (size_t i = 0; i < m_stars.size(); ++i)
	{
		auto node = m_stars[i];
		if (node->boundingBox().containsPoint(pos))
		{
			return false;
		}
	}

	auto stateOwner = StageScene::theScene()->getStateOwner();
	stateOwner->enterNormalState();
	return true;
}

void StageMaskLayer::onHighLightStars(int color)
{
	m_maskMode = kMaskModeStar;
	m_starsContainer->removeAllChildren();
	m_stars.clear();

	setVisible(true);
	auto nodes = StarsController::theModel()->getStarNodes();
	for (size_t i = 0; i < nodes.size(); ++i)
	{
		auto attr = nodes[i]->getAttr();
		if (attr.type == kColorStar && attr.color == color)
		{
			auto view = nodes[i]->getView();
			auto resPath = nodes[i]->getResPath();
			auto pos = view->getParent()->convertToWorldSpace(view->getPosition());
			CCSprite *starSpr = CCSprite::create(resPath.c_str());
			starSpr->setPosition(pos);
			m_starsContainer->addChild(starSpr);
			m_stars.push_back(starSpr);
		}
	}
}

void StageMaskLayer::initPetViewsInfo(std::unordered_map<int, cocos2d::CCPoint> info)
{
	m_petsInfo = info;
}

void StageMaskLayer::onHighLightPets(const std::vector<int> &petIds)
{	
	m_maskMode = kMaskModePet;

	m_petsContainer->removeAllChildren();

	setVisible(true);
	for (size_t i = 0; i < petIds.size(); ++i)
	{
		int tempId = petIds[i];
		auto iter = m_petsInfo.find(tempId);
		if (iter != m_petsInfo.end())
		{
			StagePetNode *petNode = StagePetNode::create(tempId, kStageMaskTouchPriority - 1);
			petNode->setPosition(iter->second);
			petNode->setTouchHandle([=](int petId)
			{
				auto stateOwner = StageScene::theScene()->getStateOwner();
				stateOwner->clickPet(petId);
				setVisible(false);
			});
			m_petsContainer->addChild(petNode);
		}

	}
}