
#ifndef __OBJ_MODEL__
#define __OBJ_MODEL__

#include "CPUT.h"
#include "ObjLoader.h"
#include <map>
#include "CPUTMath.h"
#include "CPUTSoftwareMesh.h"

class CPUTModel;
class CPUTTexture;

class CFaceModel
{
public:

	CFaceModel();
	~CFaceModel();

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

	// values that were applied to the objmodel after it was loaded
	// in an effort to normalize the mesh
	float mVertScale;
	float3 mVertOffset;

	uint32 mUniqueId;

	CPUTSoftwareMesh mMesh;
	CPUTTexture *mTexture;
	
	bool LoadLandmarks( const std::string &filename, std::vector<float3> &outMap, int formatVersion = 0 );
	
};
#endif // __OBJ_MODEL__