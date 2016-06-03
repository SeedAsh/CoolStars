#ifndef __SAVINGHELPER_H__
#define __SAVINGHELPER_H__
#include "cocos2d.h"
#include "sqlite3.h"
#include "PetEntity.h"

#define DATA_FILE "state.dat"
#define GAME_CONFIG_FILE_VERSION 1

#define ERROR 0
#define OK 1


class SavingHelper
{
public:
	static SavingHelper *theHelper();
	~SavingHelper();

	void saveCurStars();
	void getLastSavedStars(std::vector<std::vector<int>> &stars);

	void setPetsData();
	PetData getPetsData(int petId);
private:
	SavingHelper();

};

#endif
