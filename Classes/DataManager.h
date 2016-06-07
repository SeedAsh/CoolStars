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

	void getNewStageStarsData(std::vector<std::vector<int>> &stars, int stageNum);

	void loadStarsConfig();
	const StarsConfig &getStarsConfig(int starType);

	void loadCommonPetsConfig();
	const PetsConfig &getCommonPetsConfig(int petId);

	void loadSystemConfig();
	const SystemConfig &getSystemConfig();
private:
	vector<StageConfig> m_stagesConfig;
	vector<StarsConfig> m_starsConfig;
	vector<PetsConfig> m_petsConfig;
	SystemConfig m_systemConfig;
};

#endif