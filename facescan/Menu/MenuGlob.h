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
#ifndef __MENU_GLOB__
#define __MENU_GLOB__

#include "Menu_Scan.h"
#include "Menu_FaceScanPreview.h"
#include "Menu_FaceMapping.h"
#include "Menu_LandmarkEdit.h"
#include "Menu_Function.h"
#include "Menu_GlassesPreview.h"
#include "Menu_AddNewGlasses.h"
#include "Menu_NewUserRegister.h"
#include "Menu_ViewGlassesList.h"
#include "Menu_ViewUserList.h"

#define MENU_CPUT_PANEL_ID 100

extern Menu_Scan *gMenu_Scan;
extern Menu_FaceScanPreview *gMenu_FaceScanPreview;
extern Menu_FaceMapping *gMenu_FaceMapping;
extern Menu_LandmarkEdit *gMenu_LandmarkEdit;
extern Menu_Function *gMenu_Function;
extern Menu_GlassesPreview *gMenu_GlassesPreview;
extern Menu_AddNewGlasses *gMenu_AddNewGlasses;
extern Menu_NewUserRegister *gMenu_NewUserRegister;
extern Menu_ViewGlassesList *gMenu_ViewGlassesList;
extern Menu_ViewUserList *gMenu_ViewUserList;


void MenuGlob_Init();
void MenuGlob_Shutdown();

class CPUTGuiController;
CPUTGuiController *MenuGlob_GUI();

void MenuGlob_GetScreenDim(int *width, int *height);
void MenuGlob_SetScreenDim(int width, int height);

#endif