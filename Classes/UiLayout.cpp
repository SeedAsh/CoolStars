#include "UiLayout.h"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"
USING_NS_CC;
using namespace std;
using namespace rapidxml;

using namespace std;
UiLayout *UiLayout::create(const char *xmlPath)
{
	auto layout = new UiLayout(xmlPath);
	layout->init();
	layout->autorelease();
	return layout;
}

bool UiLayout::init()
{
	file<> fdoc(m_path.c_str());
	std::cout << fdoc.data() << std::endl;
	xml_document<> doc;
	doc.parse<0>(fdoc.data());

	xml_node<> *layout = doc.first_node();
	checkXml(layout);

	CCSize size;
	size.width = atof(layout->first_attribute("width")->value());
	size.height = atof(layout->first_attribute("height")->value());
	setContentSize(size);
	m_menu = CCMenu::create();
	m_menu->setPosition(ccp(0, 0));
	addChild(m_menu, 1);

	for (auto node = layout->first_node(); node != NULL; node = node->next_sibling())
	{
		createWidget(node);
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	setPosition(ccp(winSize.width * 0.5f, winSize.height * 0.5f));
	setAnchorPoint(ccp(0.5f, 0.5f));

	return true;
}

void UiLayout::checkXml(rapidxml::xml_node<> *layout)
{
	vector<int> ids;
	for (auto node = layout->first_node(); node != NULL; node = node->next_sibling())
	{
		int id = atoi(node->first_node("id")->value());
		auto iter = find(ids.begin(), ids.end(), id);
		if (iter == ids.end())
		{
			ids.push_back(id);
		}
		else
		{
			assert(false && "save id!!!");
		}
	}
}

void UiLayout::createWidget(rapidxml::xml_node<> *node)
{
	int id = atoi(node->first_node("id")->value());
	float x = atof(node->first_node("x")->value());
	float y = atof(node->first_node("y")->value());

	string widgetName = node->name();
	if (widgetName == "label")
	{
		string text = node->first_node("text")->value();
		auto pLabel = CCLabelTTF::create(text.c_str(), "Arial", 24);
		addChild(pLabel, 0, id);
		pLabel->setPosition(ccp(x, y));
	}
	else if (widgetName == "button")
	{
		string normalPath = node->first_node("normal")->value();
		string selectedPath = node->first_node("selected")->value();
		string disabledPath = node->first_node("disabled")->value();

		//ѡ��״ֱ̬��ʹ�÷Ŵ������ͼƬ
		auto normalSpr = CCSprite::create(normalPath.c_str());
		auto selectedSpr = CCSprite::create(normalPath.c_str());
		selectedSpr->setScale(1.2f);
		CCMenuItemSprite* imageItem = CCMenuItemSprite::create(normalSpr, selectedSpr, this, NULL);

		/*
		CCMenuItemImage *imageItem = CCMenuItemImage::create(
			normalPath.c_str(),
			selectedPath.c_str(),
			disabledPath.c_str(),
			this,
			NULL);
			*/

		m_menu->addChild(imageItem);
		m_menuItems[id] = imageItem;
		imageItem->setPosition(ccp(x, y));
	}
	else if (widgetName == "image")
	{
		string path = node->first_node("path")->value();
		CCSprite *spr = CCSprite::create(path.c_str());
		addChild(spr, 0, id);
		spr->setPosition(ccp(x, y));
	}
	else
	{
		assert(false && "no this widget");
	}
}

CCNode *UiLayout::getChildById(int id)
{
	auto iter = m_menuItems.find(id);
	if (iter != m_menuItems.end())
	{
		return iter->second;
	}
	else
	{
		return getChildByTag(id);
	}

}
