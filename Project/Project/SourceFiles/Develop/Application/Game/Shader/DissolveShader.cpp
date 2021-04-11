#include "../../../StdAfx.h"
#include "DissolveShader.h"

DissolveFadeShader::DissolveFadeShader(ShaderManager* manager)
    : Shader(manager)
    , d3dxhandle_technique_(nullptr)
    , d3dxhandle_texture_(nullptr)
{
}

DissolveFadeShader::~DissolveFadeShader(void)
{
}

bool DissolveFadeShader::Init(const LPDIRECT3DDEVICE9& lpd3d_device)
{
    UNREFERENCED_PARAMETER(lpd3d_device);
    return false;
}

bool DissolveFadeShader::ShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device)
{
    UNREFERENCED_PARAMETER(lpd3d_device);
    return false;
}

bool DissolveFadeShader::NewShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device)
{
    UNREFERENCED_PARAMETER(lpd3d_device);
    return false;
}

bool DissolveFadeShader::LoadCompiledShader(const LPDIRECT3DDEVICE9& lpd3d_device)
{
    UNREFERENCED_PARAMETER(lpd3d_device);
    return false;
}

void DissolveFadeShader::ShaderSet(Camera* camera, RendererComponent* rendererComponent, Texture* texture)
{
    UNREFERENCED_PARAMETER(camera);
    UNREFERENCED_PARAMETER(rendererComponent);
    UNREFERENCED_PARAMETER(texture);
}
