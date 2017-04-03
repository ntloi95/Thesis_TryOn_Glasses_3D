//--------------------------------------------------------------------------------------
// Copyright 2013 Intel Corporation
// All Rights Reserved
//
// Permission is granted to use, copy, distribute and prepare derivative works of this
// software for any purpose and without fee, provided, that the above copyright notice
// and this statement appear in all copies.  Intel makes no representations about the
// suitability of this software for any purpose.  THIS SOFTWARE IS PROVIDED "AS IS."
// INTEL SPECIFICALLY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, AND ALL LIABILITY,
// INCLUDING CONSEQUENTIAL AND OTHER INDIRECT DAMAGES, FOR THE USE OF THIS SOFTWARE,
// INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PROPRIETARY RIGHTS, AND INCLUDING THE
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  Intel does not
// assume any responsibility for any errors which may appear in this software nor any
// responsibility to update it.
//--------------------------------------------------------------------------------------
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

enum GlassesPreviewMode
{
	GlassesPreviewMode_ApproveScan,
	GlassesPReviewMode_ViewScan
};

class Menu_GlassesPreview : public MenuBase
{
public:

	Menu_GlassesPreview();
	~Menu_GlassesPreview();

	virtual void Init();

	void Update(float dt);
	void Render(CPUTRenderParameters &renderParams);

	void SetGlassesMode(GlassesPreviewMode mode);

	void LoadGlassesObj(std::string filename, bool absoluteFilename = false, bool forceReload = false);

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

	GlassesPreviewMode mMode;

	void MoveUserData(const char *srcObjFilename, const char *dstObjFilename);
};


#endif