#ifndef __COMMONMACROS_H__
#define __COMMONMACROS_H__

#define MAX_ACTIVE_PETS_AMOUNT 4
#define COMMON_PETS_AMOUNT 8
#define COLOR_AMOUNT 5

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
};

enum EraseType
{
	kLinkErase = 1, //连接消除
	kNeightbourErase,		//连接消除的星星 附近消除
	kScaleErase,    //区域消除：宠物技能，增益星星， 道具消除
};
#endif