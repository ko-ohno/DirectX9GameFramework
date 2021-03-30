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
	// �ʒu���̐ݒ�
	//
	
	inline void SetTranslation(float posX, float posY, float posZ) { eye_point_ = { posX, posY, posZ }; }
	inline void SetTranslation(const D3DXVECTOR3& position) { eye_point_ = position; }
	inline void SetTranslationX(float posX) { eye_point_.x = posX; }
	inline void SetTranslationY(float posY) { eye_point_.y = posY; }
	inline void SetTranslationZ(float posZ) { eye_point_.z = posZ; }

	//�@�ʒu���ւ̉��Z

	inline void AddTranslation(float addValueX, float addValueY, float addValueZ) { eye_point_ += { addValueX, addValueY, addValueZ }; }
	inline void AddTranslation(const D3DXVECTOR3& addValue) { eye_point_ += addValue; }
	inline void AddTranslationX(float addValueX) { eye_point_.x = addValueX; }
	inline void AddTranslationY(float addValueY) { eye_point_.y = addValueY; }
	inline void AddTranslationZ(float addValueZ) { eye_point_.z = addValueZ; }

	//�@�ʒu���̎擾�@

	inline D3DXVECTOR3 GetPositon(void) const { return eye_point_; }

	//
	// ��]���̐ݒ�
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

	// ��]���ւ̉��Z

	inline void AddRotation(float addDegreeYaw, float addDegreePitch, float addDegreeRoll)
	{
		degree_yaw_ += addDegreeYaw;
		degree_pitch_ += addDegreePitch;
		degree_roll_ += addDegreeRoll;
	}

	inline void AddRotationYaw(float addDegreeYaw) { degree_yaw_ += addDegreeYaw; }
	inline void AddRotationPitch(float addDegreePitch) { degree_pitch_ += addDegreePitch; }
	inline void AddRotationRoll(float addDegreeRoll) { degree_roll_ += addDegreeRoll; }

	//��]���̎擾

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

	// ��]���ւ̉��Z

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
	void IsSetCameraMoved(bool isCameraMoved) { is_camera_moved_ = isCameraMoved; }

	virtual TypeID GetComponentType() const override { return TypeID::CameraComponent; }

private:
protected:

	//�O�t���[���Ɣ�ׂăJ�������ړ��������̃t���O
	bool is_camera_moved_;

	// �J�����𑀍삷�邩�̃t���O
	bool is_using_camera_controller_;

	//�����_�𒆐S�ɉ�]���邩�̃t���O
	bool is_rotation_lookat_;


	// ��]���邩�̃t���O
	bool is_execute_slerp_;

	//
	// �J����������
	//

	//��ʃT�C�Y
	Vector2	   screen_aspect_size_;

	//�J�����v�f�̍s��
	
	D3DXMATRIX view_matrix_
			 , view_inverse_matrix_
			 , projection_matrix_2d_
			 , projection_matrix_3d_;

	//�J�����̎p���x�N�g��
	
	D3DXVECTOR3 front_vector_	//��̌���(�O�x�N�g��)
			  , up_vector_		//���̌���(��x�N�g��)
			  , right_vector_;	//���̌���(�E�x�N�g��)

	//�J�����̍��W

	D3DXVECTOR3 eye_point_		//���_
			  , old_eye_point_  //1�t���[���O�̃J�������W
			  , lookat_point_;	//�����X

	//
	// �J�����̎p�����
	//


	//�J�����̊p�x
	
	float degree_yaw_
		, degree_pitch_
		, degree_roll_;


	//�����_���S�̃J�����̊p�x
	
	float degree_lookat_yaw_
		, degree_lookat_pitch_
		, degree_lookat_roll_;

	// ��]�̒l

	float slerp_spped_;		// ���ʕ�Ԃ̑��x
	float slerp_runtime_;	// ���ʕ�Ԃ̎��s�x

	// �N�H�[�^�j�I��
	
	D3DXQUATERNION quaternion_;			// �p���N�H�[�^�j�I��
	D3DXQUATERNION lookat_quaternion_;	// �����N�H�[�^�j�I��

	// �e�s��̐錾

	D3DXMATRIX local_matrix_;


	D3DXMATRIX translation_lookat_matrix_;	// �����_���S�̕��s�ړ��s��
	D3DXMATRIX translation_matrix_;			// ���s�ړ��s��
	D3DXMATRIX rotation_lookat_matrix_;		// �����_���S�̉�]�s��
	D3DXMATRIX rotation_matrix_;			// �J�������S�̉�]�s��
	D3DXMATRIX world_matrix_;				// ���|���h�s��
};

#endif //CAMERA_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/