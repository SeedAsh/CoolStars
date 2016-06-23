#include "PropItemView.h"
#include "PropManager.h"
#include "CommonUtil.h"
#include "StageOperator.h"
#include "UiLayout.h"
using namespace cocos2d;
using namespace std;
using namespace CommonUtil;

PropItemView *PropItemView::create(int type)
{
	PropItemView *view = new PropItemView(type);
	view->init();
	view->autorelease();
	return view;

	/*
	switch (type)
	{
	case kPropBomb:
		return PropItemViewBomb::create();

	case kPropBrush:
		return PropItemViewBrush::create();

	case kPropReorder:
		return PropItemViewReOrder::create();

	default:
		return NULL;
	}
	*/
}

PropItemView::PropItemView(int type)
: m_type(type)
{

}

bool PropItemView::init()
{
	UiLayout *m_layout = UiLayout::create("layout/props_item.xml");

	auto path = DataManagerSelf->getPropsConfig(m_type).resPath;
	auto icon = dynamic_cast<CCSprite *>(m_layout->getChildById(3));
	icon->initWithFile(path.c_str());
	
	setContentSize(m_layout->getContentSize());
	addChild(m_layout);
	return true;
}

void PropItemView::runScale()
{
	CCScaleTo *scaleLarge = CCScaleTo::create(0.15f, 1.3f);
	CCScaleTo *scaleSmall = CCScaleTo::create(0.15f, 0.8f);
	CCScaleTo *scaleNormal = CCScaleTo::create(0.1f, 1.0f);
	CCSequence *seq = CCSequence::create(scaleLarge, scaleSmall, scaleNormal, NULL);

	runAction(seq);
}

void PropItemView::onTouchBegan(cocos2d::CCPoint)
{
	runScale();

	auto mgr = PropManager::propMgr();
	int amount = mgr->getPropItemAmount(m_type);
	if (amount > 0)
	{
		mgr->setPropItemAmount(m_type, amount - 1);

		//onClick();
	}
}
/*
bool PropItemViewBomb::init()
{
	m_iconPath = "Props_Bomb.png";
	m_type = kPropBomb;
	PropItemView::init();
	return true;
}

void PropItemViewBomb::onClick()
{
	//auto grids
	//StageOp->eraseStars();
}

bool PropItemViewBrush::init()
{
	m_iconPath = "Props_Paint.png";
	m_type = kPropBrush;
	PropItemView::init();
	return true;
}

void PropItemViewBrush::onClick()
{
	//CCMessageBox("brush", "brush");

}

bool PropItemViewReOrder::init()
{
	m_iconPath = "Props_Rainbow.png";
	m_type = kPropReorder;
	PropItemView::init();
	return true;
}

void PropItemViewReOrder::onClick()
{
	StageOp->reOrderStars();

}
*/