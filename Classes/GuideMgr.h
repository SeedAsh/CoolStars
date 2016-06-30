#ifndef __GUIDEMGR_H__
#define __GUIDEMGR_H__
#include "cocos2d.h"
#include <functional>
#include "GuideMacros.h"
class GuideMgr
{
public:
	static GuideMgr *theMgr();
	GuideMgr();
	void init();

	void startGuide(int startAction, std::function<void()> callback);
	void endGuide(int endAction);

private:
	void finishGuide();

public:
	std::vector<int> m_finishedGuides;
	int m_curGuideId;
};
#endif