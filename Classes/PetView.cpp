#include "PetView.h"
#include "PetEntity.h"
#include "PetManager.h"
using namespace std;
USING_NS_CC;

PetView::PetView(int petId)
	: m_petId(petId)
{
	m_model = PetManager::petMgr()->getPetById(petId);
	assert(m_model);
}

bool PetView::onTouchBegan(cocos2d::CCPoint pt, bool isInside)
{
	runScale();
	return true;
	//CCMessageBox("click!", "click");
}

PetView *PetView::create(int petId)
{
	auto view = new PetView(petId);
	view->init();
	view->autorelease();
	return view;
}

bool PetView::init()
{
	string iconPath = m_model->getPetData().petResPath;

	auto spr = CCSprite::create(iconPath.c_str());
	CCSize size = spr->getContentSize();

	//设置宠物的宽度为两个星星的大小
	float scale = STAR_SIZE / size.width * 2;
	spr->setScale(scale);
	size.width *= scale;
	size.height *= scale;

	setContentSize(size);
	setAnchorPoint(ccp(0.5f, 0.5f));

	spr->setPosition(ccp(size.width * 0.5f, size.height *0.5f));

	addChild(spr);
	
	CCLayerColor *mask = CCLayerColor::create(ccc4(255, 0, 0, 75));
	mask->setContentSize(size);
	//addChild(mask);
	return true;
}



////////////////////////////////////////////////////////////////////////////////////////
PetEmptyView *PetEmptyView::create()
{
	auto view = new PetEmptyView();
	view->init();
	view->autorelease();
	return view;
}

bool PetEmptyView::init()
{
	string iconPath = "pets/black.png";
	auto spr = CCSprite::create(iconPath.c_str());
	CCSize size = spr->getContentSize();

	//设置宠物的宽度为两个星星的大小
	float scale = STAR_SIZE / size.width * 2;
	spr->setScale(scale);
	size.width *= scale;
	size.height *= scale;

	setContentSize(size);
	setAnchorPoint(ccp(0.5f, 0.5f));

	spr->setPosition(ccp(size.width * 0.5f, size.height *0.5f));
	addChild(spr);
	return true;
}

bool PetEmptyView::onTouchBegan(cocos2d::CCPoint pt, bool isInside)
{
	runScale();
	return true;
}