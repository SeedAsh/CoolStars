#include "PackageScene.h"
#include "UiLayout.h"
#include "MenuScene.h"
#include "TitlePanel.h"

USING_NS_CC;
using namespace std;

PackageView *PackageView::create(int type)
{
	PackageView *view = new PackageView(type);
	view->init();
	view->autorelease();
	return view;
}

PackageView::PackageView(int type)
: m_type(type)
{

}

bool PackageView::init()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	setContentSize(winSize);

	auto titlePanel = TitlePanel::create();
	addChild(titlePanel);

	m_layout = UiLayout::create("layout/package_common.xml");
	m_layout->setAnchorPoint(ccp(0.5f, 0.5f));
	m_layout->setPosition(ccpMult(winSize, 0.5f));
	addChild(m_layout);
	
	initLayout();
	
	return true;
}

void PackageView::initLayout()
{
	CCMenuItem *cancelBtn = dynamic_cast<CCMenuItem *>((m_layout->getChildById(4)));
	cancelBtn->setTarget(this, menu_selector(PackageView::onCancelBtnClicked));

	CCMenuItem *buyBtn = dynamic_cast<CCMenuItem *>((m_layout->getChildById(5)));
	buyBtn->setTarget(this, menu_selector(PackageView::onBuyBtnClicked));
}

void PackageView::onCancelBtnClicked(cocos2d::CCObject* pSender)
{
	//CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(0.5f, MenuScene::scene()));

}

void PackageView::onBuyBtnClicked(cocos2d::CCObject* pSender)
{
	//CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(0.5f, MenuScene::scene()));

}

















CCScene* PackageScene::scene()
{
	CCScene *scene = CCScene::create();

	PackageView *view = PackageView::create(kPackageStep);
	scene->addChild(view);
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	
	return scene;

	PackageScene *layer = PackageScene::create();
	scene->addChild(layer);
	return scene;
}

bool PackageScene::init()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();

	m_mainLayout = UiLayout::create("layout/package_common.xml");
	//addChild(m_mainLayout);

	auto titlePanel = TitlePanel::create();
	addChild(titlePanel);

	//initMainLayout();
	return true;
}

void PackageScene::initMainLayout()
{
	CCMenuItem *leftPetBtn = dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(6)));
	leftPetBtn->setTarget(this, menu_selector(PackageScene::onLeftPetBtnClicked));

	CCMenuItem *rightPetBtn = dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(5)));
	rightPetBtn->setTarget(this, menu_selector(PackageScene::onRigthPetBtnClicked));

	CCMenuItem *upgradeBtn = dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(8)));
	upgradeBtn->setTarget(this, menu_selector(PackageScene::onUpgradeBtnClicked));
}

void PackageScene::onLeftPetBtnClicked(cocos2d::CCObject* pSender)
{

}

void PackageScene::onRigthPetBtnClicked(cocos2d::CCObject* pSender)
{

}

void PackageScene::onUpgradeBtnClicked(cocos2d::CCObject* pSender)
{

}
