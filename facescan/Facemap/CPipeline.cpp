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
#include "CPUT.h"
#include "CPipeline.h"
#include "CDisplacementMapStage.h"
#include "CHeadGeometryStage.h"
#include "CHeadBlendStage.h"
#include "CHairGeometryStage.h"
#include "CPUTModel.h"
#include "CPUTMaterial.h"
#include "CPUTTexture.h"
#include "CPUTMeshDX11.h"
#include "CPUTSoftwareMesh.h"

bool MappingTweaks::operator==(const MappingTweaks &other) const
{
	bool same = true;
#define CMP_EQL(X) {same &= (X == other.X);}
	CMP_EQL(Scale);
	CMP_EQL(DisplaceOffset);
	CMP_EQL(FaceYaw);
	CMP_EQL(FacePitch);
	CMP_EQL(FaceRoll);
	CMP_EQL(BlendColor1);
	CMP_EQL(BlendColor2);
	CMP_EQL(PostBlendAdjust[0]);
	CMP_EQL(PostBlendAdjust[1]);
	CMP_EQL(PostBlendColorize[0]);
	CMP_EQL(PostBlendColorize[1]);
	CMP_EQL(PostBlendMode);
	CMP_EQL(OutputTextureResolution);
	CMP_EQL(MorphTargetEntries);
	CMP_EQL(OtherHeadBlend);
	CMP_EQL(OtherHeadMesh);
	CMP_EQL(OtherHeadTexture);
	CMP_EQL(Flags)
	return same;
}

CPipeline::CPipeline() :
DisplacementMapStage(NULL),
HeadGeometryStage(NULL),
HeadBlendStage(NULL)
{
}

CPipeline::~CPipeline() 
{
	SAFE_DELETE(DisplacementMapStage);
	SAFE_DELETE(HeadGeometryStage);
	SAFE_DELETE(HeadBlendStage);
	for (int i = 0; i < (int)HairStages.size(); i++)
		SAFE_DELETE(HairStages[i]);
	HairStages.clear();
}

void CPipeline::GetOutput(CPipelineOutput *output)
{
	output->DiffuseTexture = HeadBlendStage->Output.OutputDiffuse;
	output->DeformedMesh = &mDeformedMesh;
	
	output->DeformedHairMeshes.clear();
	for (int i = 0; i < (int)HairStages.size(); i++)
	{
		output->DeformedHairMeshes.push_back(&HairStages[i]->DeformedHair);
	}
}

void CPipeline::Execute(SPipelineInput *input, CPipelineOutput *output)
{
	///////////////////////////////////////////////////////////////////////////
	// Displacement Maps
	if (DisplacementMapStage == NULL)
	{
		DisplacementMapStage = new CDisplacementMapStage();
	}
	SDisplacementMapStageInput dmInput = {};
	dmInput.FaceModel = input->FaceModel;
	dmInput.RenderParams = input->RenderParams;
	dmInput.FaceYaw = input->Tweaks->FaceYaw;
	dmInput.FacePitch = input->Tweaks->FacePitch;
	dmInput.FaceRoll = input->Tweaks->FaceRoll;
	DisplacementMapStage->Execute(&dmInput);

	///////////////////////////////////////////////////////////////////////////
	// Head Geometry
	if (HeadGeometryStage == NULL)
	{
		HeadGeometryStage = new CHeadGeometryStage();
	}
	SHeadGeometryStageInput hgInput = {};
	hgInput.DisplacementMap = DisplacementMapStage->Output.DepthMap->GetSoftwareTexture(false, true);
	hgInput.DisplacementMapInfo = &DisplacementMapStage->Output;
	hgInput.BaseHeadInfo = input->BaseHeadInfo;
	hgInput.Tweaks = input->Tweaks;
	hgInput.ClearCachedProjections = false;
	HeadGeometryStage->Execute(&hgInput);
	
	///////////////////////////////////////////////////////////////////////////
	// Head Blend Stage
	if (HeadBlendStage == NULL)
	{
		HeadBlendStage = new CHeadBlendStage();
	}
	SHeadBlendStageInput hbInput = {};
	hbInput.BaseHeadInfo = input->BaseHeadInfo;
	hbInput.DeformedMesh = &HeadGeometryStage->DeformedMesh;
	hbInput.RenderParams = input->RenderParams;
	
	hbInput.BlendColor1 = input->Tweaks->BlendColor1;
	hbInput.BlendColor2 = input->Tweaks->BlendColor2;
	hbInput.PostBlendAdjust[0] = input->Tweaks->PostBlendAdjust[0];
	hbInput.PostBlendAdjust[1] = input->Tweaks->PostBlendAdjust[1];
	hbInput.PostBlendColorize[0] = input->Tweaks->PostBlendColorize[0];
	hbInput.PostBlendColorize[1] = input->Tweaks->PostBlendColorize[1];
	hbInput.PostBlendMode = input->Tweaks->PostBlendMode;
	hbInput.Flags = input->Tweaks->Flags;
	hbInput.Tweaks = input->Tweaks;
	
	hbInput.GeneratedFaceColorMap = DisplacementMapStage->Output.ColorMap->GetColorResourceView();
	HeadBlendStage->Execute(&hbInput);

	mDeformedMesh.CopyFrom(&HeadGeometryStage->DeformedMesh);
	mDeformedMesh.RemoveComponent(eSMComponent_Tex2);

	///////////////////////////////////////////////////////////////////////////
	// Hair Geometry Stage
	for (int i = 0; i < (int)input->HairInfo.size(); i++)
	{
		if (i >= (int)HairStages.size())
		{
			HairStages.push_back(new CHairGeometryStage());
		}

		SHairGeometryStageInput hairGeomInput;
		hairGeomInput.BaseHead = input->BaseHeadInfo->BaseHeadMesh;
		hairGeomInput.DeformedHead = &mDeformedMesh;
		hairGeomInput.Hair = input->HairInfo[i].Mesh;
		hairGeomInput.ClearCachedProjections = false;
		HairStages[i]->Execute(&hairGeomInput);
	}
	int removeStageCount = (int)HairStages.size() - (int)input->HairInfo.size();
	for (int i = 0; i < removeStageCount; i++)
	{
		SAFE_DELETE(HairStages[HairStages.size() - 1]);
		HairStages.pop_back();
	}

	if ( output != NULL)
		GetOutput(output);

}