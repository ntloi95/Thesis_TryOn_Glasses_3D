#ifndef __MENU_NEWUSERREGISTER__
#define __MENU_NEWUSERREGISTER__

#include "CPUT.h"
#include "CPUTRenderTarget.h"
#include "CPUTScene.h"
#include "CPUTText.h"
#include "CPUTModel.h"
#include "CPUTSoftwareMesh.h"
#include "CPUTCamera.h"
#include "CPUTAssetSet.h"
#include "CPUTCheckbox.h"
#include "CPUTSprite.h"
#include "MenuBase.h"
#include "../entity/User.h"

class Menu_NewUserRegister : public MenuBase
{
public:
	Menu_NewUserRegister();
	~Menu_NewUserRegister();

	virtual void Init();
	void Render(CPUTRenderParameters &renderParams);
	virtual void HandleCPUTEvent(int eventID, int controlID, CPUTControl *control);
	virtual void ActivationChanged(bool active);
private:
	void DrawGUI(CPUTRenderParameters &renderParams);
	void UpdateLayout(CPUTRenderParameters &renderParams);
};

#endif __MENU_NEWUSERREGISTER__