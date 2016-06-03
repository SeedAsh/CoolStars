#ifndef __PETENTITY_H__
#define __PETENTITY_H__
#include "DataManager.h"

class PetSkill;

struct PetData
{
	int petId;
	int commonid;
	int color;
	int level;
	int exp;
	int skill;
	int energy; 
};

class PetEntity
{
public: 
	PetEntity(int petId);
	~PetEntity();
	void useSkill();
	const PetData &getPetData()const{ return m_data; }
	const PetsConfig &getMyCommonPetData() const;
	
	void setEnergy(int energy){ m_data.energy = energy; }
	void setExp(int exp){ m_data.exp = exp; }
	void setLevel(int level){ m_data.level = level; }
private:
	PetData m_data;
	PetSkill *m_skill;
};
#endif