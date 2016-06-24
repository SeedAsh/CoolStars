#include "TimeUtil.h"
USING_NS_CC;
using namespace std;

TimeWrapper GetTime()
{
	struct tm *tm;
	time_t timep;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	time(&timep);
#else
	struct cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now, NULL);
	timep = now.tv_sec;
#endif
	tm = localtime(&timep);
	TimeWrapper curTime;
	curTime.year = tm->tm_year + 1900;
	curTime.month = tm->tm_mon + 1;
	curTime.day = tm->tm_mday;
	curTime.hour = tm->tm_hour;
	curTime.min = tm->tm_min;
	curTime.second = tm->tm_sec;

	return curTime;
}