#include "PreStagePetSlot.h"
#include "UiLayout.h"
#include "EmptyBox.h"
#include "ListView.h"
#include "PetManager.h"
#include "ListPetView.h"
#include "PreStageModel.h"
#define NOT_SELECT_PET_ID 0
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

CCNode *PreStagePetSlot::getPetNode(const char* resPath)
{
	CCSprite* icon = CCSprite::create(resPath);

	icon->ignoreAnchorPointForPosition(false);
	icon->setAnchorPoint(ccp(0, 0));

	return icon;
}

void PreStagePetSlot::refresh()
{
	//这里处理不好  需要重构； listview 添加sort功能 应对添加和删减节点
	auto petMgr = PetManager::petMgr();
	auto ids = PreStageModel::theModel()->getPetsCanSelect();
	if (m_curPetId != NOT_SELECT_PET_ID)
	{
		ids.push_back(m_curPetId);
	}
	sort(ids.begin(), ids.end());
	m_petIdInList.clear();
	m_listView->clear();
	
	//list里至少有一个空的node,即没宠物可选
	//故list的数量为 宠物可选数量+1 
	CCNode *emptyNode = CCNode::create();
	m_listView->addNode(emptyNode);
	m_petIdInList.push_back(NOT_SELECT_PET_ID);

	int curIndex = 0;
	for (size_t i = 0; i < ids.size(); ++i)
	{
		m_petIdInList.push_back(ids[i]);
		auto pet = petMgr->getPetById(ids[i]);
		if (m_curPetId == pet->getPetData().petId)
		{
			curIndex = i + 1;
		}

		auto path = pet->getPetData().petImgRes;
		m_listView->addNode(getPetNode(path.c_str()));
	}
	m_listView->setCurItem(curIndex);
}

void PreStagePetSlot::onSelectItemCallback(int index)
{
	assert(index >= 0 && index <= (int)m_petIdInList.size());
	int petId = m_petIdInList[index];
	
	if (m_curPetId != petId)
	{
		int oldPetId = m_curPetId;
		m_curPetId = petId;
		PreStageModel::theModel()->selectPet(petId, oldPetId);

		auto pet = PetManager::petMgr()->getPetById(petId);
		if (pet)
		{
			CCSprite *slotBg = dynamic_cast<CCSprite *>(m_layout->getChildById(1));
			int color = pet->getPetData().color;
			auto path = DataManagerSelf->getStarsColorConfig(color).preStageSlotBg;
			slotBg->initWithFile(path.c_str());
		}
	}
}

void PreStagePetSlot::onPetSelect(int oldPetId)
{
	refresh();
}

