#ifndef __PETMANAGER_H__
#define __PETMANAGER_H__
#include "cocos2d.h"

class PetEntity;
class PetManager
{
public:
	static PetManager *petMgr();
	void loadPetsData();
	void getCurPetsInfo(int color = 0);
private:
	PetManager();
	~PetManager();
private:
	std::vector<PetEntity *> m_pets;
};
#endif