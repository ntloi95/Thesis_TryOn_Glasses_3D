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
#include "MenuGlob.h"
#include "CPUTGuiControllerDX11.h"
#include "Menu_FaceScanPreview.h"


Menu_Scan *gMenu_Scan;
Menu_FaceScanPreview *gMenu_FaceScanPreview;
Menu_FaceMapping *gMenu_FaceMapping;
Menu_LandmarkEdit *gMenu_LandmarkEdit;
Menu_Function *gMenu_Function;
Menu_GlassesPreview *gMenu_GlassesPreview;
Menu_AddNewGlasses *gMenu_AddNewGlasses;
Menu_NewUserRegister *gMenu_NewUserRegister;
Menu_ViewGlassesList *gMenu_ViewGlassesList;
Menu_ViewUserList *gMenu_ViewUserList;

static int gScreenWidth = 0;
static int gScreenHeight = 0;

void MenuGlob_Init()
{
	gMenu_Scan = new Menu_Scan();
	gMenu_FaceScanPreview = new Menu_FaceScanPreview();
	gMenu_FaceMapping = new Menu_FaceMapping();
	gMenu_LandmarkEdit = new Menu_LandmarkEdit();
	gMenu_Function = new Menu_Function();
	gMenu_GlassesPreview = new Menu_GlassesPreview();
	gMenu_AddNewGlasses = new Menu_AddNewGlasses();
	gMenu_NewUserRegister = new Menu_NewUserRegister();
	gMenu_ViewGlassesList = new Menu_ViewGlassesList();
	gMenu_ViewUserList = new Menu_ViewUserList();

	//gMenu_Scan->Init();
	//gMenu_FaceScanPreview->Init();
	//gMenu_FaceMapping->Init();
	//gMenu_LandmarkEdit->Init();
	//gMenu_Function->Init();
	//gMenu_GlassesPreview->Init();
	//gMenu_AddNewGlasses->Init();
	gMenu_NewUserRegister->Init();
	//gMenu_ViewGlassesList->Init();
	//gMenu_ViewUserList->Init();
}

void MenuGlob_Shutdown()
{
	gMenu_Scan->Shutdown();
	gMenu_FaceScanPreview->Shutdown();
	gMenu_FaceMapping->Shutdown();
	gMenu_LandmarkEdit->Shutdown();

	SAFE_DELETE(gMenu_Scan);
	SAFE_DELETE(gMenu_FaceScanPreview);
	SAFE_DELETE(gMenu_FaceMapping);
	SAFE_DELETE(gMenu_LandmarkEdit);
}

CPUTGuiController *MenuGlob_GUI()
{
	return (CPUTGuiController*)CPUTGuiControllerDX11::GetController();
}

void MenuGlob_GetScreenDim(int *width, int *height)
{
	*width = gScreenWidth;
	*height = gScreenHeight;
}

void MenuGlob_SetScreenDim(int width, int height)
{
	gScreenWidth = width;
	gScreenHeight = height;
}