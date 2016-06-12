#include "StageLayersMgr.h"
USING_NS_CC;
using namespace std;

StageLayersMgr *StageLayersMgr::theMgr()
{
	static StageLayersMgr mgr;
	return &mgr;
}

void StageLayersMgr::addLayers(IStageLayer *layer)
{
	auto iter = find(m_layers.begin(), m_layers.end(), layer);
	if (iter == m_layers.end())
	{
		m_layers.push_back(layer);
	}
}

void StageLayersMgr::removeLayers(IStageLayer *layer)
{
	auto iter = find(m_layers.begin(), m_layers.end(), layer);
	if (iter != m_layers.end())
	{
		m_layers.erase(iter);
	}
}
