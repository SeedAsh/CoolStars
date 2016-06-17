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
	kLinkErase = 1, //��������
	kNeightbourErase,		//�������������� ��������
	kScaleErase,    //�������������＼�ܣ��������ǣ� ��������
};
#endif