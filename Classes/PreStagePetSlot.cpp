#include "PreStagePetSlot.h"
#include "UiLayout.h"
#include "EmptyBox.h"
#include "ListView.h"
#include "PetManager.h"
#include "ListPetView.h"
#include "PreStageModel.h"
#define NOT_SELECT_PET 0
USING_NS_CC;
using namespace std;

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
	refresh();
}

void PreStagePetSlot::refresh()
{
	auto petMgr = PetManager::petMgr();
	auto ids = PreStageModel::theModel()->getPetsCanSelect();
	m_itemsIndex.clear();
	
	//没有宠物可选
	if (m_curPetId == NOT_SELECT_PET)
	{
		m_itemsIndex.push_back(NOT_SELECT_PET);
		CCSprite* icon = CCSprite::create("pets/black.png");
		icon->ignoreAnchorPointForPosition(false);
		icon->setAnchorPoint(ccp(0, 0));
		m_listView->addNode(icon);
		m_listView->setCurItem(0);
		return;
	}

	//有宠物可选
	int curIndex = 0;
	for (size_t i = 0; i < ids.size(); ++i)
	{
		m_itemsIndex.push_back(ids[i]);
		auto pet = petMgr->getPetById(ids[i]);
		if (m_curPetId == pet->getPetData().petId)
		{
			curIndex = i;
		}

		auto path = pet->getPetData().petImgRes;
		CCSprite* icon = CCSprite::create(path.c_str());
		icon->ignoreAnchorPointForPosition(false);
		icon->setAnchorPoint(ccp(0, 0));
		m_listView->addNode(icon);
	}
	m_listView->setCurItem(curIndex);
	onSelectItemCallback(curIndex);
}

void PreStagePetSlot::onSelectItemCallback(int index)
{
	assert(index >= 0 && index < (int)m_itemsIndex.size());
	int petId = m_itemsIndex[index];
	
	PreStageModel::theModel()->selectPet(petId, m_curPetId);
	m_curPetId = petId;
}

void PreStagePetSlot::onPetSelect()
{
//	refresh();
	
}