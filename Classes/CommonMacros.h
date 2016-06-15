#ifndef __COMMONMACROS_H__
#define __COMMONMACROS_H__

enum Colors
{
	kColorRed,
	kColorYellow,
	kColorBlue,
	kColorGreen,
	kColorPurple,

	kColorRandom,
};

#define MaxActivePetsAmount 4
#define CommonPetsAmount 8

enum TouchPriority
{
	kMainMenuTouchPriority = -10,
	kDialogMenuTouchPriority = -50,
};
#endif