/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[WeakEnemy.cpp] �ア�G�̃Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�ア�G�̃Q�[���I�u�W�F�N�g
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../../../../../StdAfx.h"
#include "WeakEnemy.h"
#include "../../Bullet/NormalBullet.h"
#include "../../../../../SandBoxManager/BulletManager.h"
#include "../../../../../CheckCollision.h"

// �ړ��R���|�[�l���g
#include "../../../../Component/MoveComponent/EnemyMoveComponent/WeakEnemyMoveComponent.h"

// �{�XAI�R���|�[�l���g
#include "../../../../Component/AIComponent/EnemyAIComponent/WeakEnemyAIComponent.h"

// ���b�V���R���|�[�l���g
#include "../../../../Component/RendererComponent/FFPMeshRendererComponent.h"

// ���b�V���R���|�[�l���g
#include "../../../../Component/RendererComponent/EffectRendererComponent.h"

// ���̏Փ˔���
#include "../../../../Component/RendererComponent/GizmoRendererComponent/SphereGizmoRendererComponent.h"
#include "../../../../Component/ColliderComponent/SphereColliderComponent.h"

// �{�b�N�X�̏Փ˔���
#include "../../../../Component/RendererComponent/GizmoRendererComponent/BoxGizmoRendererComponent.h"
#include "../../../../Component/ColliderComponent/OBBColliderComponent.h"

// ���̓`�F�b�N
#include "../../../../../Input/InputCheck.h"

// ImGui
#include "../../../../../../ImGui/ImGuiManager.h"


/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
WeakEnemy::WeakEnemy(Game* game)
	: Enemy(game)
{
	this->Init();
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
WeakEnemy::~WeakEnemy(void)
{
	this->Uninit();
}

/*-----------------------------------------------------------------------------
/* ����������
-----------------------------------------------------------------------------*/
bool WeakEnemy::Init(void)
{
	// �������W��������
	{
		this->transform_component_->SetTranslationY(-100.f);

		// �e�X�g�p�������W
		//this->transform_component_->SetTranslationX(-3.f);
		//this->transform_component_->SetTranslationZ(8.f);
	}

	// �ア�G��AI�𐶐� 
	enemy_ai_ = NEW WeakEnemyAIComponent(this);

	// �ア�G�̈ړ��R���|�[�l���g�𐶐�
	enemy_move_ = NEW WeakEnemyMoveComponent(this);

	// �������W��������
	{
		this->transform_component_->SetTranslationY(-100.f);
		this->enemy_move_->SetStartPositionY(-100.f);

		// �e�X�g�p�������W
		//this->transform_component_->SetTranslationX(-3.f);
		//this->transform_component_->SetTranslationZ(8.f);
	}

	// �ア�G�̃��b�V������
	{
		actor_mesh_ = NEW FFPMeshRendererComponent(this);
		actor_mesh_->SetMesh(XFileMeshType::EnemyWeak);
		actor_mesh_->SetScale(0.5f);
		actor_mesh_->SetTranslationY(-0.5f);
		actor_mesh_->SetEnableLighting(true);			// ���C�e�B���O��L���ɂ���
	}

	// �����G�t�F�N�g�̐���
	{
		explosion_effect_ = NEW EffectRendererComponent(this);
		explosion_effect_->SetEffect(EffectType::ExplosionActor);
	}

	// �Q�[���}�l�[�W���ւ̃|�C���^�̎擾
	{
		game_manager_ = this->FindGameObject(GameObject::TypeID::GameManager);
		if (game_manager_ == nullptr)
		{
			assert(!"WeakEnemy::Init()�F�Q�[���}�l�[�W���ւ̃|�C���^���擾�ł��܂���ł���");
		}
	}

	// �ア�G�̏�Ԃ�������
	{
		auto init_WeakEnemy_state = EnemyState::Idle;
		//init_WeakEnemy_state = EnemyState::MoveLoopLeftRight;

		// �G�̏�Ԃ�������
		enemy_ai_->SetEnemyState(init_WeakEnemy_state);
		enemy_move_->SetEnemyState(init_WeakEnemy_state);
	}

	// �Փ˔���֌W
	{
		// �Փ˔���̍����@�I�t�Z�b�g���W
		float collider_height_pos = 0.f;

		// ��
		{
			// ���̔��a
			const float sphere_radius_size = 0.5f;

			// �Փ˔���
			sphere_collider_ = NEW SphereColliderComponent(this);
			sphere_collider_->SetTranslationY(collider_height_pos);
			sphere_collider_->SetRadius(sphere_radius_size);

			// �M�Y��
			sphere_gizmo_ = NEW SphereGizmoRendererComponent(this);
			sphere_gizmo_->SetTranslationY(collider_height_pos);
			sphere_gizmo_->SetScale(sphere_radius_size);
		}

		// �Փ˔���̍����@�I�t�Z�b�g���W
		collider_height_pos = 0.f;

		// ��
		{
			// ���̍���
			const float box_height_size = 1.f;

			// ���̐������̑傫��
			const float box_scale = 1.f;

			// �Փ˔���
			obb_collider_ = NEW OBBColliderComponent(this);
			obb_collider_->SetTranslationY(collider_height_pos);
			obb_collider_->SetDirLength(box_scale, AxisType::X);
			obb_collider_->SetDirLength(box_height_size, AxisType::Y);
			obb_collider_->SetDirLength(box_scale, AxisType::Z);

			// �M�Y��
			obb_collider_gizmo_ = NEW BoxGizmoRendererComponent(this);
			obb_collider_gizmo_->SetVertexColor(0, 255, 255, 128);
			obb_collider_gizmo_->SetTranslationY(collider_height_pos);
			obb_collider_gizmo_->SetScaleX(box_scale);
			obb_collider_gizmo_->SetScaleY(box_height_size);
			obb_collider_gizmo_->SetScaleZ(box_scale);
		}
	}

	return true;
}

/*-----------------------------------------------------------------------------
/* �I��������
-----------------------------------------------------------------------------*/
void WeakEnemy::Uninit(void)
{
}

/*-----------------------------------------------------------------------------
/* �Q�[���I�u�W�F�N�g�̓��͏���
-----------------------------------------------------------------------------*/
void WeakEnemy::InputGameObject(void)
{
}

/*-----------------------------------------------------------------------------
/* override�Ŏ������g���X�V
-----------------------------------------------------------------------------*/
void WeakEnemy::UpdateGameObject(float deltaTime)
{
	// AI�R���|�[�l���g�Ɏ��g��HP��ʒm����
	{
		enemy_ai_->SetHitPoint(this->GetHitPoint());
	}

	/*
	*			��		EnemyState		��
	*
	����������������������������������������������������
	���@�@Move�@�@��  �� WeakEnemy  ���@���@�@AI�@�@�@��
	����������������������������������������������������
	*
	*			��		MotionState		��
	*/

	// AI�R���|�[�l���g����GAI�̍s���X�e�[�g���擾
	auto ai_state = enemy_ai_->GetEnemyState();
	{
		// �ړ��R���|�[�l���g�ցA�GAI�̍s���X�e�[�g��ʒm
		enemy_move_->SetEnemyState(ai_state);
	}

	// �ړ��R���|�[�l���g����ړ����[�V������Ԃ��擾
	auto move_motion_state = enemy_move_->GetMotionState();
	{
		// AI�R���|�[�l���g�ֈړ����[�V������Ԃ�ʒm
		enemy_ai_->SetMotionState(move_motion_state);
	}

	if (true)
	{
		//
		// �{�Ԋ��X�y�[�X:�l�̓`�B
		//

		// �n�_���W�̐ݒ�
		enemy_move_->SetStartPosition(position_start_);

		// �����x�N�g���̐ݒ�
		enemy_move_->SetRotationMoveDirection(angle_yaw_, angle_pitch_, angle_roll_);

		// �ړ��x�N�g���̒�����ݒ�
		enemy_move_->SetMoveVectorLength(move_vector_length_);

		// �ړ��A�N�V�����̐[����ݒ�
		enemy_move_->SetMoveActionMagnitude(move_action_magnitude_);

		// �ő�̎��s����
		enemy_move_->SetMaxExecuteTime(max_execute_time_);
	}
	else
	{
		//
		// �����X�y�[�X
		//

		switch (ai_state)
		{
		case EnemyState::MoveStraight:
			this->TestMoveStraight();
			break;

		case EnemyState::MoveStraightWaitOneTime:
			this->TestMoveStraightWaitOneTime();
			break;

		case EnemyState::MoveStraightWaitUpDown:
			this->TestMoveStraightWaitUpDown();
			break;

		case EnemyState::MoveRoundVertical:
			this->TestMoveRoundVertical();
			break;

		case EnemyState::MoveRoundHorizontal:
			this->TestMoveRoundHorizontal();
			break;

		case EnemyState::MoveLoopUpDown:
			this->TestMoveLoopUpDown();
			break;

		case EnemyState::MoveLoopLeftRight:
			this->TestMoveLoopLeftRight();
			break;

		case EnemyState::MoveShowOneTime:
			this->TestMoveShowOneTime();
			break;

		case EnemyState::Destroy:
			break;

		default:
			break;
		}
	}

	// WeakEnemy�͕K�v�Ȃ�
	//�@���g��AI�̃X�e�[�g����U���͂��X�V����
	//switch (ai_state)
	//{
	//case EnemyState::Idle:
	//	attack_ = 0.f;
	//	break;

	//case EnemyState::Shooting:
	//	attack_ = 0.f;
	//	break;

	//case EnemyState::Destroy:
	//	attack_ = 0.f;
	//	break;

	//default:
	//	attack_ = 10.f;
	//	break;
	//}

	// ���g��j�󂳂ꂽ��
	if (this->GetGameObjectState() == State::Destroy)
	{
		// �j���Ԃł̏��������s��
		if (is_destroy_ == false)
		{
			// �����G�t�F�N�g���Đ�
			explosion_effect_->Play();

			// �X�R�A�։��Z����
			auto parameter_components = game_manager_->GetParameterComponents();
			for (auto parameter_component : parameter_components)
			{
				// �X�R�A�ւ̒l�R���|�[�l���g�ւ̃|�C���^���擾
				auto parameter_component_type = parameter_component->GetParameterType();
				if (parameter_component_type == ParameterType::Score)
				{
					parameter_component->AddInt(10);
					break;
				}
			}

			actor_mesh_->IsSetDrawable(false);
			sphere_gizmo_->IsSetDrawable(false);

			// �j���Ԃł̏��������s��
			is_destroy_ = true;
		}
		
		// �j��܂ł̎���
		destroy_interval_time_ += deltaTime;

		// ���g��j������
		const float MAX_DESTROY_INTERVAL_TIME = 1.f;
		if (destroy_interval_time_ >= MAX_DESTROY_INTERVAL_TIME)
		{
			// �Q�[���I�u�W�F�N�g��j��
			this->SetGameObjectState(State::Dead);
		}
		return;
	}

	// �Փ˔���
	{	
		auto bullets = game_->GetBulletManager()->GetBulletGameObjectList();
		for (auto bullet : bullets)
		{
			// Bullet�̏��L�҂�Player���𒲂ׂ�
			auto bullet_game_object = bullet->GetParentGameObject();
			if (bullet_game_object->GetType() != GameObject::TypeID::Player)
			{
				continue;
			}

			// �v���C���[�̃o���b�g�̏Փ˔�����擾
			auto components = bullet->GetComponents();
			for (auto component : components)
			{
				auto component_type = component->GetComponentType();
				if (component_type == Component::TypeID::SphereColliderComponent)
				{
					if (CheckCollision::SphereVSSpghre(this->GetSphereCollider(), bullet->GetSphereCollider()))
					{
						// �G�l�~�[���j�󂳂��
						this->SetGameObjectState(State::Destroy);

						// �Փ˂����o���b�g��j������
						bullet->SetGameObjectState(State::Dead);
						break;
					}
				}
			}
		}
	}
}

/*-----------------------------------------------------------------------------
/* �����ړ�����
-----------------------------------------------------------------------------*/
void WeakEnemy::TestMoveStraight() 
{		
	// �n�_���W�̐ݒ�
	enemy_move_->SetStartPositionX(30.f);
	enemy_move_->SetStartPositionZ(10.f);

	// �����x�N�g���̐ݒ�
	enemy_move_->SetRotationMoveDirectionYaw(-90);

	// �ړ��x�N�g���̒�����ݒ�
	enemy_move_->SetMoveVectorLength(60.f);

	enemy_move_->SetMaxExecuteTime(6.f);
}

/*-----------------------------------------------------------------------------
/* �����ړ����Ĉ�x�҂�
-----------------------------------------------------------------------------*/
void WeakEnemy::TestMoveStraightWaitOneTime()
{
	// �n�_���W�̐ݒ�
	enemy_move_->SetStartPositionX(30.f);
	enemy_move_->SetStartPositionZ(10.f);

	// �����x�N�g���̐ݒ�
	enemy_move_->SetRotationMoveDirectionYaw(-90);

	// �ړ��x�N�g���̒�����ݒ�
	enemy_move_->SetMoveVectorLength(60.f);

	enemy_move_->SetMoveActionMagnitude(move_action_magnitude_);

	enemy_move_->SetMaxExecuteTime(6.f);
}

/*-----------------------------------------------------------------------------
/* S���J�[�u�ړ��s��
-----------------------------------------------------------------------------*/
void WeakEnemy::TestMoveStraightWaitUpDown()
{
	// �n�_���W�̐ݒ�
	enemy_move_->SetStartPositionX(15.f);
	enemy_move_->SetStartPositionZ(10.f);

	// �����x�N�g���̐ݒ�
	enemy_move_->SetRotationMoveDirectionYaw(-90);

	// �ړ��x�N�g���̒�����ݒ�
	enemy_move_->SetMoveVectorLength(30.f);

	enemy_move_->SetMoveActionMagnitude(10.f);

	enemy_move_->SetMaxExecuteTime(6.f);
}

/*-----------------------------------------------------------------------------
/* �����ɔ��~��`���s��
-----------------------------------------------------------------------------*/
void WeakEnemy::TestMoveRoundVertical()
{
	// �n�_���W�̐ݒ�
	//enemy_move_->SetStartPositionX(10.f);
	enemy_move_->SetStartPositionY( 5.f);
	enemy_move_->SetStartPositionZ(10.f);

	// �����x�N�g���̐ݒ�
	enemy_move_->SetRotationMoveDirectionPitch(90);

	// �ړ��x�N�g���̒�����ݒ�
	enemy_move_->SetMoveVectorLength(10.f);

	enemy_move_->SetMoveActionMagnitude(10.f);

	enemy_move_->SetMaxExecuteTime(2.f);
}

/*-----------------------------------------------------------------------------
/* �����ɔ��~��`���s��
-----------------------------------------------------------------------------*/
void WeakEnemy::TestMoveRoundHorizontal()
{
	// �n�_���W�̐ݒ�
	enemy_move_->SetStartPositionX(5.f);
	//enemy_move_->SetStartPositionY(5.f);
	enemy_move_->SetStartPositionZ(10.f);

	// �����x�N�g���̐ݒ�
	enemy_move_->SetRotationMoveDirectionYaw(90);
	//enemy_move_->SetRotationMoveDirectionPitch(90);

	// �ړ��x�N�g���̒�����ݒ�
	enemy_move_->SetMoveVectorLength(-10.f);

	enemy_move_->SetMoveActionMagnitude(5.f);

	enemy_move_->SetMaxExecuteTime(6.f);
}

/*-----------------------------------------------------------------------------
/* �㉺���[�v�ړ��s��
-----------------------------------------------------------------------------*/
void WeakEnemy::TestMoveLoopUpDown()
{
	// �n�_���W�̐ݒ�
	enemy_move_->SetStartPositionX(-30.f);
	enemy_move_->SetStartPositionZ(10.f);

	// �����x�N�g���̐ݒ�
	enemy_move_->SetRotationMoveDirectionYaw(90);
	//enemy_move_->SetRotationMoveDirectionPitch(90);

	// �ړ��x�N�g���̒�����ݒ�
	enemy_move_->SetMoveVectorLength(60.f);

	enemy_move_->SetMoveActionMagnitude(5.f);

	enemy_move_->SetMaxExecuteTime(8.f);
}

/*-----------------------------------------------------------------------------
/* ���E���[�v�ړ��s��
-----------------------------------------------------------------------------*/
void WeakEnemy::TestMoveLoopLeftRight()
{
	// �n�_���W�̐ݒ�
	enemy_move_->SetStartPositionY( 5.f);
	enemy_move_->SetStartPositionZ(10.f);

	// �����x�N�g���̐ݒ�
	//enemy_move_->SetRotationMoveDirectionYaw(90);
	enemy_move_->SetRotationMoveDirectionPitch(90);

	// �ړ��x�N�g���̒�����ݒ�
	enemy_move_->SetMoveVectorLength(10.f);

	enemy_move_->SetMoveActionMagnitude(10.f);

	enemy_move_->SetMaxExecuteTime(6.f);
}

/*-----------------------------------------------------------------------------
/* ��ʒ[�����o���s��
-----------------------------------------------------------------------------*/
void WeakEnemy::TestMoveShowOneTime()
{
	// �n�_���W�̐ݒ�
	enemy_move_->SetStartPositionX(30.f);
	enemy_move_->SetStartPositionZ(10.f);

	// �����x�N�g���̐ݒ�
	enemy_move_->SetRotationMoveDirectionYaw(-90);

	// �ړ��x�N�g���̒�����ݒ�
	enemy_move_->SetMoveVectorLength(60.f);

	enemy_move_->SetMoveActionMagnitude(move_action_magnitude_);

	enemy_move_->SetMaxExecuteTime(6.f);
}

/*=============================================================================
/*		End of File
=============================================================================*/