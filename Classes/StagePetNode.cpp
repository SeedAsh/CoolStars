#include "StagePetNode.h"
#include "PetEntity.h"
#include "PetManager.h"
#include "UiLayout.h"
using namespace std;
USING_NS_CC;

StagePetNode::StagePetNode(int petId)
	: m_petId(petId)
{
	m_model = PetManager::petMgr()->getPetById(petId);
	assert(m_model);
}

bool StagePetNode::onTouchBegan(cocos2d::CCPoint pt, bool isInside)
{
	if (isInside)
	{
		runScale();
		if (m_skillScanHandle)
		{
			m_skillScanHandle();
		}
		return true;
	}
	return false;
	
}

StagePetNode *StagePetNode::create(int petId)
{
	auto view = new StagePetNode(petId);
	view->init();
	view->autorelease();
	return view;
}

bool StagePetNode::init()
{
	string iconPath = m_model->getPetData().petResPath;

	m_layout = UiLayout::create("layout/stage_pet_node.xml");
	auto size = m_layout->getContentSize();
	addChild(m_layout);

	auto bottomSpr = dynamic_cast<CCSprite *>(m_layout->getChildById(1));
	auto petSpr = dynamic_cast<CCSprite *>(m_layout->getChildById(2));
	petSpr->initWithFile(iconPath.c_str());
	m_layout->getChildById(3)->setVisible(false);

	setContentSize(size);
	setAnchorPoint(ccp(0.5f, 0.5f));
	
	CCLayerColor *mask = CCLayerColor::create(ccc4(255, 0, 0, 75));
	mask->setContentSize(size);
	//addChild(mask);
	return true;
}
