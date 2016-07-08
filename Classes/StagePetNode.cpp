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
	m_layout = UiLayout::create("layout/stage_pet_node.xml");
	auto size = m_layout->getContentSize();
	addChild(m_layout);
	initLayout();
	setContentSize(size);
	setAnchorPoint(ccp(0.5f, 0.5f));
	
	CCLayerColor *mask = CCLayerColor::create(ccc4(255, 0, 0, 75));
	mask->setContentSize(size);
	//addChild(mask);

	return true;
}

void StagePetNode::initLayout()
{
	m_layout->getChildById(3)->setVisible(false);

	CCArmature *pet = dynamic_cast<CCArmature *>(m_layout->getChildById(4));

	string path = m_model->getPetData().petAnimationRes;
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(path.c_str());

	int pos1 = path.rfind("/");
	int pos2 = path.rfind(".");
	string armatureName = path.substr(pos1 + 1, pos2 - pos1 - 1);

	pet->init(armatureName.c_str());
	pet->getAnimation()->play("standby");
}