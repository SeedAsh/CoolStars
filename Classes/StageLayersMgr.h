#ifndef __STAGELAYERSMGR_H__
#define __STAGELAYERSMGR_H__
#include "cocos2d.h"
struct IStageLayer
{
	virtual void initStarsDone(){}
};

#define NOTIFY_LAYERSS(_FUNC_ ,...)						 \
for (size_t index = 0; index < m_layers.size(); ++index) \
{														 \
	m_layers[index]->_FUNC_(__VA_ARGS__);				 \
}

class StageLayersMgr
{
public:
	static StageLayersMgr *theMgr();
	~StageLayersMgr(){}
	
	void addLayers(IStageLayer *layer);
	void removeLayers(IStageLayer *layer);
private:
	StageLayersMgr(){}
	
private:
	std::vector<IStageLayer *> m_layers;

};
#endif