#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__
#include "cocos2d.h"
#include <deque>

class BasePanel;

struct PanelRecord
{
	int panelId;
	int usage;
};

class MainScene
	: public cocos2d::CCScene
{
public:
	static cocos2d::CCScene* theScene();
	CREATE_FUNC(MainScene);
	bool init();

	void addUiPanel(BasePanel *panel);
	void showPanel(int panelId);
	void backPanel();
private:
	MainScene(){}
	~MainScene(){}
	void initMainLayout();
private:
	static cocos2d::CCScene *s_scene;
	std::deque<PanelRecord> m_panelRecord;
};
#endif