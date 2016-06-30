#ifndef __GUIDEMACROS_H__
#define __GUIDEMACROS_H__

#define kNotTriggerGuide 0
enum GuideStartAction
{
	kGuideStart_common = 1,

	kGuideStart_mainMenu_in = 10,

	kGuideStart_preStage_in = 20,

	kGuideStart_stage_in = 30,
	kGuideStart_stage_initStarsFinished,
	kGuideStart_stage_petFullPower,
	kGuideStart_stage_gameOver,

	kGuideStart_ranking_in = 50,
};

enum GuideEndAction
{
	kGuideEnd_common = 1,

	kGuideEnd_mainMenu_in = 10,

	kGuideEnd_preStage_in = 20,

	kGuideEnd_stage_in = 30,
	kGuideEnd_star_clicked,
	kGuideEnd_pet_clicked,
	kGuideEnd_stage_petFullPower,
	kGuideEnd_stage_gameOver,

	kGuideEnd_ranking_in = 50,
};
#endif