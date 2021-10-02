/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Game.h] �Q�[���̏�Ԃ�I�u�W�F�N�g�̊Ǘ����W���[���w�b�_
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Q�[���̏�Ԃ�I�u�W�F�N�g���Ǘ����邽�߂̃N���X
=============================================================================*/
#ifndef GAME_H_
#define	GAME_H_

/*--- �C���N���[�h�t�@�C�� ---*/


/*-------------------------------------
/* �Q�[���N���X
-------------------------------------*/
class Game
{
public:
	enum class GameState
	{
		None = -1
		, Title
		, Gameplay
		, Result
		, Paused
		, GameStartScene	// �Q�[�����n�܂鎞�̃C�x���g�V�[��
		, GameFinishScene	// �{�X��|������́@�C�x���g�V�[��
		, GameClear
		, GameOver
		, Loading
		, Quit

		, MAX
	};

public:
	Game(void);
	~Game(void);

	static Game* Create(void);

	bool StartUp(class DX9Graphics* dx9Graphisc);
	void ShutDown(void);

	void Input(void);
	void Update(float deltaTime);
	void GenerateOutput(void);

	//�Q�[���̏�Ԃ̐ݒ�
	void SetGameState(GameState gameState) { game_state_ = gameState; }
	GameState GetGameState(void) { return game_state_; }

	// ��ʂ̐؂�ւ�
	void SetSceneState(class ISceneState* sceneState);

	// �V���b�g�_�E�������邩�H
	bool IsShutdown(void) { return is_shutdown_; }

public:
	//�Q�[���I�u�W�F�N�g�̒ǉ��ƍ폜
	void AddGameObject(class GameObject* gameObject);
	void RemoveGameObject(class GameObject* gameObject);

	//�Q�[���I�u�W�F�N�g�̃R���|�[�l���g�̃R���e�i���擾
	const std::vector<class GameObject*>& GetGameObjects() const { return game_objects_; }

	class DX9Graphics*		GetGraphics(void) { return dx9_graphics_; }
	class Renderer*			GetRenderer(void) { return renderer_; }

	// ���\�[�X�̊e�}�l�[�W��

	class ShaderManager*	GetShaderManager(void) { return shader_manager_; }
	class TextureManager*	GetTextureManager(void) { return texture_manager_; }
	class MeshManager*		GetMeshManager(void) { return mesh_manager_; }
	class LightManager*		GetLightManager(void) { return light_manager_; }
	class EffectManager*	GetEffectManager(void) { return effect_manager_; }
	class SoundManager*		GetSoundManager(void) { return sound_manager_; }
	class ColliderManager*	GetColliderManager(void) { return collider_manager_; }
	class SaveDataManager*	GetSaveDataManager(void) { return save_data_manager_; }

	// �T���h�{�b�N�X�̊e�}�l�[�W��

	class ActorManager*	    GetActorManager(void) { return actor_manager_; }
	class EnemieManager*    GetEnemieManager(void) { return enemie_manager_; }
	class BulletManager*	GetBulletManager(void) { return bullet_manager_; }

private:
	//�e�Q�[���I�u�W�F�N�g�̓��͏���
	void InputGameObjects(void);

	//�e�Q�[���I�u�W�F�N�g�̍X�V����
	void UpdateGameObjects(float deltaTime);

private:
	//���݂̃Q�[���̏��
	GameState game_state_;

	// �Q�[�����I�����邩�H
	bool is_shutdown_;

	//�e�I�u�W�F�N�g�����͒����ǂ����H
	bool input_game_objects_;

	//�e�I�u�W�F�N�g���X�V�����ǂ����H
	bool updating_game_objects_;

	//�Q�[���I�u�W�F�N�g
	std::vector<class GameObject*>  pending_game_objects_;
	std::vector<class GameObject*>  game_objects_;

private:
	// �Q�[���̏�ʑJ�ڂ̃|�C���^
	static class ISceneState* scene_state_;

private:
	class GameObjectFactory*  game_object_fuctory_;
	class DX9Graphics*		  dx9_graphics_;
	class Renderer*			  renderer_;

	// ���\�[�X�̊Ǘ���

	class ShaderManager*	  shader_manager_;
	class TextureManager*	  texture_manager_;
	class MeshManager*		  mesh_manager_;
	class LightManager*		  light_manager_;
	class EffectManager*	  effect_manager_;
	class SoundManager*		  sound_manager_;
	class ColliderManager*	  collider_manager_;
	class SaveDataManager*	  save_data_manager_;

	// �T���h�{�b�N�X�̊Ǘ���

	class ActorManager*		  actor_manager_;
	class EnemieManager*	  enemie_manager_;
	class BulletManager*	  bullet_manager_;
};

#endif //GAME_H_
/*=============================================================================
/*		End of File
=============================================================================*/