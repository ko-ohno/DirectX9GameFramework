#pragma once

#include "../Shader.h"


class DissolveFadeShader : public Shader
{
public:
	DissolveFadeShader(class ShaderManager* manager);
	~DissolveFadeShader(void);

	static DissolveFadeShader* Create(class ShaderManager* manager);

	bool Init(const LPDIRECT3DDEVICE9& lpd3d_device) override;

	//シェーダのコンパイル
	bool ShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device);

private:
	bool NewShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device);
	bool LoadCompiledShader(const LPDIRECT3DDEVICE9& lpd3d_device);

public:
	void ShaderSet(class Camera* camera, class RendererComponent* rendererComponent, class Texture* texture) override;

private:
	D3DXHANDLE d3dxhandle_technique_;	//テクニックへのハンドル
	D3DXHANDLE d3dxhandle_texture_;		//テクスチャーへのハンドル

};

