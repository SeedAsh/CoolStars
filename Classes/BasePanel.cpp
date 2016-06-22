#include "BasePanel.h"
#include "UiLayout.h"
#include "CommonMacros.h"
USING_NS_CC;
using namespace std;

BasePanel::BasePanel()
: m_touchPriority(kMainMenuTouchPriority)
{

}

bool BasePanel::init()
{
	return true;
}

