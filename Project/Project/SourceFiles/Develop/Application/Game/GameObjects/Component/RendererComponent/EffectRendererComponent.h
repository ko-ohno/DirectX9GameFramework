/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EffectRendererComponent.h]  エフェクト描画コンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：エフェクト描画コンポーネント
=============================================================================*/
#ifndef EFFECT_RENDERER_COMPONENT_H_
#define	EFFECT_RENDERER_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../RendererComponent.h"

/*-------------------------------------
/* エフェクトコンポーネントクラス
-------------------------------------*/
class EffectRendererComponent : public RendererComponent
{
public:
	EffectRendererComponent(class GameObject* owner, int drawOrder = 100);
	~EffectRendererComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Update(float deltaTime) override;
	void Draw(class Shader* shader, class Camera* camera) override;

	void SetBaseMatrix(const D3DXMATRIX& d3dxMatrix);

	// エフェクトの設定
	void SetEffect(EffectType effectTypeID);

	// エフェクト情報の取得
	class GameEffect* GetEffect(void);

	virtual TypeID GetComponentType() const override { return TypeID::EffectRendererComponent; };

	//
	// エフェクトの再生
	//

	void Play(void);
	void Play(const D3DXVECTOR3& position);
	void Play(float posX, float posY, float posZ);
	
	//
	// エフェクトの一時停止
	//

	void Paused(bool isPaused);

	//
	// エフェクトの停止
	//

	void Stop(void);

private:
	// エフェクトの管理者
	class EffectManager* effect_manager_;

	// Effekseerのマネージャへのポインタ
	Effekseer::Manager*	 effekseer_manager_;

	// エフェクトのデータ
	class GameEffect*	 effect_;

	// エフェクトのハンドル
	Effekseer::Handle	 effect_handle_;
};

#endif //EFFECT_RENDERER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/