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
, m_guideEnable(true)
{
}

void GuideMgr::startGuide(int startAction, std::function<void()> callback)
{
	if (!m_guideEnable) return;

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
	if (!m_guideEnable) return;

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
	m_curGuideId = kNotTriggerGuide;

	onSave();
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

void GuideMgr::onSave()
{
	string sql;
	char str[100] = { 0 };
	SqliteHelper helper(DB_SAVING);

	sprintf(str, "replace into save_guide values(1, \"%s\", %d);", parseIntsToStr(m_finishedGuides).c_str(), m_guideEnable ? 1 : 0);

	helper.executeSql(str);
	helper.closeDB();
}

void GuideMgr::setGuideEnable(bool enable)
{
	m_guideEnable = enable;
	onSave();
}