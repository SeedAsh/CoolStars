#include "StagePetNode.h"
#include "PetEntity.h"
#include "PetManager.h"
#include "UiLayout.h"
using namespace std;
USING_NS_CC;

StagePetNode::StagePetNode(int petId, int touchPriority)
: TouchNode(touchPriority)
, m_petId(petId)
{
	m_model = PetManager::petMgr()->getPetById(petId);
	assert(m_model);
}

bool StagePetNode::onTouchBegan(cocos2d::CCPoint pt, bool isInside)
{
	if (isInside)
	{
		runScale();
		if (m_touchHandle)
		{
			m_touchHandle(m_petId);
		}
		return true;
	}
	return false;
	
}

StagePetNode *StagePetNode::create(int petId, int touchPriority)
{
	auto view = new StagePetNode(petId, touchPriority);
	view->init();
	view->autorelease();
	return view;
}

bool StagePetNode::init()
{
	string iconPath = m_model->getPetData().petImgRes;

	m_layout = UiLayout::create("layout/stage_pet_node.xml");
	auto size = m_layout->getContentSize();
	addChild(m_layout);

	auto bottomSpr = dynamic_cast<CCSprite *>(m_layout->getChildById(1));
	auto petSpr = dynamic_cast<CCSprite *>(m_layout->getChildById(2));
	petSpr->initWithFile(iconPath.c_str());
	petSpr->setScale(size.width / petSpr->getContentSize().width);
	m_layout->getChildById(3)->setVisible(false);

	setContentSize(size);
	setAnchorPoint(ccp(0.5f, 0.5f));
	
	CCLayerColor *mask = CCLayerColor::create(ccc4(255, 0, 0, 75));
	mask->setContentSize(size);
	//addChild(mask);

	return true;
}
