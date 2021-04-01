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

private:
	//
	// カメラ状態の更新
	//

	void UpdateCameraState(void);

	//
	// カメラ視線ベクトルの更新
	//

	void UpdateViewingVectorLength(void);

	//
	// カメラ座標の更新
	//

	void UpdateCameraPosition(void);
	void UpdateLookatPosition(void);

private:
	//
	// カメラの回転
	//

	void ComputeRotationYaw(void);
	void ComputeRotationPitch(void);
	void ComputeRotationRoll(void);

	//
	// カメラの回転
	//

	void ComputeRotationLookatYaw(void);
	void ComputeRotationLookatPitch(void);
	void ComputeRotationLookatRoll(void);

private:
	void ComputeViewMatrix(void);
	void ComputeViewInverseMatrix(void);
	void ComputeProjection2DMatrix(void);
	void ComputeProjection3DMatrix(void);

public:
	//
	//　位置情報への加算
	//

	inline void AddTranslation(float addValueX, float addValueY, float addValueZ)
	{
		eye_point_	  += { addValueX, addValueY, addValueZ };
		lookat_point_ += { addValueX, addValueY, addValueZ };
	}

	inline void AddTranslation(const D3DXVECTOR3& addValue)
	{
		eye_point_	  += addValue;
		lookat_point_ += addValue;
	}

	inline void AddTranslationX(float addValueX)
	{
		eye_point_.x	+= addValueX;
		lookat_point_.x += addValueX;
	}
	
	inline void AddTranslationY(float addValueY)
	{
		eye_point_.y	+= addValueY;
		lookat_point_.y += addValueY;
	}
	
	inline void AddTranslationZ(float addValueZ)
	{
		eye_point_.z	+= addValueZ;
		lookat_point_.z += addValueZ;
	}

public:

	//
	// カメラ座標：位置情報の設定
	//

	inline void SetCameraTranslation(float posX, float posY, float posZ) { eye_point_ = { posX, posY, posZ }; }
	inline void SetCameraTranslation(const D3DXVECTOR3& position) { eye_point_ = position; }
	inline void SetCameraTranslationX(float posX) { eye_point_.x = posX; }
	inline void SetCameraTranslationY(float posY) { eye_point_.y = posY; }
	inline void SetCameraTranslationZ(float posZ) { eye_point_.z = posZ; }

	// カメラ座標：位置情報への加算

	inline void AddCameraTranslation(float addValueX, float addValueY, float addValueZ) { eye_point_ += { addValueX, addValueY, addValueZ }; }
	inline void AddCameraTranslation(const D3DXVECTOR3& addValue) { eye_point_ += addValue; }
	inline void AddCameraTranslationX(float addValueX) { eye_point_.x += addValueX; }
	inline void AddCameraTranslationY(float addValueY) { eye_point_.y += addValueY; }
	inline void AddCameraTranslationZ(float addValueZ) { eye_point_.z += addValueZ; }

	//
	// カメラ座標：回転情報の設定
	//

	inline void SetCameraRotation(float degreeYaw, float degreePitch, float degreeRoll)
	{
		degree_yaw_ = degreeYaw;
		degree_pitch_ = degreePitch;
		degree_roll_ = degreeRoll;
	}

	inline void SetCameraRotationYaw(float degreeYaw) { degree_yaw_ = degreeYaw; }
	inline void SetCameraRotationPitch(float degreePitch) { degree_pitch_ = degreePitch; }
	inline void SetCameraRotationRoll(float degreeRoll) { degree_roll_ = degreeRoll; }

	// カメラ座標：回転情報への加算

	inline void AddCameraRotation(float addDegreeYaw, float addDegreePitch, float addDegreeRoll)
	{
		degree_yaw_ += addDegreeYaw;
		degree_pitch_ += addDegreePitch;
		degree_roll_ += addDegreeRoll;
	}

	inline void AddCameraRotationYaw(float addDegreeYaw) { degree_yaw_ += addDegreeYaw; }
	inline void AddCameraRotationPitch(float addDegreePitch) { degree_pitch_ += addDegreePitch; }
	inline void AddCameraRotationRoll(float addDegreeRoll) { degree_roll_ += addDegreeRoll; }

	//
	// カメラ：回転情報の取得
	//

	inline float GetAngleCameraYaw(void) const { return degree_yaw_; }
	inline float GetAngleCameraPitch(void) const { return degree_pitch_; }
	inline float GetAngleCameraRoll(void) const { return degree_roll_; }

