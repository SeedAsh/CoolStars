#include "StageSceneState.h"
#include "StageModel.h"
#include "StageUiLayer.h"
#include "StarsLayer.h"
#include "StageOperator.h"
#include "PropManager.h"
USING_NS_CC;
using namespace std;
StageStateOwner::StageStateOwner()
{
	
}

void StageStateOwner::init()
{
	m_normalState = new StageNormalState(this);
	m_propsState = new StagePropsClickState(this);

	enterNormalState();
}

StageStateOwner::~StageStateOwner()
{
	delete m_propsState;
}

void StageStateOwner::doTouch(const LogicGrid &grid)
{
	m_curState->doTouch(grid);
}

void StageStateOwner::enterNormalState()
{
	m_curState = m_normalState;
}

void StageStateOwner::enterPropsClickState(int propType)
{
	m_propsState->setCurProp(propType);
	m_curState = m_propsState;
}
////////////////////////////////////////////////////////////////////////////////////
StageSceneState::StageSceneState(StageStateOwner *owner)
{
	m_starsLayer = owner->getStarsLayer();
	m_uiLayer = owner->getUiLayer();
}
////////////////////////////////////////////////////////////////////////////////////
void StageNormalState::doTouch(const LogicGrid &grid)
{
	StarNode *node = StageModel::theModel()->getStarNode(grid);
	if (node)
	{
		node->handleClick();
	}
	StageModel::theModel()->genNewStars();
}
////////////////////////////////////////////////////////////////////////////////////
void StagePropsClickState::doTouch(const LogicGrid &grid)
{
	StarNode *node = StageModel::theModel()->getStarNode(grid);
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
////////////////////////////////////////////////////////////////////////////////////
