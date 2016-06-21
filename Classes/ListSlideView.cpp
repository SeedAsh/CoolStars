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
, m_speed(0)
, m_scrollTime(0)
{
}

bool ListSlideView::init()
{
	ListView::init();
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
	else if (isOutOfRange())
	{
		m_speed = 0;
	}
	else if (fabs(m_speed) > speedPrec)
	{
		m_speed -= dt * m_speed * 2;
		CCPoint offset = ccp(0, m_speed * dt);
		doMove(offset);
	}
}

void ListSlideView::onTouchBegan(cocos2d::CCTouch *pTouch)
{
	m_speed = 0;
	m_scrollTime = 0;
}

void ListSlideView::onTouchMoved(cocos2d::CCTouch *pTouch)
{

}

void ListSlideView::onTouchEnded(cocos2d::CCTouch *pTouch)
{
	static float maxSpeed = 1000;
	static float minSpeed = 100;

	auto startPos = pTouch->getStartLocation();
	auto curPos = pTouch->getLocation();

	m_speed = (curPos.y - startPos.y) / m_scrollTime;
	if (fabs(m_speed) > maxSpeed)
	{
		m_speed = m_speed > 0 ? maxSpeed : -maxSpeed;
	}
	if (fabs(m_speed) < minSpeed)
	{
		m_speed = 0;
	}
}
