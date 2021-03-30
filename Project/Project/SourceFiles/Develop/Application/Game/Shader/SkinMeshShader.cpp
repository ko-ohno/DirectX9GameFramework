#include "../../../StdAfx.h"
#include "SkinMeshShader.h"



SkinMeshShader::SkinMeshShader(ShaderManager* manager)
	: Shader(manager)
	, d3dxhandle_technique_(nullptr)
	, d3dxhandle_texture_(nullptr)
{
}

SkinMeshShader::~SkinMeshShader(void)
{
}

bool SkinMeshShader::Init(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	return false;
}

void SkinMeshShader::Uninit(void)
{
}

bool SkinMeshShader::ShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	return false;
}

bool SkinMeshShader::NewShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	return false;
}

bool SkinMeshShader::LoadCompiledShader(const LPDIRECT3DDEVICE9& lpd3d_device)
{
	return false;
}

void SkinMeshShader::ShaderSet(Camera* camera, RendererComponent* rendererComponent, Texture* texture)
{
}
