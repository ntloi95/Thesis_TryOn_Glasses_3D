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
#include "Menu_GlassesPreview.h"
#include "MenuController.h"
#include "CPUTGuiControllerDX11.h"
#include "MenuGlob.h"
#include "CPUTModel.h"
#include "CPUTMesh.h"
#include "CPUTTextureDX11.h"
#include "CPUTMaterial.h"
#include "../ObjLoader.h"
#include "../CFaceModel.h"
#include "../OBJExporter.h"
#include <time.h>
#include "../GameFaceScan.h"

enum MainMenuIds
{
	MainMenuIds_Accept = 0,
	MainMenuIds_Retry,
	MainMenuIds_LandmarkDisplayAll,
	MainMenuIds_Back,
	MainMenuIds_GetInformationLandmark
};

Menu_GlassesPreview::Menu_GlassesPreview()
{
	mMode = GlassesPreviewMode_ApproveScan;
	displayModel = NULL;
	cameraController = new CPUTCameraModelViewer();
	cameraController->SetTarget(float3(0, 0, 0));
	cameraController->SetDistance(10, 3, 20);
	cameraController->SetViewAngles(0, 0);
}

Menu_GlassesPreview::~Menu_GlassesPreview()
{
	SAFE_DELETE(cameraController);
}

void Menu_GlassesPreview::Init()
{
	MenuBase::Init();
}

void Menu_GlassesPreview::SetGlassesMode(GlassesPreviewMode mode)
{
	mMode = mode;
}

void Menu_GlassesPreview::ActivationChanged(bool active)
{
	MenuBase::ActivationChanged(active);
	if (active)
	{
		CPUTGuiController *pGUI = MenuGlob_GUI();

		if (mMode == GlassesPreviewMode_ApproveScan)
		{
			pGUI->CreateButton("Accept Scan", MainMenuIds_Accept, MENU_CPUT_PANEL_ID);
			pGUI->CreateButton("Retry Scan", MainMenuIds_Retry, MENU_CPUT_PANEL_ID);
		}
		pGUI->CreateButton("Back", MainMenuIds_Back, MENU_CPUT_PANEL_ID);
		pGUI->CreateCheckbox("Landmarks", MainMenuIds_LandmarkDisplayAll, MENU_CPUT_PANEL_ID, &mLandmarkCheckbox);
		pGUI->CreateButton("Get Landmarks", MainMenuIds_GetInformationLandmark, MENU_CPUT_PANEL_ID);
	}
	else
	{
		mLandmarkCheckbox = NULL;
	}
}

// Handle event Sn review
void Menu_GlassesPreview::HandleCPUTEvent(int eventID, int controlID, CPUTControl *control)
{
	if (eventID == CPUT_EVENT_DOWN)
	{
		switch (controlID)
		{
		case MainMenuIds_Accept:
		{
			/*char buffer[256];
			time_t rawtime;
			struct tm * timeinfo;
			time(&rawtime);
			timeinfo = localtime(&rawtime);
			strftime(buffer, sizeof(buffer), "%b_%d_%Y_%H_%M_%S", timeinfo);
			std::string modelName = std::string("model_") + buffer + ".obj";

			OPENFILENAMEA ofn = { 0 };
			char ofnFilename[MAX_PATH];
			strncpy(ofnFilename, modelName.c_str(), MAX_PATH);

			ofn.lStructSize = sizeof(ofn);
			ofn.lpstrTitle = "Save Scanned Face";
			ofn.hwndOwner = NULL;
			ofn.lpstrFilter = "Obj Files (*.obj)\0*.obj\0";
			ofn.lpstrFile = ofnFilename;
			ofn.nMaxFile = sizeof(ofnFilename);
			ofn.Flags = OFN_EXPLORER;
			ofn.lpstrDefExt = "obj";

			gMenu_FaceMapping->LoadFace(ofnFilename);
			MenuController_PushMenu(gMenu_FaceMapping, true);*/
		} break;
		case MainMenuIds_Back:
		{
			MenuController_PopMenu(true);
		} break;
		case MainMenuIds_GetInformationLandmark:
		{
			PrintLandmark();
		} break;

		}
	}
}

void Menu_GlassesPreview::PrintLandmark()
{
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	int i = 0;
	for (auto it = mGlassesModel.Landmarks.begin(); it != mGlassesModel.Landmarks.end(); it++, i++)
	{
		float3 position = *it;
		printf("%d : %f %f %f \n", i, position.x, position.y, position.z);
	}
}

