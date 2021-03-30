/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[CameraComponent.h] カメラのベースコンポーネント
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：カメラコンポーネントのベースになるクラス定義
=============================================================================*/
#ifndef CAMERA_COMPONENT_H_
#define	CAMERA_COMPONENT_H_

/*--- インクルードファイル ---*/
#include "../../../../StdAfx.h"
#include "../Component.h"
#include "../../../Math.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* カメラコンポーネントのベースクラス
-------------------------------------*/
class CameraComponent : public Component
{
public:
	CameraComponent(class GameObject* owner, int updateOrder = 100);
	~CameraComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	void ComputeTransformVector(void);

private:
	
	void UpdateCameraPosition(float deltaTime);
	void UpdateLookatPosition(float deltaTime);

	void ComputeWorldMatrix(void);
	void ComputeLocalMatrix(void);


	void ComputeViewMatrix(void);
	void ComputeViewInverseMatrix(void);
	void ComputeProjection2DMatrix(void);
	void ComputeProjection3DMatrix(void);

public:

	//
	// 位置情報の設定
	//
	
	inline void SetTranslation(float posX, float posY, float posZ) { eye_point_ = { posX, posY, posZ }; }
	inline void SetTranslation(const D3DXVECTOR3& position) { eye_point_ = position; }
	inline void SetTranslationX(float posX) { eye_point_.x = posX; }
	inline void SetTranslationY(float posY) { eye_point_.y = posY; }
	inline void SetTranslationZ(float posZ) { eye_point_.z = posZ; }

	//　位置情報への加算

	inline void AddTranslation(float addValueX, float addValueY, float addValueZ) { eye_point_ += { addValueX, addValueY, addValueZ }; }
	inline void AddTranslation(const D3DXVECTOR3& addValue) { eye_point_ += addValue; }
	inline void AddTranslationX(float addValueX) { eye_point_.x = addValueX; }
	inline void AddTranslationY(float addValueY) { eye_point_.y = addValueY; }
	inline void AddTranslationZ(float addValueZ) { eye_point_.z = addValueZ; }

	//　位置情報の取得　

	inline D3DXVECTOR3 GetPositon(void) const { return eye_point_; }

	//
	// 回転情報の設定
	//

	inline bool IsSetExecuteSlerp(bool isExecuteSlerp) { is_execute_slerp_ = isExecuteSlerp; }
	inline void SetSlerpSpeed(float slerpSpeed) { slerp_spped_ = slerpSpeed; }

	inline void SetRotation(float degreeYaw, float degreePitch, float degreeRoll)
	{
		degree_yaw_ = degreeYaw;
		degree_pitch_ = degreePitch;
		degree_roll_ = degreeRoll;
	}

	inline void SetRotationYaw(float degreeYaw) { degree_yaw_ = degreeYaw; }
	inline void SetRotationPitch(float degreePitch) { degree_pitch_ = degreePitch; }
	inline void SetRotationRoll(float degreeRoll) { degree_roll_ = degreeRoll; }

	// 回転情報への加算

	inline void AddRotation(float addDegreeYaw, float addDegreePitch, float addDegreeRoll)
	{
		degree_yaw_ += addDegreeYaw;
		degree_pitch_ += addDegreePitch;
		degree_roll_ += addDegreeRoll;
	}

	inline void AddRotationYaw(float addDegreeYaw) { degree_yaw_ += addDegreeYaw; }
	inline void AddRotationPitch(float addDegreePitch) { degree_pitch_ += addDegreePitch; }
	inline void AddRotationRoll(float addDegreeRoll) { degree_roll_ += addDegreeRoll; }

	//回転情報の取得

	inline float GetAngleYaw(void) const { return degree_yaw_; }
	inline float GetAnglePitch(void) const { return degree_pitch_; }
	inline float GetAngleRoll(void) const { return degree_roll_; }


	inline void SetLookAtTranslation(float posX, float posY, float posZ) { lookat_point_ = { posX, posY, posZ }; }
	inline void SetLookAtTranslation(const D3DXVECTOR3& position) { lookat_point_ = position; }
	inline void SetLookAtTranslationX(float posX) { lookat_point_.x = posX; }
	inline void SetLookAtTranslationY(float posY) { lookat_point_.y = posY; }
	inline void SetLookAtTranslationZ(float posZ) { lookat_point_.z = posZ; }

	inline void AddLookAtTranslation(float addValueX, float addValueY, float addValueZ) { lookat_point_ += { addValueX, addValueY, addValueZ }; }
	inline void AddLookAtTranslation(const D3DXVECTOR3& addValue) { lookat_point_ += addValue; }
	inline void AddLookAtTranslationX(float addValueX) { lookat_point_.x = addValueX; }
	inline void AddLookAtTranslationY(float addValueY) { lookat_point_.y = addValueY; }
	inline void AddLookAtTranslationZ(float addValueZ) { lookat_point_.z = addValueZ; }

	inline D3DXVECTOR3 GetLookAtPositon(void) const { return lookat_point_; }

