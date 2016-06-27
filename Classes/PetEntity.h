#ifndef __PETENTITY_H__
#define __PETENTITY_H__
#include "DataManager.h"
#include "LogicGridUtil.h"

class PetSkill;

struct PetData
{
	//不变
	int petId;
	int commonid;
	int color;
	std::string petImgRes;
	std::string petSkillRes;
	std::string petAnimationRes;
	int skillTarget;
	//升级后变化
	int maxEnergy;
	int skillPower;
	int foodToUpgrade;
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

enum PetSkillTarget
{
	kNoTarget = 1,
	kTargetStar,
	kTargetPet,
};

class PetEntity
{
public:
	virtual ~PetEntity();
	const PetData &getPetData()const{ return m_data; }

	void setEnergy(int energy){ m_data.energy = energy; }
	void setExp(int exp){ m_data.exp = exp; }
	void setLevel(int level){ m_data.level = level; }

	static PetEntity *PetFactory(int petId);
protected:
	PetEntity(int petId);
	void refreshPetData();
public:
	//三个接口对应三种技能目标
	virtual void noTargetSkill(){}
	virtual void toStarSkill(const LogicGrid &grid){}
	virtual void toPetSkill(int petId){}
protected:
	PetData m_data;
};


class PetRat: public PetEntity
{
public:
	PetRat(int petId) : PetEntity(petId){}
	virtual void toStarSkill(const LogicGrid &grid);
};

class PetOx : public PetEntity
{
public:
	PetOx(int petId) : PetEntity(petId){}
	virtual void toStarSkill(const LogicGrid &grid);
};

class PetTiger : public PetEntity
{
public:
	PetTiger(int petId) : PetEntity(petId){}
	virtual void noTargetSkill();
};

class PetRabbit : public PetEntity
{
public:
	PetRabbit(int petId) : PetEntity(petId){}
	virtual void noTargetSkill();
};

class PetDragon : public PetEntity
{
public:
	PetDragon(int petId) : PetEntity(petId){}
	virtual void noTargetSkill();
};

class PetSnake : public PetEntity
{
public:
	PetSnake(int petId) : PetEntity(petId){}
	virtual void toStarSkill(const LogicGrid &grid);
};

class PetHorse : public PetEntity
{
public:
	PetHorse(int petId) : PetEntity(petId){}
	virtual void noTargetSkill();
};

class PetGoat : public PetEntity
{
public:
	PetGoat(int petId) : PetEntity(petId){}
	virtual void noTargetSkill();
};

class PetMonkey : public PetEntity
{
public:
	PetMonkey(int petId) : PetEntity(petId){}
	virtual void toPetSkill(int petId);
};

class PetRooster : public PetEntity
{
public:
	PetRooster(int petId) : PetEntity(petId){}
	virtual void noTargetSkill();
};

class PetDog : public PetEntity
{
public:
	PetDog(int petId) : PetEntity(petId){}
	virtual void toPetSkill(int petId);
};

class PetPig : public PetEntity
{
public:
	PetPig(int petId) : PetEntity(petId){}
	virtual void noTargetSkill();
};

#endif