#include "GameDataPreLoader.h"
#include "GameData.h"
#include "UserInfo.h"
#include "SoundMgr.h"
#include "MyPurchase.h"
#include "DataManager.h"
#include "DataCheck.h"
#include "PetManager.h"
#include "PropManager.h"
#include "StageModel.h"
#include "GuideMgr.h"
#include "RankingModel.h"

void GameDataPreLoader::initGameData()
{
	LoadGameConfigs();
	intModels();
}

void GameDataPreLoader::LoadGameConfigs()
{
	//GameData::getInstance()->preloadData();

	//对数据库数据进行数据校验 正式版本着取消校验
	DataCheck check;
	check.checkDataBase();

	DataManagerSelf->LoadData();

}

void GameDataPreLoader::intModels()
{
	UserInfo::theInfo()->init();
	SoundMgr::init();

	StageModel::theModel()->getStageInfo()->init();
	PropManager::propMgr()->loadPropData();
	PetManager::petMgr()->init();
	GuideMgr::theMgr()->init();
	RankingModel::theModel()->init();
}