public:

	//
	// 注視点座標：位置情報の設定
	//

	inline void SetLookAtTranslation(float posX, float posY, float posZ) { lookat_point_ = { posX, posY, posZ }; }
	inline void SetLookAtTranslation(const D3DXVECTOR3& position) { lookat_point_ = position; }
	inline void SetLookAtTranslationX(float posX) { lookat_point_.x = posX; }
	inline void SetLookAtTranslationY(float posY) { lookat_point_.y = posY; }
	inline void SetLookAtTranslationZ(float posZ) { lookat_point_.z = posZ; }

	// 注視点座標：位置情報への加算

	inline void AddLookAtTranslation(float addValueX, float addValueY, float addValueZ) { lookat_point_ += { addValueX, addValueY, addValueZ }; }
	inline void AddLookAtTranslation(const D3DXVECTOR3& addValue) { lookat_point_ += addValue; }
	inline void AddLookAtTranslationX(float addValueX) { lookat_point_.x += addValueX; }
	inline void AddLookAtTranslationY(float addValueY) { lookat_point_.y += addValueY; }
	inline void AddLookAtTranslationZ(float addValueZ) { lookat_point_.z += addValueZ; }

	//
	// 注視点座標：回転情報の設定
	//

	inline void SetLookAtRotation(float degreeYaw, float degreePitch, float degreeRoll)
	{
		degree_lookat_yaw_ = degreeYaw;
		degree_lookat_pitch_ = degreePitch;
		degree_lookat_roll_ = degreeRoll;
	}

	inline void SetLookAtRotationYaw(float degreeYaw) { degree_lookat_yaw_ = degreeYaw; }
	inline void SetLookAtRotationPitch(float degreePitch) { degree_lookat_pitch_ = degreePitch; }
	inline void SetLookAtRotationRoll(float degreeRoll) { degree_lookat_roll_ = degreeRoll; }

	// 注視点座標：回転情報への加算

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
	// 注視点：回転情報の取得
	//

	inline float GetAngleLookAtYaw(void) const { return degree_lookat_yaw_; }
	inline float GetAngleLookAtPitch(void) const { return degree_lookat_pitch_; }
	inline float GetAngleLookAtRoll(void) const { return degree_lookat_roll_; }

	//
	// カメラ・注視点座標：位置情報の取得
	//

	inline D3DXVECTOR3* GetPositon(void) { return &eye_point_; }
	inline D3DXVECTOR3* GetLookAtPositon(void) { return &lookat_point_; }

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

	virtual TypeID GetComponentType() const override { return TypeID::CameraComponent; }

private:
protected:

	//前フレームと比べてカメラが移動したかのフラグ
	bool is_camera_moved_;

	//注視点座標を回転によって更新するかのフラグ
	bool is_rotation_lookat_;

	//各回転軸に対するフラグ

	bool is_rotation_yaw_
	   , is_rotation_pitch_
	   , is_rotation_roll_;

	//
	// 姿勢情報
	//

	// カメラ・注視点の座標

	D3DXVECTOR3 eye_point_			//視点
			  , old_eye_point_		//1フレーム前のカメラ座標
			  , lookat_point_;		//注視点

	// カメラの姿勢ベクトル

	D3DXVECTOR3 front_vector_	//顔の向き(前ベクトル)
			  , up_vector_		//頭の向き(上ベクトル)
			  , right_vector_;	//頭の向き(右ベクトル)

	float viewing_vector_length_; //視線ベクトルの長さ

	// カメラの角度
	
	float degree_yaw_
		, degree_pitch_
		, degree_roll_;

	// 注視点中心のカメラの角度
	
	float degree_lookat_yaw_
		, degree_lookat_pitch_
		, degree_lookat_roll_;

	//
	// 座標変換情報
	//

	//画面サイズ
	Vector2 screen_aspect_size_;

	// ビュー変換行列

	D3DXMATRIX view_matrix_
			 , view_inverse_matrix_;

	// プロジェクション変換行列

	D3DXMATRIX projection_matrix_2d_
			 , projection_matrix_3d_;

	static constexpr float DEGREE_NORMALIZE_OFFSET = 180.f;
};

#endif //CAMERA_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/