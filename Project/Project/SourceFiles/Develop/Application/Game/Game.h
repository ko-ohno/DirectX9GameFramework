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
/* �\����
-------------------------------------*/

/*-------------------------------------
/* �N���X
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

public:
	//�Q�[���I�u�W�F�N�g�̒ǉ��ƍ폜
	void AddGameObject(class GameObject* gameObject);
	void RemoveGameObject(class GameObject* gameObject);

	//�Q�[���I�u�W�F�N�g�̃R���|�[�l���g�̃R���e�i���擾
	const std::vector<class GameObject*>& GetGameObjects() const { return game_objects_; }

	class DX9Graphics*		GetGraphics(void) { return dx9_graphics_; }
	class Renderer*			GetRenderer(void) { return renderer_; }
	class ShaderManager*	GetShaderManager(void) { return shader_manager_; }
	class TextureManager*	GetTextureManager(void) { return texture_manager_; }
	class MeshManager*		GetMeshManager(void) { return mesh_manager_; }
	class LightManager*		GetLightManager(void) { return light_manager_; }
	class EffectManager*	GetEffectManager(void) { return effect_manager_; }
	class SoundManager*		GetSoundManager(void) { return sound_manager_; }
	class ColliderManager*	GetColliderManager(void) { return collider_manager_; }


private:
	//�e�X�V����
	void UpdateGameObjects(float deltaTime);

private:
	//���݂̃Q�[���̏��
	GameState game_state_;

	//�e�I�u�W�F�N�g���X�V�����ǂ����H
	bool updating_game_objects_;

	//�Q�[���I�u�W�F�N�g
	std::vector<class GameObject*>  pending_game_objects_;
	std::vector<class GameObject*>  game_objects_;

private:
	class GameObjectFactory* game_object_fuctory_;
	class DX9Graphics*		 dx9_graphics_;
	class Renderer*			 renderer_;
	class ShaderManager*	 shader_manager_;
	class TextureManager*	 texture_manager_;
	class MeshManager*		 mesh_manager_;
	class LightManager*		 light_manager_;
	class EffectManager*	 effect_manager_;
	class SoundManager*		 sound_manager_;
	class ColliderManager*	 collider_manager_;
};


#endif //GAME_H_
/*=============================================================================
/*		End of File
=============================================================================*/