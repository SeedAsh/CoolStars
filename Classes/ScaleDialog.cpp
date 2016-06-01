#include "ScaleDialog.h"
using namespace std;
USING_NS_CC; 
//子类设置了contentsize 之后调用即可
bool ScaleDialog::init()
{
	auto visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	auto mask = getMaskLayer();
	addChild(mask);

	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"loginCancel.png",
		"loginCancel.png",
		this,
		menu_selector(ScaleDialog::closeCallback));

	CCMenu *menu = CCMenu::create(pCloseItem, NULL);
	addChild(menu);
	auto size = getContentSize();
	auto closeItemSize = pCloseItem->getContentSize();
	menu->setPosition(size.width - closeItemSize.width  * 0.5f, size.height - closeItemSize.height  * 0.5f);

	setAnchorPoint(ccp(0.5f, 0.5f));
	ignoreAnchorPointForPosition(false);
	setPosition(ccp(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
	return true;
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

void ScaleDialog::onEnter(){
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	runScale();
}

void ScaleDialog::onExit(){
	CCLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool ScaleDialog::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}