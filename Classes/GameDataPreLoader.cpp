#include "GameDataPreLoader.h"
#include "GameData.h"
#include "UserInfo.h"
#include "SoundMgr.h"
#include "MyPurchase.h"
#include "DataManager.h"
#include "DataCheck.h"
#include "PetManager.h"
#include "PropManager.h"
#include "StarsController.h"
#include "GuideMgr.h"
#include "RankingModel.h"
#include "StageDataMgr.h"
#include "ThiefManager.h"

void GameDataPreLoader::initGameData()
{
	LoadGameConfigs();
	intModels();
}

void GameDataPreLoader::LoadGameConfigs()
{
	//GameData::getInstance()->preloadData();

	//�����ݿ����ݽ�������У�� ��ʽ�汾��ȡ��У��
	DataCheck check;
	check.checkDataBase();

	DataManagerSelf->LoadData();

}

void GameDataPreLoader::intModels()
{
	UserInfo::theInfo()->init();
	SoundMgr::init();

	StageDataMgr::theMgr()->init();
	PropManager::propMgr()->loadPropData();
	PetManager::petMgr()->init();
	GuideMgr::theMgr()->init();
	RankingModel::theModel()->init();
	ThiefManager::theMgr()->init();
}