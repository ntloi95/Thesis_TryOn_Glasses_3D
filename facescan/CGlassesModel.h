#ifndef __OBJ_GLASSES_MODEL__
#define __OBJ_GLASSES_MODEL__

#include "CPUT.h"
#include "ObjLoader.h"
#include <map>
#include "CPUTMath.h"
#include "CPUTSoftwareMesh.h"

class CPUTModel;
class CPUTTexture;

class CGlassesModel
{
public:

	CGlassesModel();
	~CGlassesModel();

	void LoadObjFilename(const std::string &filename, bool landmarks = true);
	CPUTModel *CreateCPUTModel();

	bool LoadLandmarks();

	std::vector<float3> Landmarks;

	float3 AABBMin;
	float3 AABBMax;

	// Unique ID that changes if any part of this model changes
	uint32 GetUniqueId();

	// Updates the unique ID if any data in this mesh changes
	void FlagUpdated();

	CPUTTexture *GetTexture() { return mTexture; }

	CPUTSoftwareMesh *GetMesh() { return &mMesh; }

private:
	std::string mObjFilename;

	float mVertScale;
	float3 mVertOffset;

	uint32 mUniqueId;

	CPUTSoftwareMesh mMesh;
	CPUTTexture *mTexture;

};

#endif