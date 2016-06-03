#ifndef __PETMANAGER_H__
#define __PETMANAGER_H__
#include "cocos2d.h"
#include "PetEntity.h"
#include "CommonMacros.h"

class PetEntity;
class PetManager
{
public:
	static PetManager *petMgr();
	void init();
	void clearCurPets();
	std::vector<int> getCurPetIds();
	 PetEntity *getCurPetById(int id);
private:
	PetManager();
	~PetManager();
private:
	std::map<int, PetEntity *> m_pets;
};
#endif