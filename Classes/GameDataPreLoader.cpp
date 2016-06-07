#include "GameDataPreLoader.h"
#include "GameData.h"
#include "UserInfo.h"
#include "SoundMgr.h"
#include "MyPurchase.h"
#include "DataManager.h"
#include "DataCheck.h"
#include "PetManager.h"

void GameDataPreLoader::initGameData()
{
	LoadGameConfigs();
	intModels();
}

void GameDataPreLoader::LoadGameConfigs()
{
	MyPurchase::sharedPurchase()->loadIAPPlugin();
	GameData::getInstance()->preloadData();

	//对数据库数据进行数据校验 正式版本着取消校验
	DataCheck check;
	check.checkDataBase();

	DataManagerSelf->LoadData();

}

void GameDataPreLoader::intModels()
{
	UserInfo::init();
	SoundMgr::init();
	
	PetManager::petMgr()->init();
}