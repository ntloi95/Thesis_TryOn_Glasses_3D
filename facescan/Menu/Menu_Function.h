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
#include <map>
const int RECENT_FUNCTION_COUNT = 4;

class Menu_Function : public MenuBase
{
public:
	Menu_Function();
	~Menu_Function();

	virtual void Init();
	void Render(CPUTRenderParameters &renderParams);
	virtual void HandleCPUTEvent(int eventID, int controlID, CPUTControl *control);
	virtual CPUTEventHandledCode HandleMouseEvent(int x, int y, int wheel, CPUTMouseState state, CPUTEventID message);
	virtual void ActivationChanged(bool active);
private:
	void DrawGUI(CPUTRenderParameters &renderParams);
	void UpdateLayout(CPUTRenderParameters &renderParams);
	float mImGUIMenuWidth;
	float mWindowPadding;
	std::map<int, std::string> mTooltip;
	std::map<int, std::string> mNameFunction;
	int mRecentFunction[RECENT_FUNCTION_COUNT];
};

#endif __MENU_FUCTION__