#ifndef __PETSKILL_H__
#define __PETSKILL_H__

class PetSkill
{
public:
protected:
	PetSkill(){}
	~PetSkill(){}
private:
};

class PetSkillEraseOnRow : public PetSkill
{

};

class PetSkillEraseOnColumn : public PetSkill
{

};

class PetSkillAddSteps : PetSkill
{
public:
	PetSkillAddSteps(){}
	~PetSkillAddSteps(){}
private:

};

class PetSkillChangeColor : PetSkill
{
public:
	PetSkillChangeColor(){}
	~PetSkillChangeColor(){}
private:

};





/*

class PetSkill : PetSkill
{
public:
PetSkill(){}
~PetSkill(){}
private:

};

*/

#endif