/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[CameraComponent.h] �J�����̃x�[�X�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�J�����R���|�[�l���g�̃x�[�X�ɂȂ�N���X��`
=============================================================================*/
#ifndef CAMERA_COMPONENT_H_
#define	CAMERA_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../StdAfx.h"
#include "../Component.h"
#include "../../../Math.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �J�����R���|�[�l���g�̃x�[�X�N���X
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
	// �J������Ԃ̍X�V
	//

	void UpdateCameraState(void);

	//
	// �J���������x�N�g���̍X�V
	//

	void UpdateViewingVectorLength(void);

	//
	// �J�������W�̍X�V
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
	//�@���x�̐ݒ�
	//

	void SetMoveSpeed(float speed) { move_speed_ = speed; }
	void SetRotationDegree(float degree) { rotation_degree_ = degree; }

public:

	//
	// �J�������W�F�ʒu���̐ݒ�
	//

	inline void SetCameraTranslation(float posX, float posY, float posZ) { position_ = { posX, posY, posZ }; }
	inline void SetCameraTranslation(const D3DXVECTOR3& position) { position_ = position; }
	inline void SetCameraTranslationX(float posX) { position_.x = posX; }
	inline void SetCameraTranslationY(float posY) { position_.y = posY; }
	inline void SetCameraTranslationZ(float posZ) { position_.z = posZ; }

	// �J�������W�F�ʒu���ւ̉��Z

	inline void AddCameraTranslation(float addValueX, float addValueY, float addValueZ) { position_ += { addValueX, addValueY, addValueZ }; }
	inline void AddCameraTranslation(const D3DXVECTOR3& addValue) { position_ += addValue; }
	inline void AddCameraTranslationX(float addValueX) { position_.x += addValueX; }
	inline void AddCameraTranslationY(float addValueY) { position_.y += addValueY; }
	inline void AddCameraTranslationZ(float addValueZ) { position_.z += addValueZ; }

public:

	//
	// �����_���W�F�ʒu���̐ݒ�
	//

	inline void SetLookAtTranslation(float posX, float posY, float posZ) { lookat_position_ = { posX, posY, posZ }; }
	inline void SetLookAtTranslation(const D3DXVECTOR3& position) { lookat_position_ = position; }
	inline void SetLookAtTranslationX(float posX) { lookat_position_.x = posX; }
	inline void SetLookAtTranslationY(float posY) { lookat_position_.y = posY; }
	inline void SetLookAtTranslationZ(float posZ) { lookat_position_.z = posZ; }

	// �����_���W�F�ʒu���ւ̉��Z

	inline void AddLookAtTranslation(float addValueX, float addValueY, float addValueZ) { lookat_position_ += { addValueX, addValueY, addValueZ }; }
	inline void AddLookAtTranslation(const D3DXVECTOR3& addValue) { lookat_position_ += addValue; }
	inline void AddLookAtTranslationX(float addValueX) { lookat_position_.x += addValueX; }
	inline void AddLookAtTranslationY(float addValueY) { lookat_position_.y += addValueY; }
	inline void AddLookAtTranslationZ(float addValueZ) { lookat_position_.z += addValueZ; }

	//
	// �J�����E�����_���W�F�ʒu���̎擾
	//

	inline D3DXVECTOR3* GetPositon(void) { return &position_; }
	inline D3DXVECTOR3* GetLookAtPositon(void) { return &lookat_position_; }

	//
	// �p�������x�N�g�����
	//

	inline const D3DXVECTOR3* GetFrontVector(void) { return &front_vector_; }
	inline const D3DXVECTOR3* GetUpVector(void) { return &up_vector_; }
	inline const D3DXVECTOR3* GetRightVector(void) { return &right_vector_; }

	//
	// �J�����s����
	//

	// �r���[�s��̎擾
	D3DXMATRIX* GetViewMatrix(void) { return &view_matrix_; }

	// �t�r���[�s��̎擾
	D3DXMATRIX* GetViewInverseMatrix(void) { return &view_inverse_matrix_; }

	// 2D�v���W�F�N�V�����s��̎擾
	D3DXMATRIX* GetProjection2DMatrix(void) { return &projection_matrix_2d_; }

	// 3D�v���W�F�N�V�����s��̎擾
	D3DXMATRIX* GetProjection3DMatrix(void) { return &projection_matrix_3d_; }
	
	//�A�X�y�N�g�䗦�̐ݒ�
	void SetScreenAspectSize(Vector2& aspectSize) { screen_aspect_size_ = aspectSize; }

	//�J�������R���g���[�����邩
	bool IsGetCameraControlling(void) { return is_camera_controlling_; }
	void IsSetCameraControlling(bool isCameraControlling) { is_camera_controlling_ = isCameraControlling; }

	//�J�������ړ��������̃t���O
	bool IsGetCameraMoved(void) const { return is_camera_moved_; }

	virtual TypeID GetComponentType() const override { return TypeID::CameraComponent; }

private:
protected:

	//�X�V���K�v���ǂ����̃t���O
	bool is_need_update_;

	//�O�t���[���Ɣ�ׂăJ�������ړ��������̃t���O
	bool is_camera_moved_;

	// �J�����𑀍삷�邩
	bool is_camera_controlling_;

	//
	// �p�����
	//

	// �J�����E�����_�̍��W

	D3DXVECTOR3 position_			//���_
			  , old_position_		//1�t���[���O�̃J�������W
			  , lookat_position_;	//�����_

	// �J�����̎p���x�N�g��

	D3DXVECTOR3 front_vector_	//��̌���(�O�x�N�g��)
			  , up_vector_		//���̌���(��x�N�g��)
			  , right_vector_;	//���̌���(�E�x�N�g��)

	// �J�����̈ړ������x�N�g��
	D3DXVECTOR3 move_direction_;

	//�ړ��{��
	float movement_scale_;

	// �ړ��̑��x
	float move_speed_;

	// ��]�̑��x
	float rotation_degree_;

	// �����x�N�g���̒���
	float viewing_vector_length_;   

	//
	// ���W�ϊ����
	//

	// ��ʃT�C�Y
	Vector2 screen_aspect_size_;

	// �r���[�ϊ��s��

	D3DXMATRIX view_matrix_
			 , view_inverse_matrix_;

	// �v���W�F�N�V�����ϊ��s��

	D3DXMATRIX projection_matrix_2d_
			 , projection_matrix_3d_;
};

#endif //CAMERA_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/