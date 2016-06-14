#include "RankingScene.h"
#include "UiLayout.h"
#include "TitlePanel.h"

USING_NS_CC;
using namespace std;

CCScene* RankingScene::scene()
{
	CCScene *scene = CCScene::create();
	RankingScene *layer = RankingScene::create();
	scene->addChild(layer);
	return scene;
}

bool RankingScene::init()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();

	m_mainLayout = UiLayout::create("layout/pet_ui.xml");
	//addChild(m_mainLayout);

	auto titlePanel = TitlePanel::create();
	addChild(titlePanel);

	//initMainLayout();
	return true;
}

void RankingScene::initMainLayout()
{
	CCMenuItem *leftPetBtn = dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(6)));
	leftPetBtn->setTarget(this, menu_selector(RankingScene::onLeftPetBtnClicked));

	CCMenuItem *rightPetBtn = dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(5)));
	rightPetBtn->setTarget(this, menu_selector(RankingScene::onRigthPetBtnClicked));

	CCMenuItem *upgradeBtn = dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(8)));
	upgradeBtn->setTarget(this, menu_selector(RankingScene::onUpgradeBtnClicked));
}

void RankingScene::onLeftPetBtnClicked(cocos2d::CCObject* pSender)
{

}

void RankingScene::onRigthPetBtnClicked(cocos2d::CCObject* pSender)
{

}

void RankingScene::onUpgradeBtnClicked(cocos2d::CCObject* pSender)
{

}
