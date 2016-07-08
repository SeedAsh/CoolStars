#ifndef __STAGELAYERSMGR_H__
#define __STAGELAYERSMGR_H__
#include "cocos2d.h"
struct IStageLayer
{
	virtual void initStarsDone(){}
	virtual void onHighLightStars(int color){}
	virtual void onToNormalState(){}
	virtual void onNormalStarErased(cocos2d::CCPoint pos, int color){}
};

#define NOTIFY_LAYERSS(_FUNC_ ,...)						 \
for (size_t index = 0; index < m_layers.size(); ++index) \
{														 \
	m_layers[index]->_FUNC_(__VA_ARGS__);				 \
}

//这个类用于关卡中界面的通信
class StageLayersMgr
{
public:
	static StageLayersMgr *theMgr();
	~StageLayersMgr(){}
	
	void addLayers(IStageLayer *layer);
	void removeLayers(IStageLayer *layer);
public:
	void highLightStars(int color);
	void toNormalState();
	void colorStarErased(cocos2d::CCPoint pos, int color);
private:
	StageLayersMgr(){}
private:
	std::vector<IStageLayer *> m_layers;

};
#endif