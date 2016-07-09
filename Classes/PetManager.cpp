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
	return pet->getPetData().level > 0; //����0������Ҳ�ӵ�иó���
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

void PetManager::addPetEnergy(int petId, int value)
{
	if (find(m_curPets.begin(), m_curPets.end(), petId) == m_curPets.end()) return;

	auto pet = getPetById(petId);
	if (pet)
	{
		auto data = pet->getPetData();
		pet->setEnergy(data.energy + value);
	}
}

void PetManager::newStageInit()
{
	for (size_t i = 0; i < m_curPets.size(); ++i)
	{
		auto pet = getPetById(m_curPets[i]);
		if (pet)
		{
			pet->setEnergy(0);
		}

	}
}