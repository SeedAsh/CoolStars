#include "PreStagePetSlot.h"
#include "UiLayout.h"
#include "EmptyBox.h"
#include "ListView.h"
#include "PetManager.h"
USING_NS_CC;
using namespace std;

bool PreStagePetSlot::init()
{
	m_layout = UiLayout::create("layout/pre_stage_pet_slot.xml");
	setContentSize(m_layout->getContentSize());
	addChild(m_layout);

	initLayout();
	return true;
}

void PreStagePetSlot::initLayout()
{
	ListView *listview = ListView::create(getContentSize());
	
	auto petMgr = PetManager::petMgr();
	auto ids = petMgr->getOwnedPetIds();
	for (size_t i = 0; i < ids.size(); ++i)
	{
		auto pet = petMgr->getPetById(ids[i]);
		auto path = pet->getPetData().path;
		CCSprite* icon = CCSprite::create(path.c_str());
		icon->ignoreAnchorPointForPosition(false);
		icon->setAnchorPoint(ccp(0, 0));
		listview->addNode(icon);
	}

	EmptyBox *box = dynamic_cast<EmptyBox *>((m_layout->getChildById(2)));
	box->setNode(listview);
}

void PreStagePetSlot::onLeftPetBtnClicked(cocos2d::CCObject* pSender)
{

}
