#include "StageLayersMgr.h"
USING_NS_CC;
using namespace std;

StageLayersMgr *StageLayersMgr::theMgr()
{
	static StageLayersMgr mgr;
	return &mgr;
}

void StageLayersMgr::addLayer(IStageLayer *layer)
{
	auto iter = find(m_layers.begin(), m_layers.end(), layer);
	if (iter == m_layers.end())
	{
		m_layers.push_back(layer);
	}
}

void StageLayersMgr::removeLayer(IStageLayer *layer)
{
	auto iter = find(m_layers.begin(), m_layers.end(), layer);
	if (iter != m_layers.end())
	{
		m_layers.erase(iter);
	}
}

void StageLayersMgr::highLightStars(int color)
{
	NOTIFY_LAYERSS(onHighLightStars, color);
}

void StageLayersMgr::highLightPets(const std::vector<int> &petIds)
{
	NOTIFY_LAYERSS(onHighLightPets, petIds);
}

void StageLayersMgr::toNormalState()
{
	NOTIFY_LAYERSS(onToNormalState);
}

void StageLayersMgr::colorStarErased(cocos2d::CCPoint pos, int color)
{
	NOTIFY_LAYERSS(onNormalStarErased, pos, color);

}