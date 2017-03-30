#ifndef __MENU_GLASSESPREVIEW__
#define __MENU_GLASSESPREVIEW__

#include "MenuBase.h"
#include "CPUTSprite.h"
#include "../SampleUtil.h"
#include "CPUTCamera.h"
#include "CPUTAssetSet.h"
#include "CPUTCheckbox.h"
#include "../CGlassesModel.h"
#include <string>

class Menu_GlassesPreview : public MenuBase
{
public:

	Menu_GlassesPreview();
	~Menu_GlassesPreview();

	virtual void Init();

	void Update(float dt);
	void Render(CPUTRenderParameters &renderParams);

	void LoadGlassesObj(std::string filename, bool absoluteFileName = false, bool forceReload = false);

	virtual void HandleCPUTEvent(int eventID, int controlID, CPUTControl *control);
	virtual CPUTEventHandledCode HandleMouseEvent(int x, int y, int wheel, CPUTMouseState state, CPUTEventID message);
	virtual void ActivationChanged(bool active);

	// Add-on
	void PrintLandmark();

private:

	CPUTModel *mBoxModel;
	CPUTAssetSet *mCommonSet;

	CPUTModel *displayModel;
	CPUTCameraModelViewer *cameraController;

	std::string mModelFilename;

	CGlassesModel mGlassesModel;

	CPUTCheckbox *mLandmarkCheckbox;

	void MoveUserData(const char *srcObjFilename, const char *dstObjFilename);
};


#endif