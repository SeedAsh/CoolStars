#include "PetEntity.h"
#include "PetSkill.h"
#include "PetSavingHelper.h"
PetEntity::PetEntity(int petId)
{
	//上次保存的宠物数据
	m_data = PetSavingHelper::getPetState(petId);
	auto commonData = getMyCommonPetData();
	m_data.path = commonData.iconPaths[m_data.color - 1];

}

PetEntity::~PetEntity()
{
}

void PetEntity::useSkill()
{
}

const PetsConfig &PetEntity::getMyCommonPetData() const
{
	int commonPetId = m_data.commonid;
	return DataManagerSelf->getCommonPetsConfig(commonPetId);
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

