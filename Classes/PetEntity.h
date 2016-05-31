#ifndef __PETENTITY_H__
#define __PETENTITY_H__

struct PetData
{
	int level;
	int exp;
	int skill;
	int color;
	int energy; 
};

class PetEntity
{
public: 
	PetEntity();
	~PetEntity();
private:
	PetData m_data;
};
#endif