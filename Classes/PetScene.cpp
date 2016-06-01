#include "PetScene.h"
USING_NS_CC;
using namespace std;

bool PetScene::init()
{
	auto sp = CCSprite::create("exitbg.png");
	auto size = sp->getContentSize();
	setContentSize(size);

	ScaleDialog::init();

	sp->setPosition(ccp(size.width * 0.5f, size.height * 0.5f));
	addChild(sp);

	return true;
}