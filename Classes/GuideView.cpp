#include "GuideView.h"
#include "UiLayout.h"
#include "CommonUtil.h"
#include "CommonMacros.h"
#include "DataManager.h"
USING_NS_CC;
using namespace std;
GuideView::GuideView(int guideId)
: m_guideId(guideId)
{
}

GuideView *GuideView::create(int guideId)
{
	auto view = new GuideView(guideId);
	view->init();
	view->autorelease();
	return view;
}

void GuideView::onEnter()
{
	CCNode::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kGuideTouchPriority, true);
}

void GuideView::onExit()
{
	CCNode::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool GuideView::init()
{
	m_layout = UiLayout::create("layout/guide_text_dialog.xml");
	initPanel();

	setContentSize(m_layout->getContentSize());                                                     
	addChild(m_layout);
	return true;
}

void GuideView::initPanel()
{
	auto config = DataManagerSelf->getGuideConfigById(m_guideId);

	auto rectVec = config->targetRect;
	m_targetRect.setRect(rectVec[0], rectVec[1], rectVec[2], rectVec[3]);

	if (config->showMask)
	{
		addMaskLayer();
	}

	//手指动画
	if (config->showFinger)
	{
		CCSprite *fingerSpr = dynamic_cast<CCSprite *>(m_layout->getChildById(3));
		auto animation = CommonUtil::getFrameAnimation("guide/xszt_shouzi_%d.png", 2, 0.3f);
		fingerSpr->runAction(CCRepeatForever::create(animation));
		fingerSpr->setAnchorPoint(ccp(0, 1));
		fingerSpr->setPosition(ccp(m_targetRect.getMaxX(), m_targetRect.getMinY()));
	}
	else
	{
		m_layout->getChildById(3)->setVisible(false);
	}

	//文本对话框
	if (config->showTextDialog)
	{
		auto dialogText = config->dialogText;
		CCSprite *textImg = dynamic_cast<CCSprite *>(m_layout->getChildById(2));
		textImg->initWithFile(dialogText.c_str());
	}
	else
	{
		m_layout->getChildById(1)->setVisible(false);
		m_layout->getChildById(2)->setVisible(false);
	}
}

void GuideView::addMaskLayer()
{
	auto winSize = CCDirector::sharedDirector()->getWinSize();

	CCLayerColor *mask = CCLayerColor::create(ccc4(0, 0, 0, 175));
	mask->setContentSize(winSize);

	CCLayerColor *stencil = CCLayerColor::create(ccc4(0, 0, 0, 255));
	stencil->setContentSize(m_targetRect.size);
	stencil->setPosition(m_targetRect.origin);

	auto clippingNode = CCClippingNode::create();
	clippingNode->setStencil(stencil);
	clippingNode->setInverted(true);
	clippingNode->addChild(mask);

	addChild(clippingNode);
}

bool GuideView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (isTargetArea(pTouch->getLocation()))
	{
		removeFromParent();
		return false;
	}
	return true;
}

void GuideView::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	return;
	CCPoint startPos = pTouch->getStartLocation();
	CCPoint curPos = pTouch->getLocation();
	if (isTargetArea(startPos) && isTargetArea(curPos))
	{
		removeFromParent();
	}
}

bool GuideView::isTargetArea(cocos2d::CCPoint worldPos)
{
	CCPoint pos = convertToNodeSpace(worldPos);
	return m_targetRect.containsPoint(pos);
}