#include "PetEntity.h"
#include "SavingHelper.h"
#include "PetSkill.h"
PetEntity::PetEntity(int petId)
{
	//�ϴα���ĳ�������
	m_data = SavingHelper::theHelper()->getPetsData(petId);
	//��ȡͨ�ó��������
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


