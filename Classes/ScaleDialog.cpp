#include "ScaleDialog.h"
#include "CommonMacros.h"
using namespace std;
USING_NS_CC; 
//子类设置了contentsize 之后调用即可
void ScaleDialog::initDialog()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	auto mask = getMaskLayer();
	addChild(mask);

	//*
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"common/title_add.png",
		"common/title_add.png",
		this,
		menu_selector(ScaleDialog::closeCallback));
	
	CCMenu *menu = CCMenu::create(pCloseItem, NULL);
	menu->setPosition(ccp(0, 0));
	addChild(menu);
	auto size = getContentSize();
	auto closeItemSize = pCloseItem->getContentSize();
	pCloseItem->setPosition(size.width - closeItemSize.width  * 0.5f, size.height - closeItemSize.height  * 0.5f);
	//*/

	setAnchorPoint(ccp(0.5f, 0.5f));
	ignoreAnchorPointForPosition(false);
	setPosition(ccpMult(winSize, 0.5f));
}

void ScaleDialog::runScale()
{
	setScale(0.2f);

	CCScaleTo *scaleLarge = CCScaleTo::create(0.15f, 1.3f);
	CCScaleTo *scaleNormal = CCScaleTo::create(0.1f, 1.0f);
	CCSequence *seq = CCSequence::create(scaleLarge, scaleNormal, NULL);
	
	runAction(seq);
}

void ScaleDialog::closeCallback(CCObject *pSender)
{
	onClose();
	removeFromParentAndCleanup(true);
}

CCNode *ScaleDialog::getMaskLayer()
{
	CCLayerColor *mask = CCLayerColor::create(ccc4(0, 0, 0, 125));
	mask->ignoreAnchorPointForPosition(false);
	auto size = getContentSize();
	mask->setPosition(ccp(size.width * 0.5f, size.height * 0.5f));
	return mask;
}

void ScaleDialog::onEnter()
{
	CCNode::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kDialogMenuTouchPriority, true);
	runScale();
}

void ScaleDialog::onExit()
{
	CCNode::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool ScaleDialog::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}