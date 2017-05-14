#ifndef __MENU_VIEW_USER_LIST__
#define __MENU_VIEW_USER_LIST__

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

class Menu_ViewUserList : public MenuBase
{
public:
	Menu_ViewUserList();
	~Menu_ViewUserList();

	virtual void Init();
	void Render(CPUTRenderParameters &renderParams);
	virtual void HandleCPUTEvent(int eventID, int controlID, CPUTControl *control);
	virtual void ActivationChanged(bool active);
private:
	void DrawGUI(CPUTRenderParameters &renderParams);
	void UpdateLayout(CPUTRenderParameters &renderParams);
};

#endif __MENU_VIEW_USER_LIST__