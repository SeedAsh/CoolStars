#ifndef __DATAMANAGER__
#define __DATAMANAGER__

#include "sqlite3.h"
#include "DataConfig.h"
#include "cocos2d.h"
#include "ConfData.h"

using namespace std;
USING_NS_CC;

#define DataManagerSelf DataManager::GetSelf() 

class DataManager
{
public:
	DataManager(void);
	virtual ~DataManager(void);
	DataManager* m_pSelf;

	static DataManager* GetSelf()
	{
		static DataManager mgr;
		return &mgr;
	}

	void LoadData();

public:
	void loadStageConfig();
	const StageConfig &getStageConfig(int stage);

	void getNewStageStarsData(std::vector<std::vector<StageStarInfo>> &stars, int stageNum);

	void loadStarsConfig();
	const StarsConfig &getStarsConfig(int starType);

	void loadStarsColorConfig();
	const StarsColorConfig &getStarsColorConfig(int color);

	void loadPetCommonConfig();
	const PetCommonConfig &getPetCommonConfig(int petCommonId);

	void loadPetResConfig();
	const PetResConfig &getPetResConfig(int petId);

	void loadSystemConfig();
	const SystemConfig &getSystemConfig();

	void loadPropsConfig();
	const PropsConfig &getPropsConfig(int propsId);

	void loadRankingConfig();
	const RankingConfig &getRankingConfig(int rank);

	void loadShopConfig();
	const std::vector<ShopConfig> &getShopConfig();

	void loadPackageConfig();
	const PackageConfig &getPackageConfig(int type);
private:
	vector<StageConfig> m_stagesConfig;
	vector<StarsConfig> m_starsConfig;
	vector<PetCommonConfig> m_petCommonConfig;
	vector<PetResConfig> m_petResConfig;
	vector<StarsColorConfig> m_starsColorConfig;
	SystemConfig m_systemConfig;
	vector<PropsConfig> m_propsConfig;
	vector<RankingConfig> m_rankingConfig;
	vector<ShopConfig> m_shopConfig;
	vector<PackageConfig> m_packageConfig;
};

#endif