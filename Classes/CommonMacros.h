#ifndef __COMMONMACROS_H__
#define __COMMONMACROS_H__

#define MAX_ACTIVE_PETS_AMOUNT 4
#define COLOR_AMOUNT 5
#define COMMON_PETS_AMOUNT 11
#define PETS_AMOUNT (COLOR_AMOUNT * COMMON_PETS_AMOUNT)
#define MAX_PET_LEVEL 5

#define MAX_RUNESTORN_AMOUNT 5
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
	kPanelTouchPriority = -10,
	kStageStarsTouchPriority = -20,
	kStageUiTouchPriority = -30,
	kStageMaskTouchPriority = -40,
	kDialogTouchPriority = -50,
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

enum GoodsType
{
	kGoodsDiamond,
	kGoodsFood,
	kGoodsStrength,
	kGoodsRuneStone,
	kGoodsKey,
	kGoodsProps,
	kGoodsPets,
	kGoodsStep,
};

//消费方式
enum ConsumeType
{
	kConsumeDiamond,
	kConsumeMoney,
};
#define NOTIFY_VIEWS(_FUNC_ ,...)						\
for (size_t index = 0; index < m_views.size(); ++index) \
{														\
	m_views[index]->_FUNC_(__VA_ARGS__);				\
}

#endif