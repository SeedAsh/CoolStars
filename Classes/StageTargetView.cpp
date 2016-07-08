#include "StageTargetView.h"
#include "UiLayout.h"
#include <vector>
#include "CommonUtil.h"
#include "EmptyBox.h"
USING_NS_CC;
using namespace std;
using namespace CommonUtil;

StageTargetView *StageTargetView::create(const EraseStarsData &data)
{
	StageTargetView *view = new StageTargetView(data);
	view->init();
	view->autorelease();
	return view;
}

StageTargetView::StageTargetView(const EraseStarsData &data)
: m_targetData(data)
{
}

void StageTargetView::onEnter()
{
	CCNode::onEnter();
	StageDataMgr::theMgr()->addView(this);
}

void StageTargetView::onExit()
{
	CCNode::onExit();
	StageDataMgr::theMgr()->removeView(this);
}

bool StageTargetView::init()
{
	m_layout = UiLayout::create("layout/stage_target.xml");
	addChild(m_layout);
	initLayout();

	setScale(0.8f);
	setContentSize(m_layout->getContentSize());
	return true;
}

void StageTargetView::initLayout()
{
	StarAttr attr;
	attr.type = m_targetData.starType;
	attr.color = m_targetData.color;
	auto node = StarNode::createNodeFatory(attr);
	string path = node->getResPath();
	string bornAnimationPath = node->getBornAnimationPath();
	delete node;

	CCSprite *img = dynamic_cast<CCSprite *>((m_layout->getChildById(1)));
	img->initWithFile(path.c_str());

	if (!bornAnimationPath.empty())
	{
		CCSprite * bornSpr = CCSprite::create(bornAnimationPath.c_str());
		EmptyBox *box = dynamic_cast<EmptyBox *>((m_layout->getChildById(2)));
		box->setNode(bornSpr);
	}
	refreshNum();
}

void StageTargetView::onStepsChanged()
{
	auto target = StarsController::theModel()->getStageTarget();
	auto leftTarget = target->getEraseStarsLeft();
	auto iter = find_if(leftTarget.begin(), leftTarget.end(), [=](EraseStarsData data)->bool
	{
		return data.starType == m_targetData.starType && data.color == m_targetData.color;
	});

	assert(iter != leftTarget.end());
	if (iter != leftTarget.end())
	{
		m_targetData = *iter;
		refreshNum();
	}

}

void StageTargetView::refreshNum()
{
	CCLabelAtlas *leftNum = dynamic_cast<CCLabelAtlas *>((m_layout->getChildById(3)));
	leftNum->setString(intToStr(m_targetData.num));
}

