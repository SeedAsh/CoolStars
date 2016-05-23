#include "SoundMgr.h"
#include "cocos2d.h"
#include "CCUserDefaultEx.h"

USING_NS_CC;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
const char* SoundMgr::sEffectFileMap[EFFECT_MAX] = {"sounds/pop.wav","sounds/select.wav",
	"sounds/Props_Bomb.wav","sounds/Props_Paint.wav","sounds/Props_Rainbow.wav","sounds/readygo.wav","sounds/NextGameRound.wav"};
const char* SoundMgr::sMusicFileMap[MUISC_MAX] = {"sounds/music.wav"};
const char* SoundMgr::sComboFileMap[COMBO_MAX] = {"sounds/combo_1.wav","sounds/combo_2.wav","sounds/combo_3.wav"};
const char* SoundMgr::sFireFileMap[FIRE_MAX] = {"sounds/fireworks_01.wav","sounds/fireworks_02.wav","sounds/fireworks_03.wav"};

#else
const char* SoundMgr::sEffectFileMap[EFFECT_MAX] = {"sounds/pop.ogg","sounds/select.ogg",
	"sounds/Props_Bomb.ogg","sounds/Props_Paint.ogg","sounds/Props_Rainbow.ogg","sounds/readygo.ogg","sounds/NextGameRound.ogg"};
const char* SoundMgr::sMusicFileMap[MUISC_MAX] = {"sounds/music.ogg"};
const char* SoundMgr::sComboFileMap[COMBO_MAX] = {"sounds/combo_1.ogg","sounds/combo_2.ogg","sounds/combo_3.ogg"};
const char* SoundMgr::sFireFileMap[FIRE_MAX] = {"sounds/fireworks_01.ogg","sounds/fireworks_02.ogg","sounds/fireworks_03.ogg"};
#endif
bool SoundMgr::sMute = false;
void SoundMgr::init(){
	for(int i = 0; i < sizeof(sEffectFileMap)/sizeof(sEffectFileMap[0]); i++) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(sEffectFileMap[i]);
	}
	for(int i = 0; i < sizeof(sComboFileMap)/sizeof(sComboFileMap[0]); i++) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(sComboFileMap[i]);
	}	
	for(int i = 0; i < sizeof(sFireFileMap)/sizeof(sFireFileMap[0]); i++) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(sFireFileMap[i]);
	}	
	sMute = CCUserDefaultEx::sharedUserDefault()->getBoolForKey("key-sound-muted");
}

void SoundMgr::playMusic( MusicId id ){
	if (sMute) {
		return;
	}
	if (id < MUISC_MAX) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(sMusicFileMap[id],true);
	}
}

void SoundMgr::playEffect( EffectId id ){
	if (sMute) {
		return;
	}
	if (id < EFFECT_MAX) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(sEffectFileMap[id]);
	}
}

void SoundMgr::playCombo(ComboId id){
	if (sMute){
		return;
	}
	ComboId playId = COMBO_MAX;
	if (id >= COMBO_1 && id < COMBO_MAX){
		playId = id;
	}else{
		srand(time(NULL));
		playId = (ComboId)(rand() % COMBO_MAX);
	}
	if (playId < COMBO_MAX){
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(sComboFileMap[playId]);
	}
}

void SoundMgr::stopMusic(){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void SoundMgr::setMute( bool mute ){
	if (mute) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}else{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
	sMute = mute;
	CCUserDefaultEx::sharedUserDefault()->setBoolForKey("key-sound-muted", mute);
	CCUserDefaultEx::sharedUserDefault()->flush();
}


void SoundMgr::playFire(FireId id){
	if (sMute){
		return;
	}
	FireId playId = FIRE_MAX;
	if (id >= FIRE_1 && id < FIRE_MAX){
		playId = id;
	}else{
		srand(time(NULL));
		playId = (FireId)(rand() % FIRE_MAX);
	}
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(sFireFileMap[playId]);
}

bool SoundMgr::isMute(){
	return sMute;
}

SoundMgr::~SoundMgr(){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->end();
}
