#ifndef __COMMONMACROS_H__
#define __COMMONMACROS_H__

enum Colors
{
	kColorRandom,

	kColorRed,
	kColorYellow,
	kColorBlue,
	kColorGreen,
	kColorPurple,

	kColorAmount,
};

#define MaxActivePetsAmount 4
#define CommonPetsAmount 8

enum TouchPriority
{
	kMainMenuTouchPriority = -10,
	kDialogMenuTouchPriority = -50,
};

enum EraseType
{
	kLinkErase = 1, //连接消除
	kNeightbourErase,		//连接消除的星星 附近消除
	kScaleErase,    //区域消除：宠物技能，增益星星， 道具消除
};
#endif