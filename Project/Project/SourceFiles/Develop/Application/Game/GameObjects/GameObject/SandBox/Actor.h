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
/*  �A�N�^�[�̃X�e�[�g
-------------------------------------*/
enum class ActorState
{
	None = -1
	, Wait				// �ҋ@
	, Enter				// �o��
	, BodyPress			// �{�f�B�v���X
	, Shooting			// �ˌ�
	, LaserCannone		// ���[�U�[�C

	, Max
};

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

	virtual ActorState GetActorState(void) { return actor_state_; }
	virtual void SetActorState(ActorState actorState) { actor_state_ = actorState; }

	// �̗͂̐ݒ�

	void SetMaxHitPoint(float maxHitPoint) { max_hit_point_ = maxHitPoint; }
	void SetHitPoint(float hitPoint) { hit_point_ = hitPoint; }
	float GetHitPoint(void) { return hit_point_; } 
	// �U���͂̐ݒ�

	void SetMaxAttack(float maxAttack) { max_attack_ = maxAttack; }
	void SetAttack(float attack) { attack_ = attack; }
	float GetAttack(void) { return attack_; }


protected:
	// �A�N�^�[�̏�ԃX�e�[�g
	ActorState actor_state_;

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