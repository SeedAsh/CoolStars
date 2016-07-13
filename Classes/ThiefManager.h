#ifndef __THIEFMANAGER_H__
#define __THIEFMANAGER_H__
#include "cocos2d.h"

enum ThiefPanelType
{
	ThiefPreStagePanel,
	ThiefPetPanel,
	ThiefLotteryPanel,
	ThiefRankingPanel,
	ThiefShopPanel,
	ThiefPackagePanel,
};

class ThiefManager
{
public:
	static ThiefManager *theMgr();

	void init();
	bool isShowUpThief();
	int whitchPanel();
	void triggerThief();
private:
	ThiefManager();
private:
	int m_lastTriggerTime;
	static const int kTriggerDuration = 40 * 60;
};
#endif