/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[TransformComponent.h]  姿勢制御コンポーネントのベースコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：姿勢制御コンポーネントのベースになるクラス定義
=============================================================================*/
#ifndef TRANSFORM_COMPONENT_H_
#define	TRANSFORM_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../Component.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/

/*-------------------------------------
/* 姿勢制御のコンポーネント
-------------------------------------*/
class TransformComponent : public Component
{
public:
	TransformComponent(class GameObject* owner, int updateOrder = 100);
	~TransformComponent(void);

	bool Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;

private:

	//姿勢ベクトル情報の生成
	void ComputeTransformVector(void);

	//向きベクトル情報の生成
	void ComputeDirectionVector(void);

	//更新が必要かのチェック
	bool IsNeedUpdate(void);

	//クォータニオンによる回転行列の計算　
	void ComputeRotationMatrixQuaternion(float deltaTime);

	//ワールド行列の計算
	void ComputeWorldMatrix(void);

public:
	
	//
	// 位置情報の設定
	//

	inline void SetTranslation(float posX, float posY, float posZ) { position_ = { posX, posY, posZ }; }
	inline void SetTranslation(const D3DXVECTOR3& position) { position_ = position; }
	inline void SetTranslationX(float posX) { position_.x = posX; }
	inline void SetTranslationY(float posY) { position_.y = posY; }
	inline void SetTranslationZ(float posZ) { position_.z = posZ; }

	// 位置情報のへ加算

	inline void AddTranslation(float addValueX, float addValueY, float addValueZ) { position_ += { addValueX, addValueY, addValueZ }; }
	inline void AddTranslation(const D3DXVECTOR3& addValue) { position_ += addValue; }
	inline void AddTranslationX(float addValueX) { position_.x += addValueX; }
	inline void AddTranslationY(float addValueY) { position_.y += addValueY; }
	inline void AddTranslationZ(float addValueZ) { position_.z += addValueZ; }

	// 位置情報の取得

	inline const D3DXVECTOR3* GetPosition(void) { return &position_; }
	inline const D3DXVECTOR3* GetOldPosition(void) { return &old_position_; }

	//
	// 拡縮情報を設定
	//

	inline void SetScale(float scaleX, float scaleY, float scaleZ) { scale_ = { scaleX, scaleY, scaleZ }; }
	inline void SetScale(const D3DXVECTOR3& scaleValue) { scale_ = scaleValue; }
	inline void SetScale(float scaleValue) { scale_ = { scaleValue, scaleValue, scaleValue }; }
	inline void SetScaleX(float scaleX) { scale_.x = scaleX; }
	inline void SetScaleY(float scaleY) { scale_.y = scaleY; }
	inline void SetScaleZ(float scaleZ) { scale_.z = scaleZ; }

	// 拡縮情報への加算

	inline void AddScale(float addValueX, float addValueY, float addValueZ) { scale_ += {addValueX, addValueY, addValueZ}; }
	inline void AddScale(const D3DXVECTOR3& addValue) { scale_ += addValue; }
	inline void AddScale(float addValue) { scale_ += {addValue, addValue, addValue}; }
	inline void AddScaleX(float addValueX) { scale_.x += addValueX; };
	inline void AddScaleY(float addValueY) { scale_.y += addValueY; };
	inline void AddScaleZ(float addValueZ) { scale_.z += addValueZ; };

	// 拡縮情報の取得

	inline const D3DXVECTOR3* GetScale(void) { return &scale_; }
	inline const D3DXVECTOR3* GetOldScale(void) { return &old_scale_; }

	//
	// 回転情報の設定
	//

	inline bool IsSetExecuteSlerp(bool isExecuteSlerp) { is_execute_slerp_ = isExecuteSlerp; }
	inline void SetSlerpSpeed(float slerpSpeed) { slerp_spped_ = slerpSpeed; }

	inline void SetRotation(float degreeYaw, float degreePitch, float degreeRoll)
	{
		degree_yaw_   = degreeYaw;
		degree_pitch_ = degreePitch;
		degree_roll_  = degreeRoll;
	}

	inline void SetRotationYaw(float degreeYaw) { degree_yaw_ = degreeYaw; }
	inline void SetRotationPitch(float degreePitch) { degree_pitch_ = degreePitch; }
	inline void SetRotationRoll(float degreeRoll) { degree_roll_ = degreeRoll; }

	// 回転情報への加算

	inline void AddRotation(float addDegreeYaw, float addDegreePitch, float addDegreeRoll)
	{
		degree_yaw_   += addDegreeYaw;
		degree_pitch_ += addDegreePitch;
		degree_roll_  += addDegreeRoll;
	}

	inline void AddRotationYaw(float addDegreeYaw) { degree_yaw_ += addDegreeYaw; }
	inline void AddRotationPitch(float addDegreePitch) { degree_pitch_ += addDegreePitch; }
	inline void AddRotationRoll(float addDegreeRoll) { degree_roll_ += addDegreeRoll; }


	//回転情報の取得

	inline float GetAngleYaw(void) const { return degree_yaw_; }
	inline float GetAnglePitch(void) const { return degree_pitch_; }
	inline float GetAngleRoll(void) const { return degree_roll_; }


	//
	// 姿勢方向ベクトル情報
	//

	inline const D3DXVECTOR3* GetFrontVector(void) { return &front_vector_; }
	inline const D3DXVECTOR3* GetUpVector(void) { return &up_vector_; }
	inline const D3DXVECTOR3* GetRightVector(void) { return &right_vector_; }

	inline void SetDirection(const D3DXVECTOR3& direction) { direction_ = direction; }
	inline const D3DXVECTOR3* GetDirection(void) { return &direction_; }


	//
	// 姿勢行列情報
	//

	inline const D3DXMATRIX* GetRotationMatrix(void) { return &rotation_matrix_; }
	inline void SetRotationMatrix(const D3DXMATRIX& rotationMatrix)
	{
		//  回転行列を設定されているか？
		is_set_rotation_matrix_ = true;

		// 外部から回転行列を設定
		rotation_matrix_ = rotationMatrix; 
	}

	inline const D3DXMATRIX* GetWorldMatrix(void) { return &world_matrix_; }

	inline const TransformComponent* GetTransformComponent(void) { return this; }

	virtual TypeID GetComponentType() const override { return TypeID::TransformComponent; };

private:
	// 回転するかのフラグ

	bool is_set_rotation_matrix_;
	bool is_execute_slerp_;

	// 姿勢ベクトル

	D3DXVECTOR3 front_vector_
		   	  , up_vector_
		   	  , right_vector_;

	// 向きベクトル

	D3DXVECTOR3 direction_;

	// 位置情報

	D3DXVECTOR3 position_
			  , old_position_;

	// 拡縮情報

	D3DXVECTOR3 scale_
			  , old_scale_;

	// 回転情報

	float degree_yaw_
	    , degree_pitch_
	    , degree_roll_;

	// 回転の値

	float slerp_spped_;		// 球面補間の速度
	float slerp_runtime_;	// 球面補間の実行度

	// クォータニオン
	D3DXQUATERNION quaternion_;				// 姿勢クォータニオン
	D3DXQUATERNION direction_quaternion_;	// 向きクォータニオン

	// 各行列の宣言
	// 拡縮行列の情報は、scale_に保持させているので不要。
	// 平行移動行列の情報は、position_に保持させているので不要。
	D3DXMATRIX rotation_matrix_; // 回転行列
	D3DXMATRIX world_matrix_;	 // ワ－ルド行列
};

#endif //TRANSFORM_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/