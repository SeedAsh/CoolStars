#include "PetEntity.h"
#include "PetSkill.h"
#include "PetSavingHelper.h"
PetEntity::PetEntity(int petId)
{
	//�ϴα���ĳ�������
	m_data = PetSavingHelper::getPetState(petId);
	auto commonData = getMyCommonPetData();
	m_data.path = commonData.iconPaths[m_data.color - 1];
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



