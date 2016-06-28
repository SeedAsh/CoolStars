#ifndef __COMMONUTIL_H__
#define __COMMONUTIL_H__
#include "cocos2d.h"
namespace CommonUtil
{	
	std::vector<std::string> split(std::string str, std::string pattern);
	std::vector<int> parseStrToInts(std::string str);//将类似 1,2,3 的字符串分割返回为数字组

	const char *intToStr(int value);

	int getRandomValue(int begin, int end);
	bool floatEqual(float v1, float v2);
	std::vector<int> buildRandomSequence(int length);
	int getResultByPercent(const std::vector<float> &percents);
	bool isSelected(int percent);

	std::vector<int> getDifference(const std::vector<int> &v1, const std::vector<int> &v2);
}

#endif