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
#ifndef __CPUTGUICONTROLLEROGL_H__
#define __CPUTGUICONTROLLEROGL_H__

#include "CPUTGuiController.h"

class CPUTMaterial;
class CPUTBufferOGL;
class CPUTMeshOGL;


// the GUI controller class that dispatches the rendering calls to all the buttons
//--------------------------------------------------------------------------------
class CPUTGuiControllerOGL:public CPUTGuiController
{   
public:
    static CPUTGuiControllerOGL *GetController();
    static CPUTResult DeleteController();

    // initialization
    CPUTResult Initialize(const std::string& materialName, const std::string& fontName);
    
    // draw routines    
    void  Draw();
    void  UpdateConstantBuffer();

private:
    static CPUTGuiControllerOGL *mguiController; // singleton object

    CPUTMaterial *mpMaterial;

    CPUTBuffer *mpConstantBufferVS;
    CPUTMeshOGL *mpUberBuffer;
    
    CPUTResult UpdateUberBuffers();

    CPUTGuiControllerOGL();    // singleton
    ~CPUTGuiControllerOGL();
};

#endif // #ifndef __CPUTGUICONTROLLEROGL_H__
