/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Game.h] ゲームの状態やオブジェクトの管理モジュールヘッダ
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ゲームの状態やオブジェクトを管理するためのクラス
=============================================================================*/
#ifndef GAME_H_
#define	GAME_H_

/*--- インクルードファイル ---*/


/*-------------------------------------
/* ゲームクラス
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
		, GameStartScene	// ゲームが始まる時のイベントシーン
		, GameFinishScene	// ボスを倒した後の　イベントシーン
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

	//ゲームの状態の設定
	void SetGameState(GameState gameState) { game_state_ = gameState; }
	GameState GetGameState(void) { return game_state_; }

	// 場面の切り替え
	void SetSceneState(class ISceneState* sceneState);

	// シャットダウンをするか？
	bool IsShutdown(void) { return is_shutdown_; }

public:
	//ゲームオブジェクトの追加と削除
	void AddGameObject(class GameObject* gameObject);
	void RemoveGameObject(class GameObject* gameObject);

	//ゲームオブジェクトのコンポーネントのコンテナを取得
	const std::vector<class GameObject*>& GetGameObjects() const { return game_objects_; }

	class DX9Graphics*		GetGraphics(void) { return dx9_graphics_; }
	class Renderer*			GetRenderer(void) { return renderer_; }

	// リソースの各マネージャ

	class ShaderManager*	GetShaderManager(void) { return shader_manager_; }
	class TextureManager*	GetTextureManager(void) { return texture_manager_; }
	class MeshManager*		GetMeshManager(void) { return mesh_manager_; }
	class LightManager*		GetLightManager(void) { return light_manager_; }
	class EffectManager*	GetEffectManager(void) { return effect_manager_; }
	class SoundManager*		GetSoundManager(void) { return sound_manager_; }
	class ColliderManager*	GetColliderManager(void) { return collider_manager_; }
	class SaveDataManager*	GetSaveDataManager(void) { return save_data_manager_; }

	// サンドボックスの各マネージャ

	class ActorManager*	    GetActorManager(void) { return actor_manager_; }
	class EnemieManager*    GetEnemieManager(void) { return enemie_manager_; }
	class BulletManager*	GetBulletManager(void) { return bullet_manager_; }

private:
	//各ゲームオブジェクトの入力処理
	void InputGameObjects(void);

	//各ゲームオブジェクトの更新処理
	void UpdateGameObjects(float deltaTime);

private:
	//現在のゲームの状態
	GameState game_state_;

	// ゲームを終了するか？
	bool is_shutdown_;

	//各オブジェクトが入力中かどうか？
	bool input_game_objects_;

	//各オブジェクトが更新中かどうか？
	bool updating_game_objects_;

	//ゲームオブジェクト
	std::vector<class GameObject*>  pending_game_objects_;
	std::vector<class GameObject*>  game_objects_;

private:
	// ゲームの場面遷移のポインタ
	static class ISceneState* scene_state_;

private:
	class GameObjectFactory*  game_object_fuctory_;
	class DX9Graphics*		  dx9_graphics_;
	class Renderer*			  renderer_;

	// リソースの管理者

	class ShaderManager*	  shader_manager_;
	class TextureManager*	  texture_manager_;
	class MeshManager*		  mesh_manager_;
	class LightManager*		  light_manager_;
	class EffectManager*	  effect_manager_;
	class SoundManager*		  sound_manager_;
	class ColliderManager*	  collider_manager_;
	class SaveDataManager*	  save_data_manager_;

	// サンドボックスの管理者

	class ActorManager*		  actor_manager_;
	class EnemieManager*	  enemie_manager_;
	class BulletManager*	  bullet_manager_;
};

#endif //GAME_H_
/*=============================================================================
/*		End of File
=============================================================================*/