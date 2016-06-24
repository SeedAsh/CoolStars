#include "UiLayout.h"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "EmptyBox.h"
#include "cocos-ext.h"
USING_NS_CC;
using namespace std;
using namespace rapidxml;
using namespace extension;
using namespace std;

UiLayout::UiLayout(const char *xmlPath)
: m_path(xmlPath)
, m_menu(NULL)
, m_menuTouchPriority(-128)
{

}

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

	return true;
}

void UiLayout::setMenuTouchPriority(int touchPriority)
{
	if (m_menu)
	{
		m_menu->setTouchPriority(touchPriority);
	}
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
	float anchorPtX = atof(node->first_node("anchorPtX")->value());
	float anchorPtY = atof(node->first_node("anchorPtY")->value());
	float scale = atof(node->first_node("scale")->value());

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

		//选中状态直接使用放大的正常图片
		auto normalSpr = CCSprite::create(normalPath.c_str());
		auto pt = normalSpr->getAnchorPoint();
		CCLOG("%f, %f", pt.x, pt.y);
		auto selectedSpr = CCSprite::create(normalPath.c_str());
		CCLOG("%f, %f", pt.x, pt.y);

		float scale = 1.1f;
		selectedSpr->setScale(scale);
		
		CCMenuItemSprite* imageItem = CCMenuItemSprite::create(normalSpr, selectedSpr, this, NULL);
		selectedSpr->setAnchorPoint(ccp((scale - 1.0f) / 2, (scale - 1.0f) / 2));
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
		spr->setScale(scale);
	}
	else if (widgetName == "emptyBox")
	{
		EmptyBox *node = EmptyBox::create();
		addChild(node, 0, id);
		node->setPosition(ccp(x, y));
	}
	else if (widgetName == "imageNum")
	{
		string text = node->first_node("num")->value();
		string path = node->first_node("path")->value();
		int amount = atoi(node->first_node("amount")->value());
		auto size = CCSprite::create(path.c_str())->getContentSize();
		auto pLabel = CCLabelAtlas::create(text.c_str(), path.c_str(), size.width / amount, size.height, '0');

		addChild(pLabel, 0, id);
		pLabel->setPosition(ccp(x, y));
	}
	else if (widgetName == "animation")
	{
		string path = node->first_node("path")->value();
		CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(path.c_str());
		int pos1 = path.rfind("/");
		int pos2 = path.rfind(".");
		string armatureName = path.substr(pos1 + 1, pos2 - pos1 - 1);
		auto armature = CCArmature::create(armatureName.c_str());
		string movementName = node->first_node("movement")->value();
		if (movementName == "0")
		{
			armature->getAnimation()->playWithIndex(0);
		}
		else
		{
			armature->getAnimation()->play(movementName.c_str());
		}
		addChild(armature, 0, id);
		armature->setPosition(ccp(x, y));
		armature->setScale(scale);
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
