/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[EffectRendererComponent.h]  エフェクトコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：エフェクトコンポーネント
=============================================================================*/
#ifndef EFFECT_COMPONENT_H_
#define	EFFECT_COMPONENT_H_

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

	bool Init(void) override;
	void Uninit(void) override;
	void Update(float deltaTime) override;
	void Draw(class Shader* shader, class Camera* camera) override;

	// エフェクトの設定
	void SetEffect(EffectType effectTypeID);

	// エフェクト情報の取得
	class Effect* GetEffect(void);

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

	//
	// エフェクトのs姿勢情報の更新
	//

	void SetBaseMatirx(const D3DXMATRIX& matrix);

private:
	// エフェクトの管理者
	class EffectManager* effect_manager_;

	// Effekseerのマネージャへのポインタ
	Effekseer::Manager*	 effekseer_manager_;

	// エフェクトのデータ
	class Effect*		 effect_;
};

#endif //EFFECT_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/