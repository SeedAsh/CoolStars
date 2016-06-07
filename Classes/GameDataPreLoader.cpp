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

	//�����ݿ����ݽ�������У�� ��ʽ�汾��ȡ��У��
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