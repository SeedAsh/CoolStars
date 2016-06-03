#include "PetView.h"
#include "PetEntity.h"
#include "PetManager.h"
#include "layers_scenes_transitions_nodes\CCLayer.h"
using namespace std;
USING_NS_CC;

PetView::PetView(int petId)
	: m_petId(petId)
{
	m_model = PetManager::petMgr()->getCurPetById(petId);
	assert(m_model);
}

void PetView::onTouchBegan()
{
	runScale();
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
	int color = m_model->getPetData().color;
	auto commonData = m_model->getMyCommonPetData();
	string iconPath = commonData.iconPath[color];

	auto spr = CCSprite::create(iconPath.c_str());
	
	CCSize size = spr->getContentSize();
	setContentSize(size);
	setAnchorPoint(ccp(0.5f, 0.5f));

	spr->setPosition(ccp(size.width * 0.5f, size.height *0.5f));

	addChild(spr);
	
	CCLayerColor *mask = CCLayerColor::create(ccc4(255, 0, 0, 75));
	mask->setContentSize(size);
	addChild(mask);
	return true;
}

void PetView::runScale()
{
	CCScaleTo *scaleLarge = CCScaleTo::create(0.15f, 1.3f);
	CCScaleTo *scaleSmall = CCScaleTo::create(0.15f, 0.8f);
	CCScaleTo *scaleNormal = CCScaleTo::create(0.1f, 1.0f);
	CCSequence *seq = CCSequence::create(scaleLarge, scaleSmall, scaleNormal, NULL);

	runAction(seq);
}
