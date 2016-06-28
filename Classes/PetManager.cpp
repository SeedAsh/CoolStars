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
	for (int petId = 1; petId <= PETS_AMOUNT; ++petId)
	{
		m_pets[petId] = PetEntity::PetFactory(petId);
	}

	m_curPets = PetSavingHelper::getCurActivePets();
	for (size_t i = 0; i < m_curPets.size(); ++i)
	{
		assert(ownThisPet(m_curPets[i]));
	}
}

vector<int> PetManager::getOwnedPetIds()
{
	vector<int> ids;
	for (auto iter = m_pets.begin(); iter != m_pets.end(); ++iter)
	{
		int petId = iter->first;
		if (ownThisPet(petId))
		{
			ids.push_back(iter->first);
		}
	}
	return ids;
}

vector<int> PetManager::getNotOwnedPetIds()
{
	vector<int> ids;
	for (auto iter = m_pets.begin(); iter != m_pets.end(); ++iter)
	{
		int petId = iter->first;
		if (!ownThisPet(petId))
		{
			ids.push_back(iter->first);
		}
	}
	return ids;
}

bool PetManager::ownThisPet(int id)
{
	auto pet = getPetById(id);
	if (!pet) return false;
	return pet->getPetData().level > 0; //大于0级，玩家才拥有该宠物
}

PetEntity *PetManager::getPetById(int id)
{
	if (m_pets.find(id) != m_pets.end())
	{
		return m_pets[id];
	}
	return NULL;
}

void PetManager::setCurPets(std::vector<int> &ids)
{ 
	m_curPets = ids; 
	PetSavingHelper::recordCurActivePets();
}