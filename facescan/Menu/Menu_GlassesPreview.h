#ifndef __MENU_GLASSESPREVIEW__
#define __MENU_GLASSESPREVIEW__

#include "MenuBase.h"
#include "CPUTSprite.h"
#include "../SampleUtil.h"
#include "CPUTCamera.h"
#include "CPUTAssetSet.h"
#include "CPUTCheckbox.h"
#include "../CFaceModel.h"
#include <string>

// Only one mode in this Menu View
/*enum GlassesPreviewMode
{
	GlassesPreviewMode_ApproveScan,
	GlassesPReviewMode_ViewScan
};*/

class Menu_GlassesPreview : public MenuBase
{
public:

	Menu_GlassesPreview();
	~Menu_GlassesPreview();

	virtual void Init();

	void Update(float dt);
	void Render(CPUTRenderParameters &renderParams);

	//void SetGlassesMode(GlassesPreviewMode mode);

	void LoadFaceObj(std::string filename, bool absoluteFilename = false, bool forceReload = false);

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

	CFaceModel mFaceModel;

	CPUTCheckbox *mLandmarkCheckbox;

	//GlassesPreviewMode mMode;

	void MoveUserData(const char *srcObjFilename, const char *dstObjFilename);
};


#endif