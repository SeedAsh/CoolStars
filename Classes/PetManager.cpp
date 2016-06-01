#include "PetManager.h"
PetManager::PetManager()
{

}

PetManager::~PetManager()
{

}

PetManager *PetManager::petMgr()
{
	static PetManager mgr;
	return &mgr;
}

void PetManager::loadPetsData()
{
	
}

void PetManager::getCurPetsInfo(int color)
{
	if (color == 0)
	{
		// return all
	}
	else
	{
		//return color
	}
}