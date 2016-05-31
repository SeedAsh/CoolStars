#include "AppDelegate.h"
#include "MenuScene.h"
#include "GameData.h"
#include "UserInfo.h"
#include "SoundMgr.h"
#include "MyPurchase.h"
#include "DataManager.h"
#include "DataCheck.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	
	pDirector->setOpenGLView(pEGLView);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	pEGLView->setFrameSize(480, 800);
#endif
	CCSize designSize = CCSizeMake(480, 800);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionFixedWidth);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WP8 )
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionFixedWidth);
#else
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionFixedWidth);
#endif
	MyPurchase::sharedPurchase()->loadIAPPlugin();
	GameData::getInstance()->preloadData();
	UserInfo::init();
	SoundMgr::init();
	//不强制复制数据库，若数据库升级，再强制复制，此时考虑若是有写数据库操作，怎么备份已经有的数据或写其它数据库或写其它文件实现，如CCUserDefaultEx
	DataManagerSelf->UnzipGameData(false);
	DataManagerSelf->LoadData();

	//对数据库数据进行数据校验 正式版本着取消校验
	DataCheck check;
	check.checkDataBase();

    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = MenuScene::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
