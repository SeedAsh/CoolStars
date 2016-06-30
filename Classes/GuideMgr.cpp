#include "GuideMgr.h"
#include "SqliteHelper.h"
#include "CommonUtil.h"
#include "DataManager.h"
#include "StageModel.h"
#include "StageBaseInfo.h"
#include "GuideMacros.h"
#include "MainScene.h"
using namespace std;
USING_NS_CC;
using namespace CommonUtil;

GuideMgr *GuideMgr::theMgr()
{
	static GuideMgr mgr;
	return &mgr;
}

GuideMgr::GuideMgr()
: m_curGuideId(kNotTriggerGuide)
{
}

void GuideMgr::startGuide(int startAction, std::function<void()> callback)
{
	int topStage = StageModel::theModel()->getStageInfo()->getTopStage();

	auto configs = DataManagerSelf->getGuideConfig();
	auto iter = find_if(configs.begin(), configs.end(), [=](GuideConfig data)
	{
		//如果已经完成，放弃
		if (find(m_finishedGuides.begin(), m_finishedGuides.end(), data.id) != m_finishedGuides.end())
		{
			return false;
		}

		return data.stage == topStage
			&& data.startAction == startAction;
	});
	
	if (iter != configs.end())
	{
		m_curGuideId = iter->id;

		if (callback)
		{
			callback();
		}
		if (iter->showGuideView)
		{
			MainScene::theScene()->showGuideView(m_curGuideId);
		}
	}
}

void GuideMgr::endGuide(int endAction)
{
	if (m_curGuideId == kNotTriggerGuide) return;
	
	auto config = DataManagerSelf->getGuideConfigById(m_curGuideId);
	if (config->endAction == endAction)
	{
		finishGuide();
	}
}

void GuideMgr::finishGuide()
{
	auto iter = find(m_finishedGuides.begin(), m_finishedGuides.end(), m_curGuideId);
	if (iter != m_finishedGuides.end()) return;

	m_finishedGuides.push_back(m_curGuideId);
	string sql;
	char str[100] = { 0 };
	SqliteHelper helper(DB_SAVING);

	sprintf(str, "replace into save_guide values(1, \"%s\");", parseIntsToStr(m_finishedGuides).c_str());

	helper.executeSql(str);
	helper.closeDB();

	m_curGuideId = kNotTriggerGuide;
}

void GuideMgr::init()
{
	SqliteHelper sqlHelper(DB_SAVING);
	auto result = sqlHelper.readRecord("select * from save_guide");
	for (auto iter = result.begin(); iter != result.end(); ++iter)
	{
		auto data = *iter;
		m_finishedGuides = parseStrToInts(data[1]);
	}
}
