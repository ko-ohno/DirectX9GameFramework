/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Actor.h] �A�N�^�[�Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�A�N�^�[�Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef ACTOR_H_
#define	ACTOR_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../SandBox.h"

/*-------------------------------------
/* �A�N�^�[�Q�[���I�u�W�F�N�g
-------------------------------------*/
class Actor : public SandBox
{
public:
	Actor(class Game* game);
	virtual ~Actor(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	// �Q�[���I�u�W�F�N�g�̎��
	virtual TypeID GetType(void) const { return TypeID::Actor; }

	// �̗͂̐ݒ�

	inline void SetMaxHitPoint(float maxHitPoint) { max_hit_point_ = maxHitPoint; }
	inline void SetHitPoint(float hitPoint) { hit_point_ = hitPoint; }
	inline float GetHitPoint(void) { return hit_point_; } 

	// �U���͂̐ݒ�

	inline void SetMaxAttack(float maxAttack) { max_attack_ = maxAttack; }
	inline void SetAttack(float attack) { attack_ = attack; }
	inline float GetAttack(void) { return attack_; }

protected:
	// �p�����[�^

	float max_hit_point_;
	float hit_point_;
	float max_attack_;
	float attack_;

	// �G�l�~�[�̃��b�V��
	class FFPMeshRendererComponent*		actor_mesh_;

	// �Փ˔���
	class SphereGizmoRendererComponent* sphere_gizmo_;
	class SphereColliderComponent*		sphere_collider_;
	class BoxGizmoRendererComponent*	box_gizmo_;
	class OBBColliderComponent*			obb_collider_;
};


#endif //ACTOR_H_
/*=============================================================================
/*		End of File
=============================================================================*/