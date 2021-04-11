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

	void UpdateTransform(float deltaTime);
	void ComputeCameraMovement(float deltaTime);
	void ComputeRotationCameraPosition(float deltaTime);
	void ComputeRotationLookatPosition(float deltaTime);

private:
	void ComputeViewMatrix(void);
	void ComputeViewInverseMatrix(void);
	void ComputeProjection2DMatrix(void);
	void ComputeProjection3DMatrix(void);

public:
	//
	//　速度の設定
	//

	void SetMoveSpeed(float speed) { move_speed_ = speed; }
	void SetRotationDegree(float degree) { rotation_degree_ = degree; }

public:

	//
	// カメラ座標：位置情報の設定
	//

	inline void SetCameraTranslation(float posX, float posY, float posZ) { position_ = { posX, posY, posZ }; }
	inline void SetCameraTranslation(const D3DXVECTOR3& position) { position_ = position; }
	inline void SetCameraTranslationX(float posX) { position_.x = posX; }
	inline void SetCameraTranslationY(float posY) { position_.y = posY; }
	inline void SetCameraTranslationZ(float posZ) { position_.z = posZ; }

	// カメラ座標：位置情報への加算

	inline void AddCameraTranslation(float addValueX, float addValueY, float addValueZ) { position_ += { addValueX, addValueY, addValueZ }; }
	inline void AddCameraTranslation(const D3DXVECTOR3& addValue) { position_ += addValue; }
	inline void AddCameraTranslationX(float addValueX) { position_.x += addValueX; }
	inline void AddCameraTranslationY(float addValueY) { position_.y += addValueY; }
	inline void AddCameraTranslationZ(float addValueZ) { position_.z += addValueZ; }

public:

	//
	// 注視点座標：位置情報の設定
	//

	inline void SetLookAtTranslation(float posX, float posY, float posZ) { lookat_position_ = { posX, posY, posZ }; }
	inline void SetLookAtTranslation(const D3DXVECTOR3& position) { lookat_position_ = position; }
	inline void SetLookAtTranslationX(float posX) { lookat_position_.x = posX; }
	inline void SetLookAtTranslationY(float posY) { lookat_position_.y = posY; }
	inline void SetLookAtTranslationZ(float posZ) { lookat_position_.z = posZ; }

	// 注視点座標：位置情報への加算

	inline void AddLookAtTranslation(float addValueX, float addValueY, float addValueZ) { lookat_position_ += { addValueX, addValueY, addValueZ }; }
	inline void AddLookAtTranslation(const D3DXVECTOR3& addValue) { lookat_position_ += addValue; }
	inline void AddLookAtTranslationX(float addValueX) { lookat_position_.x += addValueX; }
	inline void AddLookAtTranslationY(float addValueY) { lookat_position_.y += addValueY; }
	inline void AddLookAtTranslationZ(float addValueZ) { lookat_position_.z += addValueZ; }

	//
	// カメラ・注視点座標：位置情報の取得
	//

	inline D3DXVECTOR3* GetPositon(void) { return &position_; }
	inline D3DXVECTOR3* GetLookAtPositon(void) { return &lookat_position_; }

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

	//カメラをコントロールするか
	bool IsGetCameraControlling(void) { return is_camera_controlling_; }
	void IsSetCameraControlling(bool isCameraControlling) { is_camera_controlling_ = isCameraControlling; }

	//カメラが移動したかのフラグ
	bool IsGetCameraMoved(void) const { return is_camera_moved_; }

	virtual TypeID GetComponentType() const override { return TypeID::CameraComponent; }

private:
protected:

	//更新が必要かどうかのフラグ
	bool is_need_update_;

	//前フレームと比べてカメラが移動したかのフラグ
	bool is_camera_moved_;

	// カメラを操作するか
	bool is_camera_controlling_;

	//
	// 姿勢情報
	//

	// カメラ・注視点の座標

	D3DXVECTOR3 position_			//視点
			  , old_position_		//1フレーム前のカメラ座標
			  , lookat_position_;	//注視点

	// カメラの姿勢ベクトル

	D3DXVECTOR3 front_vector_	//顔の向き(前ベクトル)
			  , up_vector_		//頭の向き(上ベクトル)
			  , right_vector_;	//頭の向き(右ベクトル)

	// カメラの移動向きベクトル
	D3DXVECTOR3 move_direction_;

	//移動倍率
	float movement_scale_;

	// 移動の速度
	float move_speed_;

	// 回転の速度
	float rotation_degree_;

	// 視線ベクトルの長さ
	float viewing_vector_length_;   

	//
	// 座標変換情報
	//

	// 画面サイズ
	Vector2 screen_aspect_size_;

	// ビュー変換行列

	D3DXMATRIX view_matrix_
			 , view_inverse_matrix_;

	// プロジェクション変換行列

	D3DXMATRIX projection_matrix_2d_
			 , projection_matrix_3d_;
};

#endif //CAMERA_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/