#include "MenuScene.h"
#include "UiLayout.h"
USING_NS_CC;
using namespace std;

CCScene *MenuScene::scene()
{
	CCScene *scene = CCScene::create();
	MenuScene *layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}

void MenuScene::onEnter()
{
	CCLayer::onEnter();
}

void MenuScene::onExit()
{
	CCLayer::onExit();
}

bool MenuScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	m_mainLayout = UiLayout::create("layout/main_menu.xml");
	addChild(m_mainLayout);

	m_settingLayout = UiLayout::create("layout/main_menu_setting.xml");
	m_settingLayout->setAnchorPoint(ccp(0, 0));
	m_settingLayout->setPosition(ccp(0, 0));
	addChild(m_settingLayout);

	initMainLayout();
	initSettingLayout();
	return true;
}

void MenuScene::initMainLayout()
{
	CCMenuItem * normalBtn= dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(6)));
	normalBtn->setTarget(this, menu_selector(MenuScene::toNormalGame));

	CCMenuItem *treasureBtn = dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(7)));
	treasureBtn->setTarget(this, menu_selector(MenuScene::toTreasureGame));

	CCMenuItem *drawLotteryBtn = dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(8)));
	drawLotteryBtn->setTarget(this, menu_selector(MenuScene::drawLottery));

	CCMenuItem *toPetBtn = dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(9)));
	toPetBtn->setTarget(this, menu_selector(MenuScene::toPetPanel));
}

void MenuScene::initSettingLayout()
{
	CCMenuItem *settingBtn = dynamic_cast<CCMenuItem *>((m_settingLayout->getChildById(1)));
	settingBtn->setTarget(this, menu_selector(MenuScene::toSetting));

	CCMenuItem *muteBtn = dynamic_cast<CCMenuItem *>((m_settingLayout->getChildById(2)));
	muteBtn->setTarget(this, menu_selector(MenuScene::toMute));

	CCMenuItem *helpBtn = dynamic_cast<CCMenuItem *>((m_settingLayout->getChildById(3)));
	helpBtn->setTarget(this, menu_selector(MenuScene::toHelpPanel));
	
	
}

void MenuScene::toNormalGame(CCObject* pSender)
{
	CCMessageBox("toNormalGame", "title");
}

void MenuScene::toTreasureGame(CCObject* pSender)
{
	CCMessageBox("toTreasureGame", "title");
}

void MenuScene::drawLottery(cocos2d::CCObject* pSender)
{
	CCMessageBox("drawLottery", "title");
}

void MenuScene::toPetPanel(cocos2d::CCObject* pSender)
{
	CCMessageBox("toPetPanel", "title");

}

void MenuScene::toSetting(cocos2d::CCObject* pSender)
{
	CCMessageBox("toSetting", "title");

}

void MenuScene::toMute(cocos2d::CCObject* pSender)
{
	CCMessageBox("toMute", "title");

}

void MenuScene::toHelpPanel(cocos2d::CCObject* pSender)
{
	CCMessageBox("toHelpPanel", "title");

}
