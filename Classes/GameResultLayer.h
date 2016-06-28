#ifndef __GAMERESULTLAYER_H__
#define __GAMERESULTLAYER_H__
#include "ScaleDialog.h"
#include "BasePanel.h"

class UiLayout;
class GameWinLayer : public BasePanel
{
public:
	CREATE_FUNC(GameWinLayer);
	bool init();
private:
	void initLayout();

	void onConfirmBtnClicked(CCObject *pSender);
private:
	UiLayout *m_layout;
};


class GameFailLayer : public BasePanel
{
public:
	CREATE_FUNC(GameFailLayer);
	bool init();
private:
	void initLayout();
	void onConfirmBtnClicked(CCObject *pSender);
	void onBuyPetBtnClicked(CCObject *pSender);
private:
	UiLayout *m_layout;

};
#endif