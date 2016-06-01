#ifndef __SAVINGHELPER_H__
#define __SAVINGHELPER_H__
#include "cocos2d.h"
#include "sqlite3.h"

#define DATA_FILE "state.dat"
#define GAME_CONFIG_FILE_VERSION 1

#define ERROR 0
#define OK 1



class SavingHelper
{
public:
	SavingHelper();
	~SavingHelper();

	int saveCurState();
	std::vector<std::vector<int>> getLastState();
private:

	void putInt(int src, FILE* file);
	int xorEncDecInt(int i);
};

#endif
