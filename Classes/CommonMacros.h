#ifndef __COMMONMACROS_H__
#define __COMMONMACROS_H__

#define MAX_ACTIVE_PETS_AMOUNT 4
#define COLOR_AMOUNT 5
#define COMMON_PETS_AMOUNT 12 
#define PETS_AMOUNT (COLOR_AMOUNT * COMMON_PETS_AMOUNT)
#define MAX_PET_LEVEL 5
enum Colors
{
	kColorRandom,

	kColorRed,
	kColorYellow,
	kColorBlue,
	kColorGreen,
	kColorPurple,
};


enum TouchPriority
{
	kMainMenuTouchPriority = -10,
	kStageUiTouchPriority = -20,
	kDialogMenuTouchPriority = -50,
	kGuideTouchPriority = -70,
};

enum EraseType
{
	kLinkErase = 1, //连接消除
	kNeightbourErase,		//连接消除的星星 附近消除
	kScaleErase,    //区域消除：宠物技能，增益星星， 道具消除
};

enum PanelId
{
	kDefaultPanel,
	kMainMenu,
	kPetPanel,
	kShopPanel,
	kLotteryPanel,
	kRankingPanel,
	kPackagePanel,
	kPreStagePanel, 
	kStageView,
	kStageFailPanel,
	kStageWinPanel,

};

enum GameType
{
	kNormalType,
	kTreasureType,
};
#define NOTIFY_VIEWS(_FUNC_ ,...)						\
for (size_t index = 0; index < m_views.size(); ++index) \
{														\
	m_views[index]->_FUNC_(__VA_ARGS__);				\
}

#endif