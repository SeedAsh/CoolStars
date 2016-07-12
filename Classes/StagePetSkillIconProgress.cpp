#include "StagePetSkillIconProgress.h"
#include "PetManager.h"
#include "CCFunctionAction.h"
USING_NS_CC;
using namespace std;
StagePetSkillIconProgress *StagePetSkillIconProgress::create(int petId)
{
	StagePetSkillIconProgress *progress = new StagePetSkillIconProgress(petId);
	progress->init();
	progress->autorelease();
	return progress;
}

bool StagePetSkillIconProgress::init()
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

	//不能直接用PetSkillIcon,因为CCProgressTimer只是支持CCSprite
	int commandId = pet->getPetData().commonid;
	char str[100] = { 0 };
	auto numSize = CCSprite::create("num/ty_ziti6.png")->getContentSize();
	if (commandId == kPetDragon)
	{
		sprintf(str, ";%d", pet->getPetData().skillPower);
		auto pLabel = CCLabelAtlas::create(str, "num/ty_ziti6.png", numSize.width / 12, numSize.height, '0');
		pLabel->setAnchorPoint(ccp(0.5f, 0.5f));
		pLabel->setPosition(ccpMult(size, 0.5));
		addChild(pLabel);
	}
	else if (commandId == kPetTiger)
	{
		sprintf(str, ":%d", pet->getPetData().skillPower);
		auto pLabel = CCLabelAtlas::create(str, "num/ty_ziti6.png", numSize.width / 12, numSize.height, '0');
		pLabel->setAnchorPoint(ccp(0.5f, 0.5f));
		pLabel->setPosition(ccpMult(size, 0.5));
		addChild(pLabel);
	}

	return true;
}

void StagePetSkillIconProgress::setPercentage(float value, bool withAction, std::function<void()> callback)
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

void StagePetSkillIconProgress::runEnergyAddAction(int oldEnergy, std::function<void()> callback)
{
	auto pet = PetManager::petMgr()->getPetById(m_petId);
	int maxEnergy = pet->getPetData().maxEnergy;

	setPercentage((float)oldEnergy / maxEnergy, false);
	setPercentage((float)pet->getPetData().energy / maxEnergy, true, callback);
}