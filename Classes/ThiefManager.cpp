#include "ThiefManager.h"
#include "TimeUtil.h"
#include "DataManager.h"
#include "CommonUtil.h"
USING_NS_CC;
using namespace std;
using namespace CommonUtil;

ThiefManager::ThiefManager()
: m_lastTriggerTime(0)
{

}

ThiefManager *ThiefManager::theMgr()
{
	static ThiefManager mgr;
	return &mgr;
}

void ThiefManager::init()
{
	m_lastTriggerTime = time_util::getCurTime();
}

bool ThiefManager::isShowUpThief()
{
	int curTime = time_util::getCurTime();
	return curTime - m_lastTriggerTime >= kTriggerDuration;
}

int ThiefManager::whitchPanel()
{
	auto configs = DataManagerSelf->getThiefConfigs();
	vector<float> percents;
	for (size_t i = 0; i < configs.size(); ++i)
	{
		percents.push_back(configs[i].percent);
	}
	int result = getResultByPercent(percents);

	return result;
}

void ThiefManager::triggerThief()
{
	m_lastTriggerTime = time_util::getCurTime();
}