/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Shader.h] シェーダーのベースクラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：シェーダーのベースクラス
=============================================================================*/
#ifndef SHADER_H_
#define	SHADER_H_

/*--- インクルードファイル ---*/
#include "../../StdAfx.h"
#include "VertexData.h"

/*-------------------------------------
/* 構造体
-------------------------------------*/

/*-------------------------------------
/* シェーダークラス
-------------------------------------*/
class Shader
{
public:
	Shader(class ShaderManager* manager);
	virtual ~Shader(void);

	//後でoverrideできるようにvirtualに

	virtual bool Init(const LPDIRECT3DDEVICE9& lpd3d_device);	//初期化
	virtual void Uninit(void);	//終了化

	//シェーダーのセット
	virtual void ShaderSet(class Camera* camera, class RendererComponent* rendererComponent, class Texture* texture);
	virtual void ShaderSet(class Camera* camera, class RendererComponent* rendererComponent, class Material* material);

	//シェーダーの開始
	virtual void ShaderPassBegin(int shaderPassNumber = 0);

	//シェーダーの終了
	virtual void ShaderPassEnd(void);

private:
protected:
	//シェーダーの所有者
	class ShaderManager* manager_;

	LPDIRECT3DVERTEXDECLARATION9 lpd3d_vertex_declaration_;	//頂点宣言
	LPD3DXEFFECT				 shader_;					//シェーダ情報
};


#endif //RENDERER_H_
/*=============================================================================
/*		End of File
=============================================================================*/