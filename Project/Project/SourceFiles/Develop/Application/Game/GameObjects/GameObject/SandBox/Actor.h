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

	class SphereColliderComponent* GetSphereCollider(void) { return sphere_collider_; }
	class OBBColliderComponent* GetOBBCollider(void) { return obb_collider_; }

protected:
	// �p�����[�^

	float max_hit_point_;
	float hit_point_
		, hit_point_old_;
	float max_attack_;
	float attack_;

	// �j�󂷂邩
	bool  is_destroy_;

	// �j���܂ł̎���
	float destroy_interval_time_;

	// �Q�[���}�l�[�W���ւ̃|�C���^
	class GameObject*					game_manager_;

	// �G�l�~�[�̃��b�V��
	class FFPMeshRendererComponent*		actor_mesh_;

	// �����̃G�t�F�N�g
	class EffectRendererComponent*		explosion_effect_;

	// �Փ˔���
	class SphereColliderComponent*		sphere_collider_;
	class SphereGizmoRendererComponent* sphere_gizmo_;
	class OBBColliderComponent*			obb_collider_;
	class BoxGizmoRendererComponent*	obb_collider_gizmo_;
};

#endif //ACTOR_H_
/*=============================================================================
/*		End of File
=============================================================================*/