	inline void SetLookAtRotation(float degreeYaw, float degreePitch, float degreeRoll)
	{
		degree_lookat_yaw_ = degreeYaw;
		degree_lookat_pitch_ = degreePitch;
		degree_lookat_roll_ = degreeRoll;
	}

	inline void SetLookAtRotationYaw(float degreeYaw) { degree_lookat_yaw_ = degreeYaw; }
	inline void SetLookAtRotationPitch(float degreePitch) { degree_lookat_pitch_ = degreePitch; }
	inline void SetLookAtRotationRoll(float degreeRoll) { degree_lookat_roll_ = degreeRoll; }

	// 回転情報への加算

	inline void AddLookAtRotation(float addDegreeYaw, float addDegreePitch, float addDegreeRoll)
	{
		degree_lookat_yaw_ += addDegreeYaw;
		degree_lookat_pitch_ += addDegreePitch;
		degree_lookat_roll_ += addDegreeRoll;
	}

	inline void AddLookAtRotationYaw(float addDegreeYaw) { degree_lookat_yaw_ += addDegreeYaw; }
	inline void AddLookAtRotationPitch(float addDegreePitch) { degree_lookat_pitch_ += addDegreePitch; }
	inline void AddLookAtRotationRoll(float addDegreeRoll) { degree_lookat_roll_ += addDegreeRoll; }






	//
	// 姿勢方向ベクトル情報
	//

	inline const D3DXVECTOR3* GetFrontVector(void) { return &front_vector_; }
	inline const D3DXVECTOR3* GetUpVector(void) { return &up_vector_; }
	inline const D3DXVECTOR3* GetRightVector(void) { return &right_vector_; }

	//
	// カメラ行列情報
	//

	// ビュー行列の取得
	D3DXMATRIX* GetViewMatrix(void) { return &view_matrix_; }

	// 逆ビュー行列の取得
	D3DXMATRIX* GetViewInverseMatrix(void) { return &view_inverse_matrix_; }

	// 2Dプロジェクション行列の取得
	D3DXMATRIX* GetProjection2DMatrix(void) { return &projection_matrix_2d_; }

	// 3Dプロジェクション行列の取得
	D3DXMATRIX* GetProjection3DMatrix(void) { return &projection_matrix_3d_; }
	
	//アスペクト比率の設定
	void SetScreenAspectSize(Vector2& aspectSize) { screen_aspect_size_ = aspectSize; }

	//カメラが移動したかのフラグ

	bool IsGetCameraMoved(void) const { return is_camera_moved_; }
	void IsSetCameraMoved(bool isCameraMoved) { is_camera_moved_ = isCameraMoved; }

	virtual TypeID GetComponentType() const override { return TypeID::CameraComponent; }

private:
protected:

	//前フレームと比べてカメラが移動したかのフラグ
	bool is_camera_moved_;

	// カメラを操作するかのフラグ
	bool is_using_camera_controller_;

	//注視点を中心に回転するかのフラグ
	bool is_rotation_lookat_;


	// 回転するかのフラグ
	bool is_execute_slerp_;

	//
	// カメラ制御情報
	//

	//画面サイズ
	Vector2	   screen_aspect_size_;

	//カメラ要素の行列
	
	D3DXMATRIX view_matrix_
			 , view_inverse_matrix_
			 , projection_matrix_2d_
			 , projection_matrix_3d_;

	//カメラの姿勢ベクトル
	
	D3DXVECTOR3 front_vector_	//顔の向き(前ベクトル)
			  , up_vector_		//頭の向き(上ベクトル)
			  , right_vector_;	//頭の向き(右ベクトル)

	//カメラの座標

	D3DXVECTOR3 eye_point_		//視点
			  , old_eye_point_  //1フレーム前のカメラ座標
			  , lookat_point_;	//注視店

	//
	// カメラの姿勢情報
	//


	//カメラの角度
	
	float degree_yaw_
		, degree_pitch_
		, degree_roll_;


	//注視点中心のカメラの角度
	
	float degree_lookat_yaw_
		, degree_lookat_pitch_
		, degree_lookat_roll_;

	// 回転の値

	float slerp_spped_;		// 球面補間の速度
	float slerp_runtime_;	// 球面補間の実行度

	// クォータニオン
	
	D3DXQUATERNION quaternion_;			// 姿勢クォータニオン
	D3DXQUATERNION lookat_quaternion_;	// 向きクォータニオン

	// 各行列の宣言

	D3DXMATRIX local_matrix_;


	D3DXMATRIX translation_lookat_matrix_;	// 注視点中心の平行移動行列
	D3DXMATRIX translation_matrix_;			// 平行移動行列
	D3DXMATRIX rotation_lookat_matrix_;		// 注視点中心の回転行列
	D3DXMATRIX rotation_matrix_;			// カメラ中心の回転行列
	D3DXMATRIX world_matrix_;				// ワ－ルド行列
};

#endif //CAMERA_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/