CPUTEventHandledCode Menu_GlassesPreview::HandleMouseEvent(int x, int y, int wheel, CPUTMouseState state, CPUTEventID message)
{
	return cameraController->HandleMouseEvent(x, y, wheel, state, message);
}

void Menu_GlassesPreview::Update(float dt)
{
	cameraController->Update(dt);
}

// Raw landmark
void Menu_GlassesPreview::Render(CPUTRenderParameters &renderParams)
{
	static bool gotLandmark = false;
	renderParams.mpCamera = (CPUTCamera*)cameraController->GetCamera();
	if (displayModel != NULL)
	{
		if (!gotLandmark)
		{
			gotLandmark = 1;
			auto item = displayModel->GetMesh(0);
			D3D11_MAPPED_SUBRESOURCE verts = item->MapVertices(renderParams, CPUT_MAP_READ);
			int vertex_count = static_cast<CPUTMeshDX11*>(item)->GetVertexCount();
			RemapVertex v;
			std::vector<float3> vertexs;
			float3 KT1(0, 0, 0);
			float3 KT2(0, 0, 0);
			float3 KM1_T(0, 0, 0);
			float3 KM2_T(0, 0, 0);
			float3 KTD1(0, 0, 0);
			float3 KTD2(0, 0, 0);
			float3 KM1(0, (float)INT_MAX, 0);
			float3 KM2(0, (float)INT_MAX, 0);

			for (int i = 0; i < vertex_count; i++) {
				if (false == CopyVerticesFromMesh(&v, NULL, NULL, i, -1, -1, verts.pData, item))
					break;

				float3 ver = v.position;
				ver.x = -ver.x;
				vertexs.push_back(ver);

				if (ver.x < 0)
				{
					if (KT1.y > ver.y)
						KT1 = ver;
					if (KM1_T.y < ver.y)
						KM1_T = ver;
					if (KTD1.x > ver.x)
						KTD1 = ver;
				}
				if (ver.x > 0)
				{
					if (KT2.y > ver.y)
						KT2 = ver;
					if (KM2_T.y < ver.y)
						KM2_T = ver;
					if (KTD2.x < ver.x)
						KTD2 = ver;
				}
			}

			mGlassesModel.Landmarks.push_back(KT1);
			mGlassesModel.Landmarks.push_back(KT2);
			mGlassesModel.Landmarks.push_back(KTD1);
			mGlassesModel.Landmarks.push_back(KTD2);

			for (int i = 0; i < vertex_count; i++)
			{
				float3 ver = vertexs[i];

				if (ver.x < 0 && ver.x >= KM1_T.x && ver.y < KM1.y)
					KM1 = ver;

				if (ver.x > 0 && ver.x <= KM2_T.x && ver.y < KM2.y)
					KM2 = ver;
			}

			mGlassesModel.Landmarks.push_back(KM1);
			mGlassesModel.Landmarks.push_back(KM2);

		}

		displayModel->Render(renderParams, 0);

		if (mLandmarkCheckbox->GetCheckboxState() == CPUT_CHECKBOX_CHECKED)
		{
			for (int i = 0; i < mGlassesModel.Landmarks.size(); i++)
				DrawCube(renderParams, mGlassesModel.Landmarks[i], 0.1f, CPUTColor4(0, 1, 0, 1));
		}
	}


}

void Menu_GlassesPreview::LoadGlassesObj(std::string filename, bool absoluteFilename, bool forceReload)
{
	ProfileBlockScoped block("Load OBJ");
	if (!absoluteFilename)
	{
		CPUTFileSystem::CombinePath(GetUserDataDirectory(), filename, &filename);
	}

	if (filename == mModelFilename && !forceReload)
		return;

	mGlassesModel.LoadObjFilename(filename);
	mModelFilename = filename;

	SAFE_RELEASE(displayModel);
	displayModel = mGlassesModel.CreateCPUTModel();

	CPUTAssetLibrary *pAssetLibrary = CPUTAssetLibrary::GetAssetLibrary();
	pAssetLibrary->SetRootRelativeMediaDirectory("MyAssets");
	std::string matName = pAssetLibrary->GetMaterialDirectoryName();
	CPUTFileSystem::CombinePath(matName, "meshpreview.mtl", &matName);

	CPUTMaterial *material = CPUTMaterial::Create(matName);
	material->OverridePSTexture(0, mGlassesModel.GetTexture());
	displayModel->SetMaterial(0, &material, 1);
}