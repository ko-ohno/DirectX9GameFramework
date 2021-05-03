/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GizmoShader.h] スプライトシェーダクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：スプライトシェーダクラス
=============================================================================*/
#ifndef GIZMO_SHADER_H_
#define	GIZMO_SHADER_H_

/*--- インクルードファイル ---*/
#include "../Shader.h"

/*-------------------------------------
/* スプライトシェーダクラス
-------------------------------------*/
class GizmoShader : public Shader
{
public:
	GizmoShader(class ShaderManager* manager);
	~GizmoShader(void);

	//初期化
	bool Init(const LPDIRECT3DDEVICE9& lpd3d_device) override;

	//シェーダのコンパイル
	bool ShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device);

private:
	bool NewShaderCompile(const LPDIRECT3DDEVICE9& lpd3d_device);
	bool LoadCompiledShader(const LPDIRECT3DDEVICE9& lpd3d_device);

public:
	void ShaderSet(class Camera* camera, class RendererComponent* rendererComponent, class Material* material) override;

private:
	D3DXHANDLE d3dxhandle_technique_;	//テクニックへのハンドル
};

#endif //GIZMO_SHADER_H_
/*=============================================================================
/*		End of File
=============================================================================*/