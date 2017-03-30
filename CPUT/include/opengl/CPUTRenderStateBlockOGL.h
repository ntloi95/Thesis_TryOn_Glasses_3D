//--------------------------------------------------------------------------------------
// Copyright 2011 Intel Corporation
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
#ifndef _CPUTRENDERSTATEBLOCKOGL_H
#define _CPUTRENDERSTATEBLOCKOGL_H

#include "CPUTRenderStateBlock.h"
#include "CPUTConfigBlock.h"
#include <string.h>

struct CPUTRenderStateMapEntry;
class CPUTRenderParameters;

struct CPUT_DEPTH_STENCIL_DESC {
    bool        DepthEnable;
    GLboolean   DepthWriteMask;
    GLenum      DepthFunc;
    bool        StencilEnable;
    GLuint      StencilWriteMask;
    GLenum      FrontFaceStencilFailOp;
    GLenum      FrontFaceStencilDepthFailOp;
    GLenum      FrontFaceStencilPassOp;
    GLenum      FrontFaceStencilFunc;
    GLint       FrontFaceStencilFuncRef;
    GLuint      FrontFaceStencilFuncMask;
    GLenum      BackFaceStencilFailOp;
    GLenum      BackFaceStencilDepthFailOp;
    GLenum      BackFaceStencilPassOp;
    GLenum      BackFaceStencilFunc;
    GLint       BackFaceStencilFuncRef;
    GLuint      BackFaceStencilFuncMask;
};

struct CPUT_RASTERIZER_DESC {
    GLenum      FillMode;
    GLenum      CullMode;
    GLenum      FrontCounterClockwise;
    bool        CullingEnabled;
    bool        DepthClipEnable;
    bool        ScissorEnable;
    bool        MultisampleEnable;
    bool        AntialiasedLineEnable;
};

struct CPUT_BLEND_DESC {
    GLenum      BlendEnable;
	GLenum		SrcBlend;
	GLenum		DestBlend;
	GLenum		SrcBlendAlpha;
	GLenum		DestBlendAlpha;
	GLenum		BlendOp;
	GLenum		BlendOpAlpha;
};

struct CPUT_SAMPLER_DESC {
//    std::string     TextureName;
    GLint       MinFilter;
    GLint       MagFilter;
    GLint       AddressU;
    GLint       AddressV;
    GLint       AddressW;
    GLfloat     MipLODBias;
//    GLint MaxAnisotropy; there doesn't seem to be an opengl equivalent
    GLint       ComparisonMode;
    GLint       ComparisonFunc;
    GLfloat     BorderColor[4];
    GLfloat     MinLOD;
    GLfloat     MaxLOD;
};


//-----------------------------------------------------------------------------
// TODO: Move to own file

// magic number 16! TODO: change to a stl::vector or something and query OGL for max number
#define NUM_SAMPLERS_PER_RENDERSTATE 16 
class CPUTRenderStateOGL
{
public:
    CPUT_DEPTH_STENCIL_DESC  DepthStencilDesc;
    CPUT_RASTERIZER_DESC     RasterizerDesc;
	CPUT_BLEND_DESC			 RenderTargetBlendDesc;
    GLuint                   SamplerIDs[NUM_SAMPLERS_PER_RENDERSTATE];
    CPUT_SAMPLER_DESC        SamplerDesc[NUM_SAMPLERS_PER_RENDERSTATE];

    GLuint                   DefaultSamplerID;
    CPUT_SAMPLER_DESC        DefaultSamplerDesc;
    float                    BlendFactor[4];
    UINT                     SampleMask;

    CPUTRenderStateOGL() { SetDefaults(); }
    ~CPUTRenderStateOGL() {} // Destructor is not public.  Must release instead of delete.
    void SetDefaults();
};

//-----------------------------------------------------------------------------
class CPUTRenderStateBlockOGL:public CPUTRenderStateBlock
{
protected:
    // The state descriptor describes all of the states.
    // We read it in when creating assets.  We keep it around in case we need to adjust and recreate.
    CPUTRenderStateOGL        mStateDesc;

    UINT                        mNumSamplers;

    CPUTRenderStateBlockOGL() {}

     // Destructor is not public.  Must release instead of delete.
    ~CPUTRenderStateBlockOGL()
    {
    }

public:
	static CPUTRenderStateBlockOGL* Create();

    // constructor
    CPUTResult ReadProperties(
        CPUTConfigFile                &file,
        const std::string                 &blockName,
        const CPUTRenderStateMapEntry *pMap,
        void                          *pDest
    );
    void               ReadValue( CPUTConfigEntry *pValue, const CPUTRenderStateMapEntry *pRenderStateList, void *pDest );
    virtual CPUTResult LoadRenderStateBlock(const std::string &fileName);
    virtual void       CreateNativeResources();
    void               SetRenderStates();
    CPUTRenderStateOGL *GetState() {return &mStateDesc;}
	UINT				GetNumSamplers() { return mNumSamplers;}
};

//-----------------------------------------------------------------------------
enum CPUT_PARAM_TYPE{
    ePARAM_TYPE_TYPELESS,
    ePARAM_TYPE_INT,
    ePARAM_TYPE_UINT,
    ePARAM_TYPE_FLOAT,
    ePARAM_TYPE_BOOL,
    ePARAM_TYPE_SHORT,
    ePARAM_TYPE_CHAR,
    ePARAM_TYPE_UCHAR,
    ePARAM_TYPE_STRING, // Does string make sense?  Could copy it.
    ePARAM_TYPE_GL_BLEND,
    ePARAM_TYPE_GL_BLEND_OP,
    ePARAM_TYPE_DEPTH_WRITE_MASK,
    ePARAM_TYPE_OGL_COMPARISON_MODE,
    ePARAM_TYPE_OGL_COMPARISON_FUNC,
    ePARAM_TYPE_OGL_STENCIL_OP,
    ePARAM_TYPE_OGL_FILL_MODE,
    ePARAM_TYPE_OGL_CULL_MODE,
    ePARAM_TYPE_OGL_CULL_ENABLE,
    ePARAM_TYPE_OGL_FILTER,
    ePARAM_TYPE_OGL_TEXTURE_ADDRESS_MODE,
    ePARAM_TYPE_OGL_ENUM,
    ePARAM_TYPE_OGL_BOOL,
    ePARAM_TYPE_OGL_INT,
    ePARAM_TYPE_OGL_UINT,
    ePARAM_TYPE_OGL_HEX32,
};

//-----------------------------------------------------------------------------
struct CPUTRenderStateMapEntry
{
    std::string     name;
    CPUT_PARAM_TYPE type;
    UINT            offset;
};

#endif // _CPUTRENDERSTATEBLOCKOGL_H
