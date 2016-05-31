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

