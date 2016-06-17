#include "PropItemView.h"
#include "PropManager.h"
#include "CommonUtil.h"
#include "StageOperator.h"
using namespace cocos2d;
using namespace std;
using namespace CommonUtil;

PropItemView *PropItemView::create(int type)
{
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
}

PropItemView::PropItemView()
: m_label(NULL)
, m_type(0)
{

}

bool PropItemView::init()
{
	CCSprite *spr = CCSprite::create(m_iconPath.c_str());
	CCSize size = spr->getContentSize();
	spr->setPosition(ccp(size.width * 0.5f, size.height * 0.5f));
	addChild(spr);

	setContentSize(size);

	auto mgr = PropManager::propMgr();
	int amount = mgr->getPropItemAmount(m_type);
	m_label = CCLabelTTF::create(intToStr(amount), "Arial", 18);
	m_label->setPosition(ccp(size.width * 0.5f, size.height * 0.05f));
	addChild(m_label);
	
	setAnchorPoint(ccp(1, 0));
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
		m_label->setString(CommonUtil::intToStr(amount - 1));

		onClick();
	}
}

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