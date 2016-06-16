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
	kLinkErase = 1, //��������
	kNeightbourErase,		//�������������� ��������
	kScaleErase,    //�������������＼�ܣ��������ǣ� ��������
};
#endif