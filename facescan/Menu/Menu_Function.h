#ifndef __MENU_FUNCTION__
#define __MENU_FUNCTION__

#include "MenuBase.h"
#include <string>
#include <vector>
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
#include "../FaceMap/CPipeline.h"
#include "../CFaceModel.h"
#include "../CGlassesModel.h"
#include "../SampleUtil.h"
const int RECENT_FUNCTION_COUNT = 7;
#define USER_REGISTER 100
#define VIEW_LIST_USER 111
#define SCAN_NEW 123
#define SCAN_EDIT 124
#define GLASSES_REGISTER 125
#define VIEW_LIST_GLASSES 126
#define GLASSES_EDIT 127
#define GLASSES_REMOVE 128

class Menu_Function : public MenuBase
{
public:
	Menu_Function();
	~Menu_Function();

	virtual void Init();
	void Render(CPUTRenderParameters &renderParams);
	virtual void HandleCPUTEvent(int eventID, int controlID, CPUTControl *control);
	virtual void ActivationChanged(bool active);
private:
	void DrawGUI(CPUTRenderParameters &renderParams);
	void UpdateLayout(CPUTRenderParameters &renderParams);
	float mImGUIMenuWidth;
	float mWindowPadding;
};

#endif __MENU_FUCTION__