#include "PreStagePetSlot.h"
#include "UiLayout.h"
#include "EmptyBox.h"
#include "ListView.h"
#include "PetManager.h"
#include "ListPetView.h"
#include "PreStageModel.h"
USING_NS_CC;
using namespace std;

PreStagePetSlotNode *PreStagePetSlotNode::create(int petId)
{
	auto node = new PreStagePetSlotNode(petId);
	node->init();
	node->autorelease();
	return node;
}

bool PreStagePetSlotNode::init()
{
	auto pet = PetManager::petMgr()->getPetById(m_petId);
	if (pet)
	{
		auto path = pet->getPetData().petImgRes;
		CCSprite* icon = CCSprite::create(path.c_str());

		icon->ignoreAnchorPointForPosition(false);
		icon->setAnchorPoint(ccp(0, 0));
		addChild(icon);
		setContentSize(icon->getContentSize());
	}
	return true;
}

string PreStagePetSlotNode::getBgPath()
{
	auto pet = PetManager::petMgr()->getPetById(m_petId);
	string path;
	if (pet)
	{
		int color = pet->getPetData().color;
		path = DataManagerSelf->getPetColorConfig(color).preStageSlotBg;
	}
	return path;
}


/////////////////////////////////////////////////////////////////////
PreStagePetSlot *PreStagePetSlot::create(int petId)
{
	auto node = new PreStagePetSlot(petId);
	node->init();
	node->autorelease();
	return node;
}

void PreStagePetSlot::onEnter()
{
	CCNode::onEnter();
	PreStageModel::theModel()->addView(this);
}

void PreStagePetSlot::onExit()
{
	CCNode::onExit();
	PreStageModel::theModel()->removeView(this);
}

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
	m_listView = ListPetView::create(getContentSize());
	m_listView->setItemSelectedCallback(bind(&PreStagePetSlot::onSelectItemCallback, this, placeholders::_1));
	
	EmptyBox *box = dynamic_cast<EmptyBox *>((m_layout->getChildById(2)));
	box->setNode(m_listView);
	PreStageModel::theModel()->selectPet(m_curPetId, NOT_SELECT_PET_ID);
	refreshList();
}

void PreStagePetSlot::refreshList()
{
	auto petMgr = PetManager::petMgr();
	auto ids = PreStageModel::theModel()->getPetsCanSelect(m_curPetId);
	m_listView->clear();

	int curIndex = 0;
	for (size_t i = 0; i < ids.size(); ++i)
	{
		if (m_curPetId == ids[i])
		{
			curIndex = i;
		}
		auto node = PreStagePetSlotNode::create(ids[i]);
		m_listView->addNode(node);
	}
	m_listView->setCurItem(curIndex);
}

void PreStagePetSlot::onSelectItemCallback(int index)
{
	PreStagePetSlotNode *node = dynamic_cast<PreStagePetSlotNode *>(m_listView->getNode(index));
	int petId = node->getPetId();
	if (m_curPetId != petId)
	{
		int oldPetId = m_curPetId;
		m_curPetId = petId;
		PreStageModel::theModel()->selectPet(petId, oldPetId);
	}

	CCSprite *slotBg = dynamic_cast<CCSprite *>(m_layout->getChildById(1));
	slotBg->initWithFile(node->getBgPath().c_str());
}


void PreStagePetSlot::onPetSelect(int oldPetId)
{
	refreshList();
}

