[SamplerOGL_1]


MinFilter = GL_LINEAR_MIPMAP_LINEAR
MagFilter = GL_LINEAR
AddressU = GL_REPEAT
AddressV = GL_REPEAT
AddressW = GL_CLAMP_TO_EDGE

ComparisonMode = GL_COMPARE_REF_TO_TEXTURE
ComparisonFunc = GL_LESS


[SamplerOGL_2]

MinFilter = GL_LINEAR_MIPMAP_LINEAR
MagFilter = GL_LINEAR
AddressU = GL_REPEAT
AddressV = GL_REPEAT
AddressW = GL_CLAMP_TO_EDGE
ComparisonMode = GL_COMPARE_REF_TO_TEXTURE
ComparisonFunc = GL_LESS

[SamplerDX11_1]
[SamplerDX11_2]
ComparisonFunc = D3D11_COMPARISON_GREATER_EQUAL
Filter = D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT
AddressU       = D3D11_TEXTURE_ADDRESS_CLAMP
AddressV       = D3D11_TEXTURE_ADDRESS_CLAMP
