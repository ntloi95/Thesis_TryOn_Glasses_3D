//--------------------------------------------------------------------------------------
// Copyright 2013 Intel Corporation
#include "CGlassesModel.h"
#include "CPUTModel.h"
#include "CPUTMesh.h"
#include "CPUTMaterial.h"
#include "SampleUtil.h"
#include "CPUTTexture.h"

static uint32 gGlassesScanUniqueId = 0;
CGlassesModel::CGlassesModel() :
mObjFilename(""),
mTexture(NULL)
{
	FlagUpdated();
}

CGlassesModel::~CGlassesModel()
{
	SAFE_RELEASE(mTexture);
}

uint32 CGlassesModel::GetUniqueId() { return mUniqueId; }
void CGlassesModel::FlagUpdated() { mUniqueId = gGlassesScanUniqueId++; }

void CGlassesModel::LoadObjFilename(const std::string &filename, bool landmarks)
{
	AABBMin = float3(10000.0f, 10000.0f, 10000.0f);
	AABBMax = -AABBMin;

	mObjFilename = filename;
	{
		tObjModel objModel;
		objLoader(filename.c_str(), objModel);
		CopyOBJDataToSoftwareMesh(&objModel, &mMesh);
	}

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

		float3 center = (vmax + vmin) / 2.0f;
		float3 dim = vmax - vmin;

		float maxDim = floatMax(dim.x, floatMax(dim.y, dim.z));

		mVertOffset = -center;
		mVertScale = boxSize / maxDim / 1.5f;

		// center to origin, scale, and rotate
		// 
		for (int i = 0; i < vertCount; i++)
		{
			float3 *pos = &mMesh.Pos[i];
			*pos -= center;
			*pos *= mVertScale;
			Swap(pos->z, pos->y);

			// save scale and rotate from RSSDK format. Z is up in rssdk
			mMesh.Tex[i].y = 1.0f - mMesh.Tex[i].y;

			AABBMin = Min(*pos, AABBMin);
			AABBMax = Max(*pos, AABBMax);
		}
	}
	LoadLandmarks();

	// load texture
	SAFE_RELEASE(mTexture);
	std::string fnString = mObjFilename;
	int lastindex = (int)fnString.find_last_of(".");
	std::string rawname = fnString.substr(0, lastindex);
	std::string textureName = rawname.append("image1.png");
	mTexture = CPUTTexture::Create(std::string("facetexture"), textureName, false);

	FlagUpdated();
}

CPUTModel *CGlassesModel::CreateCPUTModel()
{
	ProfileBlockScoped block("LoadCPUTModel");

	CPUTModel *model = CPUTModel::Create();
	CPUTMesh *mesh = CPUTMesh::Create();
	mMesh.CopyToDX11Mesh((CPUTMeshDX11*)mesh);

	model->mpMaterialCount = new int[1];
	model->mpMaterial = new CPUTMaterial**[1];
	model->mpMaterial[0] = new CPUTMaterial*[1];
	model->mpMaterial[0][0] = NULL;
	model->mpMaterialCount[0] = 1;

	model->SetMeshes(&mesh, 1);

	return model;
}

bool CGlassesModel::LoadLandmarks()
{
	return 0;
	//CPUTModel *displayModel = CreateCPUTModel();
	//auto item = displayModel->GetMesh(0);
	//D3D11_MAPPED_SUBRESOURCE verts = item->MapVertices(renderParams, CPUT_MAP_READ);
	//int vertex_count = static_cast<CPUTMeshDX11*>(item)->GetVertexCount();
	//RemapVertex v;
	//std::vector<float3> vertexs;
	//std::vector<float3> landmarks;
	//float3 KT1(0, 0, 0);
	//float3 KT2(0, 0, 0);
	//float3 KM1(0, 0, 0);
	//float3 KM2(0, 0, 0);
	//float3 KTD1(0, 0, 0);
	//float3 KTD2(0, 0, 0);

	//for (int i = 0; i < vertex_count; i++) {
	//	if (false == CopyVerticesFromMesh(&v, NULL, NULL, i, -1, -1, verts.pData, item))
	//		break;

	//	float3 ver = v.position;
	//	ver.x = -ver.x;
	//	vertexs.push_back(ver);

	//	if (ver.x < 0)
	//	{
	//		if (KT1.y > ver.y)
	//			KT1 = ver;
	//		if (KM1.y < ver.y)
	//			KM1 = ver;
	//		if (KTD1.x > ver.x)
	//			KTD1 = ver;
	//	}
	//	if (ver.x > 0)
	//	{
	//		if (KT2.y > ver.y)
	//			KT2 = ver;
	//		if (KM2.y < ver.y)
	//			KM2 = ver;
	//		if (KTD2.x < ver.x)
	//			KTD2 = ver;
	//	}
	//}

	//landmarks.push_back(KT1);
	//landmarks.push_back(KT2);
	//landmarks.push_back(KM1);
	//landmarks.push_back(KM2);
	//landmarks.push_back(KTD1);
	//landmarks.push_back(KTD2);
	//for (int i = 0; i < landmarks.size(); i++)
	//	DrawCube(renderParams, landmarks[i], 0.1f, CPUTColor4(0, 1, 0, 1));
	////DrawCube(renderParams, KT2, 0.1f, CPUTColor4(0, 1, 1, 1));
}