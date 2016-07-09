#include "StagePetNode.h"
#include "PetEntity.h"
#include "PetManager.h"
#include "UiLayout.h"
#include "EmptyBox.h"
#include "StagePetSkillIcon.h"
using namespace std;
USING_NS_CC;

StagePetNode::StagePetNode(int petId, int touchPriority)
: m_touchPriority(touchPriority)
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

void StagePetNode::onEnter()
{
	CCNode::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_touchPriority, true);
}

void StagePetNode::onExit()
{
	CCNode::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
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
	m_skillIcon->setVisible(false);
}

bool StagePetNode::isInside(CCPoint pt)
{
	auto pos = convertToNodeSpace(pt);
	auto size = getContentSize();
	CCRect rect(0, 0, size.width, size.height);
	return rect.containsPoint(pos);
}

bool StagePetNode::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (isInside(pTouch->getLocation()))
	{
		if (m_model->canUseSkill())
		{
			m_petAnimation->getAnimation()->play("move");
			m_petAnimation->getAnimation()->setMovementEventCallFunc(this, SEL_MovementEventCallFunc(&StagePetNode::runNormalAction));
			if (m_touchHandle)
			{
				m_touchHandle(m_petId);
			}
		}
		else
		{
			m_skillIcon->setVisible(true);
		}
		return true;
	}

	return false;
}

void StagePetNode::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (!isInside(pTouch->getLocation()))
	{
		m_skillIcon->setVisible(false);
	}
}

void StagePetNode::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	m_skillIcon->setVisible(false);
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
	m_skillIcon->refresh([=]()
	{
		m_skillIcon->setVisible(false);
	});
}
