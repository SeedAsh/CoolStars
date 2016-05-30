#include "SavingHelper.h"
#include "ConfData.h"

USING_NS_CC;
using namespace std;
SavingHelper::SavingHelper()
{
}

SavingHelper::~SavingHelper()
{

}

int SavingHelper::saveCurState()
{
	string path = CCFileUtils::sharedFileUtils()->getWritablePath() + DATA_FILE;
	int score = 1200;
	int setps = 10;
	int star[ROWS_SIZE][COlUMNS_SIZE] = {0};
	FILE *file = fopen(path.c_str(), "wb+");
	if (file) {
		putInt(xorEncDecInt(GAME_CONFIG_FILE_VERSION), file);
		putInt(xorEncDecInt(score), file);
		putInt(xorEncDecInt(setps), file);
		for (int i = 0; i < ROWS_SIZE; i++){
			for (int j = 0; j < COlUMNS_SIZE; j++){
				putInt(xorEncDecInt(star[i][j]), file);
			}
		}
		fclose(file);
		return OK;
	}
	else{
		CCLOG("save file error.");
	}
	return ERROR;
}

vector<vector<int>> SavingHelper::getLastState(){
	string path = CCFileUtils::sharedFileUtils()->getWritablePath() + DATA_FILE;
	FILE *file = fopen(path.c_str(), "r");
	vector<vector<int>> StageVec;
	if (file) {
		int star[ROWS_SIZE][COlUMNS_SIZE] = { 0 };
		for (int i = 0; i < COlUMNS_SIZE; i++){
			vector<int> vec;
			StageVec.push_back(vec);
			for (int j = 0; j < ROWS_SIZE; j++){
				StageVec[i].push_back(xorEncDecInt(0));
			}
		}
		fclose(file);
	}
	else{
		CCLOG("save file error.");
	}
	return StageVec;
}

void SavingHelper::putInt(int src, FILE* file){
	int temp = src;
	fwrite((char *)(&temp), sizeof(temp), 1, file);
}

int SavingHelper::xorEncDecInt(int ch){
	return ch ^ 0x8B7E;
}