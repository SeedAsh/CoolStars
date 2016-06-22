#ifndef __PETENTITY_H__
#define __PETENTITY_H__
#include "DataManager.h"

class PetSkill;

struct PetData
{
	//����
	int petId;
	int commonid;
	int color;
	std::string petResPath;
	std::string skillResPath;
	//������仯
	int maxEnergy;
	int skillPower;
	int foodToUpgrade;
	//�ɱ�
	int level;
	int exp;
	int energy; 
};

enum PetType
{
	kPetRat = 1,
	kPetOx,
	kPetTiger,
	kPetRabbit,
	kPetDragon,
	kPetSnake,
	kPetHorse,
	kPetGoat,
	kPetMonkey,
	kPetRooster,
	kPetDog,
	kPetPig,
};

class PetEntity
{
public: 
	virtual ~PetEntity();
	//���������ݣ�������ͻ���
	const PetData &getPetData()const{ return m_data; }
	
	void setEnergy(int energy){ m_data.energy = energy; }
	void setExp(int exp){ m_data.exp = exp; }
	void setLevel(int level){ m_data.level = level; }

	static PetEntity *PetFactory(int petId);
protected:
	PetEntity(int petId);
	void refreshPetData();
public:
	virtual void useSkill() = 0;
private:
	PetData m_data;
};


class PetRat: public PetEntity
{
public:
	PetRat(int petId) : PetEntity(petId){}
	virtual void useSkill();
};

class PetOx : public PetEntity
{
public:
	PetOx(int petId) : PetEntity(petId){}
	virtual void useSkill();
};

class PetTiger : public PetEntity
{
public:
	PetTiger(int petId) : PetEntity(petId){}
	virtual void useSkill();
};

class PetRabbit : public PetEntity
{
public:
	PetRabbit(int petId) : PetEntity(petId){}
	virtual void useSkill();
};

class PetDragon : public PetEntity
{
public:
	PetDragon(int petId) : PetEntity(petId){}
	virtual void useSkill();
};

class PetSnake : public PetEntity
{
public:
	PetSnake(int petId) : PetEntity(petId){}
	virtual void useSkill();
};

class PetHorse : public PetEntity
{
public:
	PetHorse(int petId) : PetEntity(petId){}
	virtual void useSkill();
};

class PetGoat : public PetEntity
{
public:
	PetGoat(int petId) : PetEntity(petId){}
	virtual void useSkill();
};

class PetMonkey : public PetEntity
{
public:
	PetMonkey(int petId) : PetEntity(petId){}
	virtual void useSkill();
};

class PetRooster : public PetEntity
{
public:
	PetRooster(int petId) : PetEntity(petId){}
	virtual void useSkill();
};

class PetDog : public PetEntity
{
public:
	PetDog(int petId) : PetEntity(petId){}
	virtual void useSkill();
};

class PetPig : public PetEntity
{
public:
	PetPig(int petId) : PetEntity(petId){}
	virtual void useSkill();
};


#endif