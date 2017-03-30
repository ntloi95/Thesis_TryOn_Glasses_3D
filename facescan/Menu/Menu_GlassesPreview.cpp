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
#include <time.h>
#include "../GameFaceScan.h"

enum MainMenuIds
{
	MainMenuIds_Load = 0,
	MainMenuIds_LandmarkDisplayAll,
	MainMenuIds_Back,
	MainMenuIds_GetInformationLandmark
};

Menu_GlassesPreview::Menu_GlassesPreview()
{
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

void Menu_GlassesPreview::ActivationChanged(bool active)
{
	MenuBase::ActivationChanged(active);
	if (active)
	{
		CPUTGuiController *pGUI = MenuGlob_GUI();

		pGUI->CreateCheckbox("Landmarks", MainMenuIds_LandmarkDisplayAll, MENU_CPUT_PANEL_ID, &mLandmarkCheckbox);
		pGUI->CreateButton("Get Landmarks", MainMenuIds_GetInformationLandmark, MENU_CPUT_PANEL_ID);
		pGUI->CreateButton("Load Object", MainMenuIds_Load, MENU_CPUT_PANEL_ID);
		pGUI->CreateButton("Back", MainMenuIds_Back, MENU_CPUT_PANEL_ID);
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
		case MainMenuIds_Load:
		{
			//Open a dialog 
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
	//int i = 0;
	//for (auto it = mFaceModel.Landmarks.begin(); it != mFaceModel.Landmarks.end(); it++, i++)
	//{
	//	float3 position = *it;
	//	printf("%d : %f %f %f \n", i, position.x, position.y, position.z);
	//}
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
	renderParams.mpCamera = (CPUTCamera*)cameraController->GetCamera();
	if (displayModel != NULL)
	{
		displayModel->Render(renderParams, 0);

		if (mLandmarkCheckbox->GetCheckboxState() == CPUT_CHECKBOX_CHECKED)
		{
			// Draw landmarks in glasses
			/*for (auto it = mFaceModel.Landmarks.begin(); it != mFaceModel.Landmarks.end(); it++)
			{
				CPUTColor4 color = CPUTColor4(0.0f, 1.0f, 0.0f, 1.0f);
				DrawCube(renderParams, *it, 0.1f, color);
			}*/
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

	//CPUTAssetLibrary *pAssetLibrary = CPUTAssetLibrary::GetAssetLibrary();
	//pAssetLibrary->SetRootRelativeMediaDirectory("MyAssets");
	//std::string matName = pAssetLibrary->GetMaterialDirectoryName();
	//CPUTFileSystem::CombinePath(matName, "meshpreview.mtl", &matName);

	//CPUTMaterial *material = CPUTMaterial::Create(matName);
	//material->OverridePSTexture(0, NULL);
	//displayModel->SetMaterial(0, &material, 1);
}