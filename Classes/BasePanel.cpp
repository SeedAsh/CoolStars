#include "BasePanel.h"
#include "UiLayout.h"
#include "CommonMacros.h"
USING_NS_CC;
using namespace std;

BasePanel::BasePanel()
: m_touchPriority(kMainMenuTouchPriority)
, m_panelId(kDefaultPanel)
, m_usage(0)
{

}

bool BasePanel::init()
{
	return true;
}

