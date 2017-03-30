#include "CGlassesModel.h"
#include "CPUTModel.h"
#include "CPUTMesh.h"
#include "CPUTMaterial.h"
#include "SampleUtil.h"
#include "CPUTTexture.h"

static uint32 gKeyUniqueId = 0;

CGlassesModel::CGlassesModel() : mObjFilename("")
{
	FlagUpdated();
}

CGlassesModel::~CGlassesModel()
{
	//SAFE_RELEASE(mTexture);
}

uint32 CGlassesModel::GetUniqueId() { return mUniqueId; }
void CGlassesModel::FlagUpdated() { mUniqueId = gKeyUniqueId++; }

void CGlassesModel::LoadObjFilename(const std::string &filename)
{
	AABBMin = float3(10000.0f, 10000.0f, 10000.0f);
	AABBMax = -AABBMin;

	mObjFilename = filename;
	tObjModel objModel;
	objLoader(filename.c_str(), objModel);
	CopyOBJDataToSoftwareMesh(&objModel, &mMesh);

	float boxSize = 8.0f;
	int vertCount = mMesh.GetVertCount();
	if (vertCount > 0)
	{
		float3 vmin = mMesh.Pos[0];
		float3 vmax = mMesh.Pos[0];

		for (int i = 1; i < vertCount; i++)
		{
			vmin = Min(vmin, mMesh.Pos[i]);
			vmax = Max(vmax, mMesh.Pos[i]);
		}

		float3 center = (vmax - vmin) / 2.0f;
		float3 dim = vmax - vmin;

		float maxDim = floatMax(dim.x, floatMax(dim.y, dim.z));

		mVertOffset = -center;
		mVertScale = boxSize / maxDim;

		for (int i = 0; i < vertCount; i++)
		{
			float3 *pos = &mMesh.Pos[i];
			*pos -= center;
			*pos *= mVertScale;
			Swap(pos->z, pos->y);

			mMesh.Tex[i].y = 1.0f - mMesh.Tex[i].y;

			AABBMin = Min(*pos, AABBMin);
			AABBMax = Max(*pos, AABBMax);
		}
	}

	FindLandmarks();

	FlagUpdated();
}

// Process Landmarks here
void CGlassesModel::FindLandmarks()
{

}

CPUTModel* CGlassesModel::CreateCPUTModel()
{
	ProfileBlockScoped block("LoadCUPUTModel");

	CPUTModel *model = CPUTModel::Create();
	CPUTMesh *mesh = CPUTMesh::Create();
	mMesh.CopyFromDX11Mesh((CPUTMeshDX11*)mesh);

	// 
	model->mpMaterialCount = new int[1];
	model->mpMaterial = new CPUTMaterial**[1];
	model->mpMaterial[0] = new CPUTMaterial*[2];
	model->mpMaterial[0][0] = NULL;
	model->mpMaterial[1][0] = NULL;
	model->mpMaterialCount[0] = 2; // ????
	
	model->SetMeshes(&mesh, 1);

	return model;
}
