#ifndef _SOUNDMGR_H_
#define _SOUNDMGR_H_
#include "SimpleAudioEngine.h"

class SoundMgr {
public:
	enum EffectId {
		EFFECT_BROKEN = 0,
		EFFECT_CLICK,
		EFFECT_PRO_BOMB,
		EFFECT_PRO_PAINT,
		EFFECT_PRO_RAINBOW,
		EFFECT_READY_GO,
		EFFECT_NEXT,
		EFFECT_MAX
	};
	
	enum ComboId {
		COMBO_1 = 0,
		COMBO_2,
		COMBO_3,
		COMBO_MAX
	};
	enum FireId {
		FIRE_1 = 0,
		FIRE_2,
		FIRE_3,
		FIRE_MAX
	};
	enum MusicId {
		MUSIC_BACKGROUND = 0,
		MUISC_MAX
	};
private:
	SoundMgr(){}
	~SoundMgr();
	static const char* sEffectFileMap[EFFECT_MAX];
	static const char* sMusicFileMap[MUISC_MAX];
	static const char* sComboFileMap[COMBO_MAX];
	static const char* sFireFileMap[FIRE_MAX];
	static bool sMute;
public:
	static void init();
	static void playEffect(EffectId id);
	static void playMusic(MusicId id);
	static void playFire(FireId id);
	static void playCombo(ComboId);
	static void stopMusic();
	static void setMute(bool mute);
	static bool isMute();
};



#endif