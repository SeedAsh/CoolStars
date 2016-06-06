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

	//不强制复制数据库，若数据库升级，再强制复制，此时考虑若是有写数据库操作，怎么备份已经有的数据或写其它数据库或写其它文件实现，如CCUserDefaultEx
	DataManagerSelf->UnzipGameData(false);
	DataManagerSelf->LoadData();

}

void GameDataPreLoader::intModels()
{
	UserInfo::init();
	SoundMgr::init();
	
	PetManager::petMgr()->init();
}