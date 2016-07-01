#include "PetScene.h"
#include "UiLayout.h"
#include "MenuScene.h"
#include "TitlePanel.h"
#include "CommonMacros.h"
#include "MainScene.h"
#include "EmptyBox.h"
#include "PetView.h"
#include "PetManager.h"
#include "CommonUtil.h"

USING_NS_CC;
using namespace std;

const float PetScene::kBtnSelectedScale = 1.3f;
bool PetScene::init()
{
	setPanelId(kPetPanel);
	initColorPets();
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	setContentSize(winSize);

	auto titlePanel = TitlePanel::create(m_touchPriority);
	titlePanel->setUiVisible(kTitlePanelBackHome, false);
	addChild(titlePanel);

	m_mainLayout = UiLayout::create("layout/pet_ui.xml");
	m_mainLayout->setMenuTouchPriority(m_touchPriority);
	addChild(m_mainLayout);

	m_bottomLayout = UiLayout::create("layout/pet_ui_bottom.xml");
	m_bottomLayout->setMenuTouchPriority(m_touchPriority);
	m_bottomLayout->setAnchorPoint(ccp(0, 0));
	m_bottomLayout->setPosition(ccp(0, 0));
	addChild(m_bottomLayout);
	
	initMainLayout();
	initBottomLayout();

	return true;
}

void PetScene::initMainLayout()
{
	CCMenuItem *leftPetBtn = dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(6)));
	leftPetBtn->setTarget(this, menu_selector(PetScene::onLeftPetBtnClicked));

	CCMenuItem *rightPetBtn = dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(5)));
	rightPetBtn->setTarget(this, menu_selector(PetScene::onRigthPetBtnClicked));

	CCMenuItem *upgradeBtn = dynamic_cast<CCMenuItem *>((m_mainLayout->getChildById(8)));
	upgradeBtn->setTarget(this, menu_selector(PetScene::onUpgradeBtnClicked));
	
	CCPoint leftmost = m_mainLayout->getChildById(19)->getPosition();
	CCPoint center = m_mainLayout->getChildById(10)->getPosition();
	CCPoint rightmost = m_mainLayout->getChildById(20)->getPosition();
	m_moveHelper.init(leftmost, center, rightmost);
}

void PetScene::initBottomLayout()
{
	CCMenuItem *backBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(1)));
	backBtn->setTarget(this, menu_selector(PetScene::onBackBtnClicked));

	CCMenuItem *greenPetBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(2)));
	greenPetBtn->setTarget(this, menu_selector(PetScene::onGreenPetBtnClicked));

	CCMenuItem *purplePetBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(6)));
	purplePetBtn->setTarget(this, menu_selector(PetScene::onPurplePetBtnClicked));

	CCMenuItem *redPetBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(5)));
	redPetBtn->setTarget(this, menu_selector(PetScene::onRedPetBtnClicked));

	CCMenuItem *bluePetBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(3)));
	bluePetBtn->setTarget(this, menu_selector(PetScene::onBluePetBtnClicked));

	CCMenuItem *yellowPetBtn = dynamic_cast<CCMenuItem *>((m_bottomLayout->getChildById(4)));
	yellowPetBtn->setTarget(this, menu_selector(PetScene::onYellowPetBtnClicked));

	changePetsColor(kColorGreen);
	greenPetBtn->setScale(kBtnSelectedScale);
}

void PetScene::onLeftPetBtnClicked(cocos2d::CCObject* pSender)
{
	if (m_curColorPetIndex > 0)
	{
		m_curColorPetIndex--;

		int petId = m_colorPets[m_curPetColor][m_curColorPetIndex];
		auto view = PetView::create(petId);
		addChild(view, -1);
		m_moveHelper.moveLeft(view);

		refreshUi();
	}
}

void PetScene::onRigthPetBtnClicked(cocos2d::CCObject* pSender)
{
	if (m_curColorPetIndex < m_colorPets[m_curPetColor].size() - 1)
	{
		m_curColorPetIndex++;

		int petId = m_colorPets[m_curPetColor][m_curColorPetIndex];
		auto view = PetView::create(petId);
		addChild(view, -1);
		m_moveHelper.moveRight(view);

		refreshUi();
	};
}

void PetScene::onUpgradeBtnClicked(cocos2d::CCObject* pSender)
{
	int petId = m_colorPets[m_curPetColor][m_curColorPetIndex];
	auto pet = PetManager::petMgr()->getPetById(petId);
	pet->upgrade();
	refreshUi();
}

void PetScene::onGreenPetBtnClicked(cocos2d::CCObject* pSender)
{
	resetPetBtnsScale();
	CCMenuItem *btn = dynamic_cast<CCMenuItem *>(pSender);
	btn->setScale(kBtnSelectedScale);
	changePetsColor(kColorGreen);
}

void PetScene::onPurplePetBtnClicked(cocos2d::CCObject* pSender)
{
	resetPetBtnsScale();
	CCMenuItem *btn = dynamic_cast<CCMenuItem *>(pSender);
	btn->setScale(kBtnSelectedScale);
	changePetsColor(kColorPurple);
}

