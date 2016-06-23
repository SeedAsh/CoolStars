#include "CommonUtil.h"
using namespace cocos2d;
using namespace std;
vector<string> CommonUtil::split(string str, string pattern)
{
	string::size_type pos;
	vector<string> result;
	str += pattern;//扩展字符串以方便操作
	int size = str.size();

	for (int i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

vector<int> CommonUtil::parseStrToInts(string str)
{
	vector<int> ints;
	auto strs = split(str, ",");
	for (size_t i = 0; i < strs.size(); ++i)
	{
		ints.push_back(atoi(strs[i].c_str()));
	}
	return ints;
}

const char *CommonUtil::intToStr(int value)
{
	static char str[100];
	sprintf(str, "%d", value);
	return str;
}

//end 不超过1000
int CommonUtil::getRandomValue(int begin, int end)
{
	assert(begin <= end);
	return ((int)(CCRANDOM_0_1() * 1000)) % (end - begin + 1) + begin;
}


bool CommonUtil::floatEqual(float v1, float v2)
{
	return (fabs(v1 - v2) < 0.000001);
}


//生成 [0 , length-1] 的随机序列
vector<int> CommonUtil::buildRandomSequence(int length)
{
	vector<int> seq;
	for (int i = 0; i < length; ++i)
	{
		seq.push_back(i);
	}
	int index = 0;
	int tmp = 0;
	for (int i = length - 1; i > 0; i--) {
		index = (int(CCRANDOM_0_1() * 100)) % i;

		tmp = seq[i];
		seq[i] = seq[index];
		seq[index] = tmp;
	}

	return seq;
}