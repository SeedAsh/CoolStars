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
	LoadSaving();
	intModels();
}

void GameDataPreLoader::LoadGameConfigs()
{
	MyPurchase::sharedPurchase()->loadIAPPlugin();
	GameData::getInstance()->preloadData();

	//�����ݿ����ݽ�������У�� ��ʽ�汾��ȡ��У��
	DataCheck check;
	check.checkDataBase();

	//��ǿ�Ƹ������ݿ⣬�����ݿ���������ǿ�Ƹ��ƣ���ʱ����������д���ݿ��������ô�����Ѿ��е����ݻ�д�������ݿ��д�����ļ�ʵ�֣���CCUserDefaultEx
	DataManagerSelf->UnzipGameData(false);
	DataManagerSelf->LoadData();

}

void GameDataPreLoader::LoadSaving()
{
	DataManagerSelf->loadCurState();
}

void GameDataPreLoader::intModels()
{
	UserInfo::init();
	SoundMgr::init();
	
	PetManager::petMgr()->init();
}