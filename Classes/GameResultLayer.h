#ifndef __GAMERESULTLAYER_H__
#include "ScaleDialog.h"
#define __GAMERESULTLAYER_H__

class GameWinLayer : public ScaleDialog
{
public:
	CREATE_FUNC(GameWinLayer);
	bool init();
private:
	void toMainMenu(CCObject *pSender);
	void toNextStage(CCObject *pSender);
};


class GameFailLayer : public ScaleDialog
{
public:
	CREATE_FUNC(GameFailLayer);
	bool init();
private:
	void toMainMenu(CCObject *pSender);
	void replay(CCObject *pSender);
};
#endif