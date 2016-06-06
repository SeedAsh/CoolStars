#include "PetManager.h"
#include "DataManager.h"
#include "PetSavingHelper.h"
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

void PetManager::init()
{
	clearCurPets();
	auto ids = PetSavingHelper::getCurActivePets();
	for (size_t i = 0; i < ids.size(); ++i)
	{
		int id = ids[i];
		m_pets[id] = new PetEntity(id);
	}
}

void PetManager::clearCurPets()
{
	for (auto iter = m_pets.begin(); iter != m_pets.end(); ++iter)
	{
		delete (iter->second);
	}
	m_pets.clear();
}

vector<int> PetManager::getCurPetIds()
{
	vector<int> ids;
	for (auto iter = m_pets.begin(); iter != m_pets.end(); ++iter)
	{
		ids.push_back(iter->first);
	}
	return ids;
}

PetEntity *PetManager::getCurPetById(int id)
{
	if (m_pets.find(id) != m_pets.end())
	{
		return m_pets[id];
	}
	
	return NULL;
}
