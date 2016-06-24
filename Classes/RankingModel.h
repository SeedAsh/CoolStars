#ifndef __RANKINGMODEL_H__
#define __RANKINGMODEL_H__
#include "cocos2d.h"

class RankingModel
{
public:
	static RankingModel *theModel();

	std::string getRandomName();
private:

};
#endif