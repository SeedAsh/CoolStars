#include "PreStagePetSlot.h"
#include "UiLayout.h"
#include "EmptyBox.h"
#include "ListView.h"
#include "PetManager.h"
#include "ListPetView.h"
#include "PreStageModel.h"
USING_NS_CC;
using namespace std;

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

	int lastIndex = ids.size() - 1;
	for (size_t i = 0; i < ids.size(); ++i)
	{
		m_itemsIndex.push_back(ids[i]);
		if (ids[i] == m_curPetId)
		{
			lastIndex = i;
		}

		auto pet = petMgr->getPetById(ids[i]);
		auto path = pet->getPetData().path;
		CCSprite* icon = CCSprite::create(path.c_str());
		icon->ignoreAnchorPointForPosition(false);
		icon->setAnchorPoint(ccp(0, 0));
		m_listView->addNode(icon);
	}

	if (!ids.empty())
	{
		m_listView->setCurItem(lastIndex);
		onSelectItemCallback(lastIndex);
	}
}

void PreStagePetSlot::onSelectItemCallback(int index)
{
	assert(index >= 0 && index < (int)m_itemsIndex.size());
	int petId = m_itemsIndex[index];
	PreStageModel::theModel()->selectPet(petId);
	m_curPetId = petId;
}

void PreStagePetSlot::onPetSelect()
{
//	refresh();
	
}