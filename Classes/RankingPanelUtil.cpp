#include "RankingPanelUtil.h"
#include "UiLayout.h"
#include "RankingModel.h"
#include "EmptyBox.h"
#include "DataManager.h"
#include "CommonUtil.h"
USING_NS_CC;
using namespace std;
using namespace CommonUtil;

bool RankingNameInputPanel::init()
{
	m_layout = UiLayout::create("layout/ranking_name_input.xml");
	initLayout();
	addChild(m_layout);

	setContentSize(m_layout->getContentSize());
	addMaskLayer();
	return true;
}

void RankingNameInputPanel::initLayout()
{
	CCMenuItem *confirmBtn = dynamic_cast<CCMenuItem *>((m_layout->getChildById(4)));
	confirmBtn->setTarget(this, menu_selector(RankingNameInputPanel::onConfirm));

	CCMenuItem *genNameBtn = dynamic_cast<CCMenuItem *>((m_layout->getChildById(3)));
	genNameBtn->setTarget(this, menu_selector(RankingNameInputPanel::onGenRandomName));

	refreshName("");
}

void RankingNameInputPanel::refreshName(std::string name)
{
	CCLabelTTF *nameLabel = dynamic_cast<CCLabelTTF *>((m_layout->getChildById(5)));
	nameLabel->setString(name.c_str());
}

void RankingNameInputPanel::onGenRandomName(cocos2d::CCObject* pSender)
{
	string name = RankingModel::theModel()->getRandomName();
	refreshName(name);
}

void RankingNameInputPanel::onConfirm(cocos2d::CCObject* pSender)
{
	removeFromParent();
}

//////////////////////////////////////////////////////////////////////////////
RankingNode* RankingNode::create(int id)
{
	RankingNode *node = new RankingNode(id);
	node->init();
	node->autorelease();
	return node;
}

bool RankingNode::init()
{
	m_layout = UiLayout::create("layout/ranking_node_common.xml");
	addChild(m_layout);
	setContentSize(m_layout->getContentSize());

	auto data = DataManagerSelf->getRankingConfig(m_id);
	CCLabelTTF *name = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(5));
	name->setString(data.name.c_str());

	CCLabelAtlas *rank = dynamic_cast<CCLabelAtlas *>(m_layout->getChildById(6));
	rank->setString(intToStr(data.id));
	return true;
}

//////////////////////////////////////////////////////////////////////////////
RankingOpponentNode* RankingOpponentNode::create()
{
	RankingOpponentNode *node = new RankingOpponentNode();
	node->init();
	node->autorelease();
	return node;
}

bool RankingOpponentNode::init()
{
	m_layout = UiLayout::create("layout/ranking_node_opponent.xml");
	addChild(m_layout);
	setContentSize(m_layout->getContentSize());

	CCLabelTTF *name = dynamic_cast<CCLabelTTF *>(m_layout->getChildById(5));
	name->setString("hellow");

	CCLabelAtlas *rank = dynamic_cast<CCLabelAtlas *>(m_layout->getChildById(6));
	rank->setString("100");
	return true;
}
//////////////////////////////////////////////////////////////////////////////
bool RankingOpponentUpgradePanel::init()
{
	m_layout = UiLayout::create("layout/ranking_opponet_upgrade.xml");
	initLayout();
	addChild(m_layout);

	setContentSize(m_layout->getContentSize());
	addMaskLayer();
	return true;
}

void RankingOpponentUpgradePanel::initLayout()
{
	CCMenuItem *confirmBtn = dynamic_cast<CCMenuItem *>((m_layout->getChildById(4)));
	confirmBtn->setTarget(this, menu_selector(RankingOpponentUpgradePanel::onConfirm));

	auto targetRank = dynamic_cast<EmptyBox *>((m_layout->getChildById(5)));
	targetRank->setNode(RankingNode::create(90));

	auto opponent = dynamic_cast<EmptyBox *>((m_layout->getChildById(6)));
	opponent->setNode(RankingOpponentNode::create());
	
	runAction(CCSequence::create(CCDelayTime::create(1.0f), 
		CCCallFunc::create(this, callfunc_selector(RankingOpponentUpgradePanel::doMoveAction)), NULL));

}

void RankingOpponentUpgradePanel::doMoveAction()
{
	auto targetRank = dynamic_cast<EmptyBox *>((m_layout->getChildById(5)));
	auto opponent = dynamic_cast<EmptyBox *>((m_layout->getChildById(6)));

	const float kDuration = 0.2f;
	CCPoint toPos1;
	CCPoint toPos2;
	toPos1 = ccp(targetRank->getPositionX(), opponent->getPositionY());
	toPos2 = ccp(opponent->getPositionX(), targetRank->getPositionY());

	targetRank->runAction(CCEaseBounceInOut::create(CCMoveTo::create(kDuration, toPos1)));
	opponent->runAction(CCEaseBounceInOut::create(CCMoveTo::create(kDuration, toPos2)));
}

void RankingOpponentUpgradePanel::onConfirm(cocos2d::CCObject* pSender)
{
	removeFromParent();
}