#include "PreStageModel.h"
#include "PetManager.h"
#include "CommonMacros.h"

using namespace std;
USING_NS_CC;

PreStageModel *PreStageModel::theModel()
{
	static PreStageModel model;
	return &model;
}

void PreStageModel::selectPet(int newPetId, int oldPetId)
{
	auto petMgr = PetManager::petMgr();
	auto iter = find(m_selectedPets.begin(), m_selectedPets.end(), oldPetId);
	if (iter != m_selectedPets.end())
	{
		m_selectedPets.erase(iter);
	}

	iter = find(m_selectedPets.begin(), m_selectedPets.end(), newPetId);
	if (iter == m_selectedPets.end() && petMgr->ownThisPet(newPetId))
	{
		m_selectedPets.push_back(newPetId);
	}

	NOTIFY_VIEWS(onPetSelect);
}

std::vector<int> PreStageModel::getPetsCanSelect()
{
	auto ids = PetManager::petMgr()->getOwnedPetIds();
	vector<int> result(ids.size());
	sort(ids.begin(), ids.end());
	sort(m_selectedPets.begin(), m_selectedPets.end());

	auto iter = set_difference(ids.begin(), ids.end(), m_selectedPets.begin(), m_selectedPets.end(), result.begin());

	return vector<int>(result.begin(), iter);
}

void PreStageModel::addView(IPreStageView *view)
{
	auto iter = find(m_views.begin(), m_views.end(), view);
	if (iter == m_views.end())
	{
		m_views.push_back(view);
	}
}

void PreStageModel::removeView(IPreStageView *view)
{
	auto iter = find(m_views.begin(), m_views.end(), view);
	if (iter != m_views.end())
	{
		m_views.erase(iter);
	}
}

void PreStageModel::confirmCurPets()
{
	PetManager::petMgr()->setCurPets(m_selectedPets);
}


