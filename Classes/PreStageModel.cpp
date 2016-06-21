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

void PreStageModel::selectPet(int petId)
{
	auto petMgr = PetManager::petMgr();
	auto iter = find(m_selectedPets.begin(), m_selectedPets.end(), petId);
	if (iter == m_selectedPets.end() && petMgr->ownThisPet(petId))
	{
		m_selectedPets.push_back(petId);
		NOTIFY_VIEWS(onPetSelect);
	}
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



