#include "StagePetNode.h"
#include "PetEntity.h"
#include "PetManager.h"
#include "UiLayout.h"
#include "EmptyBox.h"
#include "StagePetSkillIcon.h"
using namespace std;
USING_NS_CC;

StagePetNode::StagePetNode(int petId, int touchPriority)
: TouchNode(touchPriority)
, m_petId(petId)
{
	m_model = PetManager::petMgr()->getPetById(petId);
	assert(m_model);
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

	m_petAnimation = dynamic_cast<CCArmature *>(m_layout->getChildById(4));

	string path = m_model->getPetData().petAnimationRes;
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(path.c_str());

	int pos1 = path.rfind("/");
	int pos2 = path.rfind(".");
	string armatureName = path.substr(pos1 + 1, pos2 - pos1 - 1);

	m_petAnimation->init(armatureName.c_str());
	m_petAnimation->getAnimation()->play("standby");

	EmptyBox *box = dynamic_cast<EmptyBox *>(m_layout->getChildById(5));
	m_skillIcon = StagePetSkillIcon::create(m_petId);
	box->setNode(m_skillIcon);
}

bool StagePetNode::onTouchBegan(cocos2d::CCPoint pt, bool isInside)
{
	if (isInside)
	{
		m_petAnimation->getAnimation()->play("move");
		m_petAnimation->getAnimation()->setMovementEventCallFunc(this, SEL_MovementEventCallFunc(&StagePetNode::runNormalAction));
		if (m_touchHandle)
		{
			m_touchHandle(m_petId);
		}
		return true;
	}
	return false;

}

void StagePetNode::runNormalAction(CCArmature *, MovementEventType, const char *)
{
	m_petAnimation->getAnimation()->setMovementEventCallFunc(NULL, NULL);
	m_petAnimation->getAnimation()->play("standby");
}

int StagePetNode::getColor()
{
	return m_model->getPetData().color;
}

void StagePetNode::updateSkillEnergy()
{
	m_skillIcon->setVisible(true);
	m_skillIcon->refresh();
}
