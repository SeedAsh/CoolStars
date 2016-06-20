#include "ListSlideView.h"
USING_NS_CC;
using namespace std;
using namespace std::placeholders;


ListSlideView *ListSlideView::create(const CCSize &size)
{
	ListSlideView *view = new ListSlideView(size);
	view->init();
	view->autorelease();
	return view;
}


ListSlideView::ListSlideView(const CCSize &size)
: ListView(size)
, m_touchPriority(0)
, m_spacing(0)
, m_speed(0)
, m_scrollTime(0)
, m_isTouching(false)
{
	
}

bool ListSlideView::init()
{
	setContentSize(m_size);

	CCLayerColor *maskNode = CCLayerColor::create(ccc4(0, 255, 0, 75));
	maskNode->setContentSize(m_size);
	//addChild(maskNode);

	CCLayerColor *back = CCLayerColor::create(ccc4(125, 0, 0, 255));
	back->setContentSize(m_size);
	m_clippingNode = CCClippingNode::create();
	m_clippingNode->setInverted(false);
	m_clippingNode->setAlphaThreshold(1.0f);
	m_clippingNode->setStencil(back);
	addChild(m_clippingNode);

	m_content = CCNode::create();
	m_clippingNode->addChild(m_content);
	
	scheduleUpdate();
	return true;
}

void ListSlideView::update(float dt)
{
	static const float speedPrec = 1.0f;

	if (m_isTouching)
	{
		m_scrollTime += dt;
	}
	else if (fabs(m_speed)>speedPrec)
	{
		m_speed -= dt * m_speed * 2;
		CCPoint offset = ccp(0, m_speed * dt);
		doMove(offset);
	}
}

int ListSlideView::addNode(cocos2d::CCNode *node)
{
	float contentHeight = m_content->getContentSize().height;
	float contentWidth = m_content->getContentSize().width;

	m_content->addChild(node);
	int height = contentHeight;
	if (!m_nodes.empty())
	{
		height += m_spacing;
	}
	node->setPosition(ccp(0, height));
	auto nodeSize = node->getContentSize();
	m_nodes.push_back(node);

	float maxWidth = max(contentWidth, nodeSize.width);
	float curHight = height + nodeSize.height;
	m_content->setContentSize(CCSize(maxWidth, curHight));

	m_content->setPosition(ccp(0, m_size.height - curHight));
	return m_nodes.size() - 1;
}

void ListSlideView::removeNode(int index)
{
	auto node = getNode(index);
	if (node)
	{
		node->removeFromParent();
	}
}

cocos2d::CCNode *ListSlideView::getNode(int index)
{
	int nodeAmount = count();
	if (index < 0 || index > nodeAmount - 1) return NULL;

	return m_nodes[index];
}

void ListSlideView::onEnter()
{
	CCNode::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_touchPriority, true);
}

void ListSlideView::onExit()
{
	CCNode::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void ListSlideView::clear()
{
	m_content->removeAllChildren();	
	m_nodes.clear();
}

void ListSlideView::doMove(cocos2d::CCPoint pt)
{
	CCSize contentSize = m_content->getContentSize();
	auto offSetY = pt.y;
	CCPoint contentPos = m_content->getPosition();
	float maxY = 0;
	float minY = m_size.height - contentSize.height;
	float newY = min(max(contentPos.y + offSetY, minY), maxY);

	m_content->setPosition(ccp(0, newY));
}

bool ListSlideView::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	auto localPos = convertToNodeSpace(pTouch->getLocation());
	auto size = getContentSize();
	CCRect rect(0, 0, size.width, size.height);
	if (!rect.containsPoint(localPos)) return false;
	m_speed = 0;
	m_scrollTime = 0;
	m_isTouching = true;
	return true;
}


void ListSlideView::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	CCSize contentSize = m_content->getContentSize();
	if (contentSize.height < m_size.height) return;

	auto curPos = pTouch->getLocation();
	auto prePos = pTouch->getPreviousLocation();

	doMove(ccpSub(curPos, prePos));
}

void ListSlideView::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	static float maxSpeed = 1000;
	static float minSpeed = 100;

	auto startPos = pTouch->getStartLocation();
	auto prePos = pTouch->getPreviousLocation();
	auto curPos = pTouch->getLocation();
	
	m_speed = (curPos.y - startPos.y) / m_scrollTime;
	if (fabs(m_speed) > maxSpeed)
	{
		m_speed = m_speed >0 ? maxSpeed : -maxSpeed;
	}
	if (fabs(m_speed) < minSpeed)
	{
		m_speed = 0;
	}

	m_isTouching = false;
}