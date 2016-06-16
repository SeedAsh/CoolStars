#ifndef __COMMONUTIL_H__
#define __COMMONUTIL_H__
#include "cocos2d.h"
namespace CommonUtil
{	
	std::vector<std::string> split(std::string str, std::string pattern);
	std::vector<int> parseStrToInts(std::string str);//������ 1,2,3 ���ַ����ָ��Ϊ������

	const char *intToStr(int value);

	int getRandomValue(int begin, int end);
}

#endif