#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__
#include "cocos2d.h"
#include <deque>

class BasePanel;
class ScaleDialog;
struct PanelRecord
{
	int panelId;
	int usage;
};

class MainScene
	: public cocos2d::CCScene
{
public:
	static MainScene* theScene();
	bool init();

	void showPanel(int panelId, bool closeBehind = true);
	void showDialog(ScaleDialog *dialog);
	void backPanel();
	void clearPanelRecord(){ m_panelRecord.clear(); }
private:
	MainScene(){}
	~MainScene(){}
	void addUiPanel(BasePanel *panel, bool closeBehind);
	void recordPanel(int panelId, int usage);
private:
	static MainScene *s_scene;
	std::deque<PanelRecord> m_panelRecord;
	std::vector<BasePanel *>m_panels;
	
	cocos2d::CCNode *m_bkLayer;
	cocos2d::CCNode *m_uiLayer;
	cocos2d::CCNode *m_dialogLayer;

};

#endif