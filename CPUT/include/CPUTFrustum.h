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
#ifndef _CPUTFRUSTUM_H
#define _CPUTFRUSTUM_H

#include "CPUT.h"
#include "CPUTMath.h"

class CPUTCamera;

class CPUTFrustum
{
public:
    float3 mpPosition[8];
    float3 mpNormal[6];

    UINT mNumFrustumVisibleModels;
    UINT mNumFrustumCulledModels;

    CPUTFrustum(){}
    ~CPUTFrustum(){}

    void InitializeFrustum
    (
        float nearClipDistance,
        float farClipDistance,
        float aspectRatio,
        float fov,
        const float3 &position,
        const float3 &look,
        const float3 &up
    );

    void InitializeFrustum
    (
        float nearClipDistance,
        float farClipDistance,
        float aspectRatio,
        float width,
        float height,
        const float3 &position,
        const float3 &look,
        const float3 &up
    );

    void InitializeFrustum( CPUTCamera *pCamera );

    bool IsVisible(
        const float3 &center,
        const float3 &half
    );

};

#endif // _CPUTFRUSTUM_H
