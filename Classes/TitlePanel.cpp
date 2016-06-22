#include "TitlePanel.h"
#include "MenuScene.h"
#include "UiLayout.h"
#include "CCFunctionAction.h"
#include "MainScene.h"
#include "CommonMacros.h"
#include "PackageScene.h"
USING_NS_CC;
using namespace std;
TitlePanel *TitlePanel::create(int touchPriority)
{
	auto panel = new TitlePanel(touchPriority);
	panel->init();
	panel->autorelease();
	return panel;
}

bool TitlePanel::init()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	setContentSize(winSize);

	m_topLayout = UiLayout::create("layout/common_title.xml");
	m_topLayout->setMenuTouchPriority(m_touchPriority);
	m_topLayout->setAnchorPoint(ccp(0, 1));
	m_topLayout->setPosition(ccp(0, winSize.height));
	addChild(m_topLayout);

	m_bottomLayout = UiLayout::create("layout/common_bottom.xml");
	m_bottomLayout->setMenuTouchPriority(m_touchPriority);
	m_bottomLayout->setAnchorPoint(ccp(0, 0));
	m_bottomLayout->setPosition(ccp(0, 0));
	addChild(m_bottomLayout);

	initTopLayout();
	initBottomLayout();
	return true;
}

void TitlePanel::initTopLayout()
{
	CCMenuItem *addStrengthBtn = dynamic_cast<CCMenuItem *>(m_topLayout->getChildById(9));
	addStrengthBtn->setTarget(this, menu_selector(TitlePanel::onAddStrengthBtnClicked));

	CCMenuItem *addDiamondBtn = dynamic_cast<CCMenuItem *>(m_topLayout->getChildById(6));
	addDiamondBtn->setTarget(this, menu_selector(TitlePanel::onAddDiamondBtnClicked));
}

void TitlePanel::initBottomLayout()
{
	CCMenuItem *backHomeBtn = dynamic_cast<CCMenuItem *>(m_bottomLayout->getChildById(2));
	backHomeBtn->setTarget(this, menu_selector(TitlePanel::onBackHomeBtnClicked));
}

void TitlePanel::onAddStrengthBtnClicked(cocos2d::CCObject* pSender)
{
	auto dialog = PackageDialog::create(kPackageStrength);
	MainScene::theScene()->addDialog(dialog);
}

void TitlePanel::onAddDiamondBtnClicked(cocos2d::CCObject* pSender)
{
	auto dialog = PackageDialog::create(kPackageDiamond);
	MainScene::theScene()->addDialog(dialog);
}

void TitlePanel::onBackHomeBtnClicked(cocos2d::CCObject* pSender)
{
	MainScene::theScene()->showPanel(kMainMenu);
}

void TitlePanel::setUiVisible(int who, bool isVisible)
{
	switch (who)
	{
	case kTitlePanelStrength:
		m_topLayout->getChildById(7)->setVisible(isVisible);
		m_topLayout->getChildById(8)->setVisible(isVisible);
		m_topLayout->getChildById(9)->setVisible(isVisible);
		m_topLayout->getChildById(10)->setVisible(isVisible);
		break;
	case kTitlePanelFood:
		m_topLayout->getChildById(1)->setVisible(isVisible);
		m_topLayout->getChildById(2)->setVisible(isVisible);
		m_topLayout->getChildById(12)->setVisible(isVisible);
		break;
	case kTitlePanelDiamond:
		m_topLayout->getChildById(4)->setVisible(isVisible);
		m_topLayout->getChildById(5)->setVisible(isVisible);
		m_topLayout->getChildById(6)->setVisible(isVisible);
		m_topLayout->getChildById(11)->setVisible(isVisible);
		break;
	case kTitlePanelBackHome:
		m_bottomLayout->getChildById(1)->setVisible(isVisible);
		break;
	default:
		break;
	}
}



