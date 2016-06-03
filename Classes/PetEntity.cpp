#include "PetEntity.h"
#include "SavingHelper.h"
#include "PetSkill.h"
PetEntity::PetEntity(int petId)
{
	//上次保存的宠物数据
	m_data = SavingHelper::theHelper()->getPetsData(petId);
	//获取通用宠物的数据
	int skillId = getMyCommonPetData().skillId;
	m_skill = PetSkill::petSkillFactory(skillId);
}

PetEntity::~PetEntity()
{
	delete m_skill;
}

void PetEntity::useSkill()
{
	m_skill->doMagic();
}

const PetsConfig &PetEntity::getMyCommonPetData() const
{
	int commonPetId = m_data.commonid;
	return DataManagerSelf->getCommonPetsConfig(commonPetId);
}


