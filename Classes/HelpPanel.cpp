#include "HelpPanel.h"
#include "UiLayout.h"
USING_NS_CC;
using namespace std;

bool HelpPanel::init()
{
	m_layout = UiLayout::create("layout/main_menu_bottom.xml");
	auto size = m_layout->getContentSize();
	setContentSize(size);

	addChild(m_layout);

	initLayout();
	return true;
}

void HelpPanel::initLayout()
{
	/*
	CCMenuItem *leftPetBtn = dynamic_cast<CCMenuItem *>((m_layout->getChildById(6)));
	leftPetBtn->setTarget(this, menu_selector(HelpPanel::onLeftPetBtnClicked));
	*/
}

void HelpPanel::onLeftPetBtnClicked(cocos2d::CCObject* pSender)
{

}
