#ifndef __MENU_ADDNEWGLASSES__
#define __MENU_ADDNEWGLASSES__

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
#include "../entity/Glasses.h"

class Menu_AddNewGlasses : public MenuBase
{
public:
	Menu_AddNewGlasses();
	~Menu_AddNewGlasses();

	virtual void Init();
	void Render(CPUTRenderParameters &renderParams);
	virtual void HandleCPUTEvent(int eventID, int controlID, CPUTControl *control);
	virtual void ActivationChanged(bool active);
private:
	void DrawGUI(CPUTRenderParameters &renderParams);
	void UpdateLayout(CPUTRenderParameters &renderParams);
};

#endif __MENU_ADDNEWGLASSES__