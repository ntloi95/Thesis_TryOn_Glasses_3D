#ifndef __MENU_FUNCTION__
#define __MENU_FUNCTION__

#include "MenuBase.h"
#include "CPUTSprite.h"
#include "../SampleUtil.h"
#include "CPUTCamera.h"
#include "CPUTAssetSet.h"
#include "CPUTCheckbox.h"
#include <string>

class Menu_Function : public MenuBase
{
public:
	Menu_Function();
	~Menu_Function();

	virtual void Init();

	virtual void HandleCPUTEvent(int eventID, int controlID, CPUTControl *control);
	virtual void ActivationChanged(bool active);
};

#endif __MENU_FUCTION__