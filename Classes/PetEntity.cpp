#include "PetEntity.h"
#include "PetSkill.h"
#include "PetSavingHelper.h"
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
	auto commonData = DataManagerSelf->getCommonPetsConfig(m_data.commonid);

	m_data.petResPath = commonData.petResPaths[m_data.color - 1];
	m_data.skillResPath = commonData.skillResPath;
	
	int level = m_data.level;
	m_data.maxEnergy = (level > 0 ? commonData.maxEnergy[level - 1] : 0);
	m_data.skillPower = (level > 0 ? commonData.skillPower[level - 1] : 0);
	m_data.foodToUpgrade = (level > 0 ? commonData.foodToUpgrade[level - 1] : 0);
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
//////////////////////////////////////////////////////////////////////////////
void PetRat::useSkill()
{
	
}

void PetOx::useSkill()
{

}

void PetTiger::useSkill()
{

}

void PetRabbit::useSkill()
{

}

void PetDragon::useSkill()
{

}

void PetSnake::useSkill()
{

}

void PetHorse::useSkill()
{

}

void PetGoat::useSkill()
{

}

void PetMonkey::useSkill()
{

}

void PetRooster::useSkill()
{

}

void PetDog::useSkill()
{

}

void PetPig::useSkill()
{

}

