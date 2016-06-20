#include "ListView.h"
USING_NS_CC;
using namespace std;
using namespace std::placeholders;


ListView *ListView::create(const CCSize &size)
{
	ListView *view = new ListView(size);
	view->init();
	view->autorelease();
	return view;
}


ListView::ListView(const CCSize &size)
: m_size(size)
, m_touchPriority(0)
, m_spacing(0)
{
	
}

bool ListView::init()
{
	setContentSize(m_size);

	CCLayerColor *maskNode = CCLayerColor::create(ccc4(255, 255, 0, 75));
	maskNode->setContentSize(m_size);
	addChild(maskNode);

	CCLayerColor *back = CCLayerColor::create(ccc4(125, 0, 0, 255));
	back->setContentSize(m_size);
	m_clippingNode = CCClippingNode::create();
	m_clippingNode->setInverted(false);
	m_clippingNode->setAlphaThreshold(1.0f);
	m_clippingNode->setStencil(back);
	addChild(m_clippingNode);

	m_content = CCNode::create();
	m_clippingNode->addChild(m_content);

	return true;
}

int ListView::addNode(cocos2d::CCNode *node)
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

void ListView::removeNode(int index)
{
	auto node = getNode(index);
	if (node)
	{
		node->removeFromParent();
	}
}

cocos2d::CCNode *ListView::getNode(int index)
{
	int nodeAmount = count();
	if (index < 0 || index > nodeAmount - 1) return NULL;

	return m_nodes[index];
}

void ListView::onEnter()
{
	CCNode::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_touchPriority, true);
}

void ListView::onExit()
{
	CCNode::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void ListView::clear()
{
	m_content->removeAllChildren();	
	m_nodes.clear();
}

bool ListView::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	m_beganPt = pTouch->getLocation();
	return true;
}


void ListView::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	CCSize contentSize = m_content->getContentSize();
	if (contentSize.height < m_size.height) return;

	auto pos = pTouch->getLocation();
	auto offSetY = pos.y - m_beganPt.y;
	CCPoint contentPos = m_content->getPosition();
	
	float maxY = 0;
	float minY = m_size.height - contentSize.height;
	float newY = min(max(contentPos.y + offSetY, minY), maxY);

	//CCMoveTo *moveTo = CCMoveTo::create(0.1f, ccp(0, newY));
	//m_content->runAction(CCEaseSineIn::create(moveTo));

	m_content->setPosition(ccp(0, newY));
	m_beganPt = pos;
}

void ListView::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}