void PetScene::onRedPetBtnClicked(cocos2d::CCObject* pSender)
{
	resetPetBtnsScale();
	CCMenuItem *btn = dynamic_cast<CCMenuItem *>(pSender);
	btn->setScale(kBtnSelectedScale);
	changePetsColor(kColorRed);
}

void PetScene::onBluePetBtnClicked(cocos2d::CCObject* pSender)
{
	resetPetBtnsScale();
	CCMenuItem *btn = dynamic_cast<CCMenuItem *>(pSender);
	btn->setScale(kBtnSelectedScale);
	changePetsColor(kColorBlue);
}

void PetScene::onYellowPetBtnClicked(cocos2d::CCObject* pSender)
{
	resetPetBtnsScale();
	CCMenuItem *btn = dynamic_cast<CCMenuItem *>(pSender);
	btn->setScale(kBtnSelectedScale);
	changePetsColor(kColorYellow);
}

void PetScene::resetPetBtnsScale()
{
	int btnsId[5] = { 2, 3, 4, 5, 6 };
	for (int i = 0; i < 5; ++i)
	{
		m_bottomLayout->getChildById(btnsId[i])->setScale(1);
	}
}

void PetScene::onBackBtnClicked(cocos2d::CCObject* pSender)
{
	MainScene::theScene()->backPanel();
}

void PetScene::initColorPets()
{
	auto petMgr = PetManager::petMgr();
	auto petIds = petMgr->getOwnedPetIds();
	for (size_t i = 0; i < petIds.size(); ++i)
	{
		auto data = petMgr->getPetById(petIds[i])->getPetData();
		m_colorPets[data.color].push_back(petIds[i]);
	}
}

void PetScene::changePetsColor(int color)
{
	m_curPetColor = color;
	m_curColorPetIndex = 0;

	m_moveHelper.clearNodes();

	int size = m_colorPets[m_curPetColor].size();
	if (m_curColorPetIndex >= 0 && m_curColorPetIndex < size)
	{
		int petId = m_colorPets[m_curPetColor][m_curColorPetIndex];
		auto view = PetView::create(petId);
		addChild(view, -1);
		m_moveHelper.setCenterNode(view);
	}

	refreshUi();
}

void PetScene::refreshUi()
{
	int size = m_colorPets[m_curPetColor].size();
	m_mainLayout->setVisible(size != 0);

	if (m_curColorPetIndex >= 0 && m_curColorPetIndex < size)
	{
		int petId = m_colorPets[m_curPetColor][m_curColorPetIndex];

		auto data = PetManager::petMgr()->getPetById(petId)->getPetData();
		auto config = DataManagerSelf->getPetColorConfig(data.color);

		//等级图标
		CCSprite *lvImg = dynamic_cast<CCSprite *>(m_mainLayout->getChildById(13));
		lvImg->initWithFile(config.skillLvLabel.c_str());
		//宠物名字
		CCSprite *nameImg = dynamic_cast<CCSprite *>(m_mainLayout->getChildById(14));
		nameImg->initWithFile(data.petNameRes.c_str());
		//等级
		CCLabelAtlas *lvNum = dynamic_cast<CCLabelAtlas *>(m_mainLayout->getChildById(16));
		CCSprite *numRes = CCSprite::create(config.numRes.c_str());
		auto numResSize = numRes->getContentSize();
		lvNum->initWithString(CommonUtil::intToStr(data.level), config.numRes.c_str(), numResSize.width / 10, numResSize.height, '0');
	}

	refreshArrows();
	refreshUpgrdeCost();
}

void PetScene::refreshUpgrdeCost()
{
	if (m_colorPets[m_curPetColor].empty()) return;

	int foodNum = UserInfo::theInfo()->getFood();
	int diamondNum = UserInfo::theInfo()->getDiamond();
	int petId = m_colorPets[m_curPetColor][m_curColorPetIndex];
	auto pet = PetManager::petMgr()->getPetById(petId);
	if (pet->isMaxLevel())//宠物已经满级
	{
		m_mainLayout->getChildById(9)->setVisible(false);
		m_mainLayout->getChildById(18)->setVisible(false);
		m_mainLayout->getChildById(17)->setVisible(false);
		m_mainLayout->getChildById(8)->setVisible(false);
	}
	else
	{
		auto foodCost = pet->getPetData().foodToUpgrade;
		bool isFoodEnough = foodNum >= foodCost;

		m_mainLayout->getChildById(9)->setVisible(!isFoodEnough);
		m_mainLayout->getChildById(18)->setVisible(isFoodEnough);
		m_mainLayout->getChildById(17)->setVisible(true);
		m_mainLayout->getChildById(8)->setVisible(true);

		CCLabelAtlas *lvNum = dynamic_cast<CCLabelAtlas *>(m_mainLayout->getChildById(17));
		lvNum->setString(CommonUtil::intToStr(foodCost));
	}
}

void PetScene::refreshArrows()
{
	int size = m_colorPets[m_curPetColor].size();
	m_mainLayout->getChildById(6)->setVisible(m_curColorPetIndex > 0);
	m_mainLayout->getChildById(5)->setVisible(m_curColorPetIndex < size - 1);
}
