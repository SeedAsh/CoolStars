#include "RedPackageModule.h"
#include "StageDataMgr.h"
#include "CommonUtil.h"
#include "GoodsMgr.h"
#include "DataManager.h"
#include "PackageScene.h"
#include "MainScene.h"

using namespace std;
USING_NS_CC;
using namespace CommonUtil;

RedPackageModule::RedPackageModule()
: m_times(0)
{

}

bool RedPackageModule::isShowUp()
{
	int curScore = StageDataMgr::theMgr()->getCurScore();
	int targetScore = StageDataMgr::theMgr()->getTargetScore();
	return (float)curScore / targetScore >= 0.5f;
}

int RedPackageModule::whitchRedPackage()
{
	if (m_times == 0)
	{
		return kRedPackageDiamond;
	}
	else
	{
		vector<float> percents;
		percents.push_back(60);
		percents.push_back(40);

		int result = getResultByPercent(percents);
		return result;
	}
	
}

void RedPackageModule::openRedPackage(int type)
{
	m_times++;
	if (type == kRedPackageDiamond)
	{
		auto rewards = DataManagerSelf->getRewardsConfig().redPackage;
		GoodsMgr::theMgr()->addGoods(rewards);
	}
	else
	{
		PackageDialog *dialog = PackageDialog::create(kPackageDiamond);
		MainScene::theScene()->showDialog(dialog);
	}
}