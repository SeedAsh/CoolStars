#ifndef __TIMEUTILE_H
#define __TIMEUTILE_H
#include "cocos2d.h"

struct TimeWrapper 
{
	int year;
	int month;
	int day;
	int hour;
	int min;
	int second;
};

TimeWrapper GetTime();
#endif