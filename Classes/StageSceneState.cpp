#include "StageSceneState.h"
#include "StarsController.h"
#include "StageUiLayer.h"
#include "StarsLayer.h"
#include "StageOperator.h"
#include "PropManager.h"
#include "PetManager.h"
#include "GuideMgr.h"
USING_NS_CC;
using namespace std;
StageStateOwner::StageStateOwner()
{
	
}

void StageStateOwner::init()
{
	m_normalState = new StageNormalState(this);
	m_propsState = new StagePropsClickState(this);
	m_petSkillState = new StagePetSkillState(this);

	enterNormalState();
}

StageStateOwner::~StageStateOwner()
{
	delete m_normalState;
	delete m_propsState;
	delete m_petSkillState;
}

void StageStateOwner::clickStar(const LogicGrid &grid)
{
	GuideMgr::theMgr()->endGuide(kGuideEnd_star_clicked);
	m_curState->clickStar(grid);
}

void StageStateOwner::clickPet(int petId)
{
	GuideMgr::theMgr()->endGuide(kGuideEnd_pet_clicked);
	m_curState->clickPet(petId);
}

void StageStateOwner::enterNormalState()
{
	m_curState = m_normalState;
	StageLayersMgr::theMgr()->toNormalState();
}

void StageStateOwner::enterPropsClickState(int propType)
{
	m_propsState->setCurProp(propType);
	m_curState = m_propsState;
}

void StageStateOwner::enterPetSkillState(int petId)
{
	m_petSkillState->setCurPet(petId);
	m_curState = m_petSkillState;
	auto pet = PetManager::petMgr()->getPetById(petId);
	if (pet)
	{
		pet->skillInit();
	}
}
////////////////////////////////////////////////////////////////////////////////////
StageSceneState::StageSceneState(StageStateOwner *owner)
{
	m_owner = owner;
	m_starsLayer = owner->getStarsLayer();
	m_uiLayer = owner->getUiLayer();
}
////////////////////////////////////////////////////////////////////////////////////
void StageNormalState::clickStar(const LogicGrid &grid)
{
	StarNode *node = StarsController::theModel()->getStarNode(grid);
	if (node)
	{
		node->handleClick();
		StarsController::theModel()->onOneRoundEnd();
		StarsController::theModel()->genNewStars();
		StarsController::theModel()->onOneRoundBegan();
	}
}

void StageNormalState::clickPet(int petId)
{
	auto pet = PetManager::petMgr()->getPetById(petId);
	if (!pet || !pet->canUseSkill()) return;
	int targetType = pet->getPetData().skillTarget;
	if (targetType == kNoTarget)
	{
		pet->noTargetSkill();
	}
	else
	{
		m_owner->enterPetSkillState(petId);
	}
}
////////////////////////////////////////////////////////////////////////////////////
void StagePropsClickState::clickStar(const LogicGrid &grid)
{
	StarNode *node = StarsController::theModel()->getStarNode(grid);
	if (!node) return;
	int starType = node->getAttr().type;
	if (m_curType == kPropBrush && starType == kColorStar)
	{
		m_uiLayer->showChangeColorPanel(grid);
	}
	else if (m_curType == kPropBomb && starType == kBomb)
	{
		PropManager::propMgr()->usePropBomb(grid);
	}
	
}

void StagePropsClickState::clickPet(int petId)
{

}
////////////////////////////////////////////////////////////////////////////////////
void StagePetSkillState::clickStar(const LogicGrid &grid)
{
	auto pet = PetManager::petMgr()->getPetById(m_curPetId);
	if (pet)
	{
		pet->toStarSkill(grid);
		m_owner->enterNormalState();
	}
}

void StagePetSkillState::clickPet(int petId)
{
	auto pet = PetManager::petMgr()->getPetById(m_curPetId);
	if (pet)
	{
		pet->toPetSkill(petId);
		m_owner->enterNormalState();
	}
}