#include "PackageScene.h"
#include "UiLayout.h"
#include "MenuScene.h"
#include "TitlePanel.h"

USING_NS_CC;
using namespace std;

PackageView *PackageView::create(int type, int touchPriority)
{
	PackageView *view = new PackageView(type, touchPriority);
	view->init();
	view->autorelease();
	return view;
}

PackageView::PackageView(int type, int touchPriority)
: m_type(type)
, m_touchPriority(touchPriority)

{

}

bool PackageView::init()
{
	m_layout = UiLayout::create("layout/package_common.xml");
	m_layout->setMenuTouchPriority(m_touchPriority);
	addChild(m_layout);
	initLayout();
	setContentSize(m_layout->getContentSize());
	return true;
}

void PackageView::initLayout()
{
	CCMenuItem *cancelBtn = dynamic_cast<CCMenuItem *>((m_layout->getChildById(4)));
	cancelBtn->setTarget(this, menu_selector(PackageView::onCancelBtnClicked));

	CCMenuItem *buyBtn = dynamic_cast<CCMenuItem *>((m_layout->getChildById(5)));
	buyBtn->setTarget(this, menu_selector(PackageView::onBuyBtnClicked));
}

void PackageView::onCancelBtnClicked(cocos2d::CCObject* pSender)
{
	if (m_handle)
	{
		m_handle();
	}
}

void PackageView::onBuyBtnClicked(cocos2d::CCObject* pSender)
{
	if (m_handle)
	{
		m_handle();
	}
}


bool PackageScene::init()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	setContentSize(winSize);

	auto view = PackageView::create(kPackageProps, m_touchPriority);
	view->setAnchorPoint(ccp(0.5f, 0.5f));
	view->setPosition(ccpMult(winSize, 0.5f));
	addChild(view);

	auto titlePanel = TitlePanel::create(m_touchPriority);
	addChild(titlePanel);
	return true;
}


PackageDialog *PackageDialog::create(int type)
{
	auto dialog = new PackageDialog(type);
	dialog->init();
	dialog->autorelease();
	return dialog;
}

bool PackageDialog::init()
{
	auto view = PackageView::create(m_type, m_touchPriority);
	view->setBtnHanle([=]()
	{
		removeFromParent();
	});
	addChild(view);
	auto size = view->getContentSize();
	setContentSize(size);

	addMaskLayer();
	return true;
}


