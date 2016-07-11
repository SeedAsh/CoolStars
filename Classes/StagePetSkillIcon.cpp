#include "StagePetSkillIcon.h"
#include "PetManager.h"
#include "CCFunctionAction.h"
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
	auto mask = CCSprite::create("pet_skill_icon/jntb_mask.png");
	mask->setPosition(ccpMult(size, 0.5f));
	addChild(mask);
	setContentSize(size);

	m_progress = CCProgressTimer::create(CCSprite::create(iconPath.c_str()));
	m_progress->setType(kCCProgressTimerTypeRadial);
	m_progress->setPosition(ccpMult(size, 0.5f));
	addChild(m_progress);
	int maxEnergy = pet->getPetData().maxEnergy;
	setPercentage((float)pet->getPetData().energy / maxEnergy, false);

	return true;
}

void StagePetSkillIcon::setPercentage(float value, bool withAction, std::function<void()> callback)
{
	value = max(0, min(value * 100, 100));
	if (withAction)
	{
		static const float kDurainon = 0.5f;
		CCProgressTo *progressto = CCProgressTo::create(kDurainon, value);
		CCDelayTime *delay = CCDelayTime::create(1.5f);
		CCFunctionAction *func = CCFunctionAction::create(callback);
		m_progress->runAction(CCSequence::create(progressto, delay, func, NULL));
	}
	else
	{
		m_progress->setPercentage(value);
	}
}

void StagePetSkillIcon::runEnergyAddAction(int oldEnergy, std::function<void()> callback)
{
	auto pet = PetManager::petMgr()->getPetById(m_petId);
	int maxEnergy = pet->getPetData().maxEnergy;

	setPercentage((float)oldEnergy / maxEnergy, false);
	setPercentage((float)pet->getPetData().energy / maxEnergy, true, callback);
}