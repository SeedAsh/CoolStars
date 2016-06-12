#ifndef __UILAYOUT_H__
#define __UILAYOUT_H__
#include "cocos2d.h"
#include <unordered_map>
#include "rapidxml/rapidxml.hpp"

class UiLayout
	: public cocos2d::CCNode
{
public:
	static UiLayout *create(const char *xmlPath);
	cocos2d::CCNode *getChildById(int id);
private:
	UiLayout(const char *xmlPath) : m_path(xmlPath){}
	virtual bool init();
	void createWidget(rapidxml::xml_node<> *node);
	void checkXml(rapidxml::xml_node<> *layout);
private:
	std::string m_path;
	std::unordered_map<int, cocos2d::CCMenuItemSprite *> m_menuItems;
	cocos2d::CCMenu *m_menu;
	
};
#endif