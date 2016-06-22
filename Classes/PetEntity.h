#ifndef __PETENTITY_H__
#define __PETENTITY_H__
#include "DataManager.h"

class PetSkill;

struct PetData
{
	//不变
	int petId;
	int commonid;
	int color;
	std::string path;
	std::string skillPath;
	 //可变
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
	//独立的数据，如红龙和黄龙
	const PetData &getPetData()const{ return m_data; }
	//同种宠物不同颜色的数据，如红龙和黄龙都是龙
	const PetsConfig &getMyCommonPetData() const;
	
	void setEnergy(int energy){ m_data.energy = energy; }
	void setExp(int exp){ m_data.exp = exp; }
	void setLevel(int level){ m_data.level = level; }

	static PetEntity *PetFactory(int petId);
protected:
	PetEntity(int petId);
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