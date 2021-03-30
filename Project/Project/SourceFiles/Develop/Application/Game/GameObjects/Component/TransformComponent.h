/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[TransformComponent.h]  �p������R���|�[�l���g�̃x�[�X�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�p������R���|�[�l���g�̃x�[�X�ɂȂ�N���X��`
=============================================================================*/
#ifndef TRANSFORM_COMPONENT_H_
#define	TRANSFORM_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Component.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/

/*-------------------------------------
/* �p������̃R���|�[�l���g
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

	//�p���x�N�g�����̐���
	void ComputeTransformVector(void);

	//�����x�N�g�����̐���
	void ComputeDirectionVector(void);

	//�X�V���K�v���̃`�F�b�N
	bool IsNeedUpdate(void);

	//�N�H�[�^�j�I���ɂ���]�s��̌v�Z�@
	void ComputeRotationMatrixQuaternion(float deltaTime);

	//���[���h�s��̌v�Z
	void ComputeWorldMatrix(void);

public:
	
	//
	// �ʒu���̐ݒ�
	//

	inline void SetTranslation(float posX, float posY, float posZ) { position_ = { posX, posY, posZ }; }
	inline void SetTranslation(const D3DXVECTOR3& position) { position_ = position; }
	inline void SetTranslationX(float posX) { position_.x = posX; }
	inline void SetTranslationY(float posY) { position_.y = posY; }
	inline void SetTranslationZ(float posZ) { position_.z = posZ; }

	// �ʒu���̂։��Z

	inline void AddTranslation(float addValueX, float addValueY, float addValueZ) { position_ += { addValueX, addValueY, addValueZ }; }
	inline void AddTranslation(const D3DXVECTOR3& addValue) { position_ += addValue; }
	inline void AddTranslationX(float addValueX) { position_.x += addValueX; }
	inline void AddTranslationY(float addValueY) { position_.y += addValueY; }
	inline void AddTranslationZ(float addValueZ) { position_.z += addValueZ; }

	// �ʒu���̎擾

	inline const D3DXVECTOR3* GetPosition(void) { return &position_; }
	inline const D3DXVECTOR3* GetOldPosition(void) { return &old_position_; }

	//
	// �g�k����ݒ�
	//

	inline void SetScale(float scaleX, float scaleY, float scaleZ) { scale_ = { scaleX, scaleY, scaleZ }; }
	inline void SetScale(const D3DXVECTOR3& scaleValue) { scale_ = scaleValue; }
	inline void SetScale(float scaleValue) { scale_ = { scaleValue, scaleValue, scaleValue }; }
	inline void SetScaleX(float scaleX) { scale_.x = scaleX; }
	inline void SetScaleY(float scaleY) { scale_.y = scaleY; }
	inline void SetScaleZ(float scaleZ) { scale_.z = scaleZ; }

	// �g�k���ւ̉��Z

	inline void AddScale(float addValueX, float addValueY, float addValueZ) { scale_ += {addValueX, addValueY, addValueZ}; }
	inline void AddScale(const D3DXVECTOR3& addValue) { scale_ += addValue; }
	inline void AddScale(float addValue) { scale_ += {addValue, addValue, addValue}; }
	inline void AddScaleX(float addValueX) { scale_.x += addValueX; };
	inline void AddScaleY(float addValueY) { scale_.y += addValueY; };
	inline void AddScaleZ(float addValueZ) { scale_.z += addValueZ; };

	// �g�k���̎擾

	inline const D3DXVECTOR3* GetScale(void) { return &scale_; }
	inline const D3DXVECTOR3* GetOldScale(void) { return &old_scale_; }

	//
	// ��]���̐ݒ�
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

	// ��]���ւ̉��Z

	inline void AddRotation(float addDegreeYaw, float addDegreePitch, float addDegreeRoll)
	{
		degree_yaw_   += addDegreeYaw;
		degree_pitch_ += addDegreePitch;
		degree_roll_  += addDegreeRoll;
	}

	inline void AddRotationYaw(float addDegreeYaw) { degree_yaw_ += addDegreeYaw; }
	inline void AddRotationPitch(float addDegreePitch) { degree_pitch_ += addDegreePitch; }
	inline void AddRotationRoll(float addDegreeRoll) { degree_roll_ += addDegreeRoll; }


	//��]���̎擾

	inline float GetAngleYaw(void) const { return degree_yaw_; }
	inline float GetAnglePitch(void) const { return degree_pitch_; }
	inline float GetAngleRoll(void) const { return degree_roll_; }


	//
	// �p�������x�N�g�����
	//

	inline const D3DXVECTOR3* GetFrontVector(void) { return &front_vector_; }
	inline const D3DXVECTOR3* GetUpVector(void) { return &up_vector_; }
	inline const D3DXVECTOR3* GetRightVector(void) { return &right_vector_; }

	inline void SetDirection(const D3DXVECTOR3& direction) { direction_ = direction; }
	inline const D3DXVECTOR3* GetDirection(void) { return &direction_; }


	//
	// �p���s����
	//

	inline const D3DXMATRIX* GetRotationMatrix(void) { return &rotation_matrix_; }
	inline void SetRotationMatrix(const D3DXMATRIX& rotationMatrix)
	{
		//  ��]�s���ݒ肳��Ă��邩�H
		is_set_rotation_matrix_ = true;

		// �O�������]�s���ݒ�
		rotation_matrix_ = rotationMatrix; 
	}

	inline const D3DXMATRIX* GetWorldMatrix(void) { return &world_matrix_; }

	inline const TransformComponent* GetTransformComponent(void) { return this; }

	virtual TypeID GetComponentType() const override { return TypeID::TransformComponent; };

private:
	// ��]���邩�̃t���O

	bool is_set_rotation_matrix_;
	bool is_execute_slerp_;

	// �p���x�N�g��

	D3DXVECTOR3 front_vector_
		   	  , up_vector_
		   	  , right_vector_;

	// �����x�N�g��

	D3DXVECTOR3 direction_;

	// �ʒu���

	D3DXVECTOR3 position_
			  , old_position_;

	// �g�k���

	D3DXVECTOR3 scale_
			  , old_scale_;

	// ��]���

	float degree_yaw_
	    , degree_pitch_
	    , degree_roll_;

	// ��]�̒l

	float slerp_spped_;		// ���ʕ�Ԃ̑��x
	float slerp_runtime_;	// ���ʕ�Ԃ̎��s�x

	// �N�H�[�^�j�I��
	D3DXQUATERNION quaternion_;				// �p���N�H�[�^�j�I��
	D3DXQUATERNION direction_quaternion_;	// �����N�H�[�^�j�I��

	// �e�s��̐錾
	// �g�k�s��̏��́Ascale_�ɕێ������Ă���̂ŕs�v�B
	// ���s�ړ��s��̏��́Aposition_�ɕێ������Ă���̂ŕs�v�B
	D3DXMATRIX rotation_matrix_; // ��]�s��
	D3DXMATRIX world_matrix_;	 // ���|���h�s��
};

#endif //TRANSFORM_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/