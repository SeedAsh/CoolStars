#include "StagePetSkillIcon.h"
#include "PetManager.h"
USING_NS_CC;
using namespace std;

StagePetSkillIcon *StagePetSkillIcon::create(int petId)
{
	StagePetSkillIcon *icon = new StagePetSkillIcon(petId);
	icon->init();
	icon->autorelease();
	return icon;
}

bool StagePetSkillIcon::init()
{
	auto pet = PetManager::petMgr()->getPetById(m_petId);
	auto iconPath = pet->getPetData().petSkillRes;

	auto spr = CCSprite::create(iconPath.c_str());
	auto size = spr->getContentSize();
	spr->setPosition(ccpMult(size, 0.5f));
	addChild(spr);
	setContentSize(size);

	m_progress = CCProgressTimer::create(CCSprite::create("pet_skill_icon/jntb_mask.png"));
	m_progress->setType(kCCProgressTimerTypeRadial);
	m_progress->setReverseProgress(false);
	m_progress->setPosition(ccpMult(size, 0.5f));
	addChild(m_progress);
	setPercentage(pet->getPetData().energy, false);

	return true;
}

void StagePetSkillIcon::setPercentage(int value, bool withAction)
{
	value = max(0, min(100 - value, 100));
	if (withAction)
	{
		static const float kDurainon = 0.5f;
		CCProgressTo *t = CCProgressTo::create(kDurainon, value);
		m_progress->runAction(t);
	}
	else
	{
		m_progress->setPercentage(value);
	}
}

void StagePetSkillIcon::refresh()
{
	auto pet = PetManager::petMgr()->getPetById(m_petId);
	setPercentage(pet->getPetData().energy, true);
}