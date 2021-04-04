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

	void UpdateCameraPosition(void);
	void UpdateLookatPosition(void);

private:
	//
	// �J�����̉�]
	//

	void ComputeRotationYaw(void);
	void ComputeRotationPitch(void);
	void ComputeRotationRoll(void);

	//
	// �J�����̉�]
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
	//�@�ʒu���ւ̉��Z
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
	// �J�������W�F�ʒu���̐ݒ�
	//

	inline void SetCameraTranslation(float posX, float posY, float posZ) { eye_point_ = { posX, posY, posZ }; }
	inline void SetCameraTranslation(const D3DXVECTOR3& position) { eye_point_ = position; }
	inline void SetCameraTranslationX(float posX) { eye_point_.x = posX; }
	inline void SetCameraTranslationY(float posY) { eye_point_.y = posY; }
	inline void SetCameraTranslationZ(float posZ) { eye_point_.z = posZ; }

	// �J�������W�F�ʒu���ւ̉��Z

	inline void AddCameraTranslation(float addValueX, float addValueY, float addValueZ) { eye_point_ += { addValueX, addValueY, addValueZ }; }
	inline void AddCameraTranslation(const D3DXVECTOR3& addValue) { eye_point_ += addValue; }
	inline void AddCameraTranslationX(float addValueX) { eye_point_.x += addValueX; }
	inline void AddCameraTranslationY(float addValueY) { eye_point_.y += addValueY; }
	inline void AddCameraTranslationZ(float addValueZ) { eye_point_.z += addValueZ; }

	//
	// �J�������W�F��]���̐ݒ�
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

	// �J�������W�F��]���ւ̉��Z

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
	// �J�����F��]���̎擾
	//

	inline float GetAngleCameraYaw(void) const { return degree_yaw_; }
	inline float GetAngleCameraPitch(void) const { return degree_pitch_; }
	inline float GetAngleCameraRoll(void) const { return degree_roll_; }

public:

	//
	// �����_���W�F�ʒu���̐ݒ�
	//

	inline void SetLookAtTranslation(float posX, float posY, float posZ) { lookat_point_ = { posX, posY, posZ }; }
	inline void SetLookAtTranslation(const D3DXVECTOR3& position) { lookat_point_ = position; }
	inline void SetLookAtTranslationX(float posX) { lookat_point_.x = posX; }
	inline void SetLookAtTranslationY(float posY) { lookat_point_.y = posY; }
	inline void SetLookAtTranslationZ(float posZ) { lookat_point_.z = posZ; }

	// �����_���W�F�ʒu���ւ̉��Z

	inline void AddLookAtTranslation(float addValueX, float addValueY, float addValueZ) { lookat_point_ += { addValueX, addValueY, addValueZ }; }
	inline void AddLookAtTranslation(const D3DXVECTOR3& addValue) { lookat_point_ += addValue; }
	inline void AddLookAtTranslationX(float addValueX) { lookat_point_.x += addValueX; }
	inline void AddLookAtTranslationY(float addValueY) { lookat_point_.y += addValueY; }
	inline void AddLookAtTranslationZ(float addValueZ) { lookat_point_.z += addValueZ; }

	//
	// �����_���W�F��]���̐ݒ�
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

	// �����_���W�F��]���ւ̉��Z

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
	// �����_�F��]���̎擾
	//

	inline float GetAngleLookAtYaw(void) const { return degree_lookat_yaw_; }
	inline float GetAngleLookAtPitch(void) const { return degree_lookat_pitch_; }
	inline float GetAngleLookAtRoll(void) const { return degree_lookat_roll_; }

	//
	// �J�����E�����_���W�F�ʒu���̎擾
	//

	inline D3DXVECTOR3* GetPositon(void) { return &eye_point_; }
	inline D3DXVECTOR3* GetLookAtPositon(void) { return &lookat_point_; }

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

	//�J�������ړ��������̃t���O
	bool IsGetCameraMoved(void) const { return is_camera_moved_; }

	virtual TypeID GetComponentType() const override { return TypeID::CameraComponent; }

private:
protected:

	//�O�t���[���Ɣ�ׂăJ�������ړ��������̃t���O
	bool is_camera_moved_;

	//�����_���W����]�ɂ���čX�V���邩�̃t���O
	bool is_rotation_lookat_;

	//�e��]���ɑ΂���t���O

	bool is_rotation_yaw_
	   , is_rotation_pitch_
	   , is_rotation_roll_;

	//
	// �p�����
	//

	// �J�����E�����_�̍��W

	D3DXVECTOR3 eye_point_			//���_
			  , old_eye_point_		//1�t���[���O�̃J�������W
			  , lookat_point_;		//�����_

	// �J�����̎p���x�N�g��

	D3DXVECTOR3 front_vector_	//��̌���(�O�x�N�g��)
			  , up_vector_		//���̌���(��x�N�g��)
			  , right_vector_;	//���̌���(�E�x�N�g��)

	float viewing_vector_length_; //�����x�N�g���̒���

	// �J�����̊p�x
	
	float degree_yaw_
		, degree_pitch_
		, degree_roll_;

	// �����_���S�̃J�����̊p�x
	
	float degree_lookat_yaw_
		, degree_lookat_pitch_
		, degree_lookat_roll_;

	//
	// ���W�ϊ����
	//

	//��ʃT�C�Y
	Vector2 screen_aspect_size_;

	// �r���[�ϊ��s��

	D3DXMATRIX view_matrix_
			 , view_inverse_matrix_;

	// �v���W�F�N�V�����ϊ��s��

	D3DXMATRIX projection_matrix_2d_
			 , projection_matrix_3d_;

	static constexpr float DEGREE_NORMALIZE_OFFSET = 180.f;
};

#endif //CAMERA_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/