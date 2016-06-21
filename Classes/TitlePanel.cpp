#include "TitlePanel.h"
#include "MenuScene.h"
#include "UiLayout.h"
#include "CCFunctionAction.h"
#include "BackgroundLayer.h"
USING_NS_CC;
using namespace std;
bool TitlePanel::init()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	setContentSize(winSize);

	BackgroundLayer *bk = BackgroundLayer::create();
	bk->setPosition(ccpMult(winSize, 0.5f));
	addChild(bk);

	m_topLayout = UiLayout::create("layout/common_title.xml");
	m_topLayout->setAnchorPoint(ccp(0, 1));
	m_topLayout->setPosition(ccp(0, winSize.height));
	addChild(m_topLayout);

	m_bottomLayout = UiLayout::create("layout/common_bottom.xml");
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

}

void TitlePanel::onAddDiamondBtnClicked(cocos2d::CCObject* pSender)
{

}

void TitlePanel::onBackHomeBtnClicked(cocos2d::CCObject* pSender)
{
	////CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, MenuScene::scene()));
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



