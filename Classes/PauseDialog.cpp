#include "PauseDialog.h"
#include "UiLayout.h"
#include "MainScene.h"
#include "CommonMacros.h"

USING_NS_CC;
using namespace std;
PauseDialog::PauseDialog(void)
{

}

bool PauseDialog::init()
{
	m_layout = UiLayout::create("layout/package_pause.xml");
	
	setContentSize(m_layout->getContentSize());
	addMaskLayer();
	addChild(m_layout);
	initLayout();
    return true;
}

void PauseDialog::initLayout()
{
	CCMenuItem *resumeBtn = dynamic_cast<CCMenuItem *>((m_layout->getChildById(3)));
	resumeBtn->setTarget(this, menu_selector(PauseDialog::onResume));

	CCMenuItem *muteBtn = dynamic_cast<CCMenuItem *>((m_layout->getChildById(4)));
	muteBtn->setTarget(this, menu_selector(PauseDialog::onMute));

	CCMenuItem *backBtn = dynamic_cast<CCMenuItem *>((m_layout->getChildById(5)));
	backBtn->setTarget(this, menu_selector(PauseDialog::onBackHome));

	CCMenuItem *purchaseBtn = dynamic_cast<CCMenuItem *>((m_layout->getChildById(6)));
	purchaseBtn->setTarget(this, menu_selector(PauseDialog::onPurchase));
}

void PauseDialog::onResume(CCObject* pSender)
{
	removeFromParent();
}

void PauseDialog::onMute(CCObject* pSender)
{

}

void PauseDialog::onBackHome(CCObject* pSender)
{
	removeFromParent();
	MainScene::theScene()->showPanel(kMainMenu);
}

void PauseDialog::onPurchase(CCObject* pSender)
{

}

