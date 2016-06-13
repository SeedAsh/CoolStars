#include "EmptyBox.h"
using namespace std;
USING_NS_CC;

EmptyBox *EmptyBox::create()
{
    EmptyBox *node = new EmptyBox();
    node->init();
    node->autorelease();
    return node;
}

bool EmptyBox::init()
{
    return true;
}

EmptyBox::EmptyBox()
:m_node(NULL)
{
    
}

void EmptyBox::setNode(cocos2d::CCNode* node)
{
    removeNode();
    addChild(node);
    setContentSize(node->getContentSize());
}

void EmptyBox::removeNode()
{
    if(m_node)
    {
        setContentSize(CCSize(0, 0));
        m_node->removeFromParent();
        m_node = NULL;
    }
}


