#include "PetEntity.h"
#include "PetSkill.h"
#include "PetSavingHelper.h"
#include "StageOperator.h"
#include "CommonMacros.h"
#include "UserInfo.h"
PetEntity::PetEntity(int petId)
{
	//上次保存的宠物数据
	m_data = PetSavingHelper::getPetState(petId);

	refreshPetData();
}

PetEntity::~PetEntity()
{
}

void PetEntity::refreshPetData()
{
	m_data.energy = 0;

	auto petRes = DataManagerSelf->getPetResConfig(m_data.petId);
	m_data.petImgRes = petRes.petImgRes;
	m_data.petSkillRes = petRes.skillRes;
	m_data.petAnimationRes = petRes.petAnimationRes;
	m_data.petNameRes = petRes.petNameRes;

	auto commonData = DataManagerSelf->getPetCommonConfig(m_data.commonid);
	int level = m_data.level;
	m_data.maxEnergy = (level > 0 ? commonData.maxEnergy[level - 1] : 0);
	m_data.skillPower = (level > 0 ? commonData.skillPower[level - 1] : 0);
	m_data.foodToUpgrade = (level > 0 ? commonData.foodToUpgrade[level - 1] : 0);
	m_data.skillTarget = commonData.skillTarget;
}

PetEntity *PetEntity::PetFactory(int petId)
{
	auto data = PetSavingHelper::getPetState(petId);
	int petType = data.commonid;
	int petColor = data.color;
	switch (data.commonid)
	{
	case kPetRat:
		return new PetRat(petId);
	case kPetOx:
		return new PetOx(petId);
	case kPetTiger:
		return new PetTiger(petId);
	case kPetRabbit:
		return new PetRabbit(petId);
	case kPetDragon:
		return new PetDragon(petId);
	case kPetSnake:
		return new PetSnake(petId);
	case kPetHorse:
		return new PetHorse(petId);
	case kPetGoat:
		return new PetGoat(petId);
	case kPetMonkey:
		return new PetMonkey(petId);
	case kPetRooster:
		return new PetRooster(petId);
	case kPetDog:
		return new PetDog(petId);
	case kPetPig:
		return new PetPig(petId);
	default:
		assert(false && "no this kind of pet");
		return NULL;
	}
}

bool PetEntity::isMaxLevel()
{
	return m_data.level == MAX_PET_LEVEL;
}

void PetEntity::upgrade()
{
	int foodNum = UserInfo::theInfo()->getFood();
	int diamondNum = UserInfo::theInfo()->getDiamond();
	if (isMaxLevel()) return;

	int foodCost = m_data.foodToUpgrade;
	if (foodNum >= foodCost)
	{
		UserInfo::theInfo()->setFood(foodNum - foodCost);
	}
	else if (diamondNum >= foodCost)
	{
		UserInfo::theInfo()->setDiamond(diamondNum - foodCost);
	}

	m_data.level++;
	refreshPetData();
	PetSavingHelper::setPetState(m_data);
}
//////////////////////////////////////////////////////////////////////////////
void PetRat::skillInit()
{

}

void PetRat::toStarSkill(const LogicGrid &grid)
{
	StageOp->eraseStars(getStarsOnRow(grid, m_data.skillPower));
}

void PetOx::toStarSkill(const LogicGrid &grid)
{
	StageOp->eraseStars(getStarsOnColumn(grid, m_data.skillPower));
}

void PetTiger::noTargetSkill()
{
	StageOp->addSteps(m_data.skillPower);
}

void PetRabbit::noTargetSkill()
{
	StageOp->randomChangeColor(m_data.color, m_data.skillPower);
}

void PetDragon::noTargetSkill()
{
	auto info = StageModel::theModel()->getStageInfo();
	info->setNextScoreBonus(m_data.skillPower);
}

void PetSnake::toStarSkill(const LogicGrid &grid)
{
	StageOp->eraseSameColorStars(grid, m_data.skillPower);
}

void PetHorse::noTargetSkill()
{
	StageOp->randomReplaceToDiamond(m_data.skillPower);
}

void PetGoat::noTargetSkill()
{
	StageOp->randomErase(m_data.skillPower);
}

void PetMonkey::toPetSkill(int petId)
{
	StageOp->addPetEnergy(petId, m_data.skillPower);
}

void PetRooster::noTargetSkill()
{

}

void PetDog::toPetSkill(int petId)
{

}

void PetPig::noTargetSkill()
{
	StageOp->randomReplaceToKey(m_data.skillPower);
}

