/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Renderer.h] �����_���[�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�����_���[�N���X
=============================================================================*/
#ifndef RENDERER_H_
#define	RENDERER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../StdAfx.h"
#include "../Math.h"
#include "ResourceManager/EffectManager.h"

/*-------------------------------------
/* �����_���[�N���X
-------------------------------------*/
class Renderer
{
public:
	Renderer(class Game* game);
	~Renderer(void);

	static Renderer* Create(class Game* game);

	bool StartUp(void);
	void ShutDown(void);

	void Update(float deltaTime);
	void Draw(void);

private:
	void DrawUpRendererComponents(class Camera* camera, int nowDrawLayerOrder);

public:
	//
	// �����_���[�R���|�[�l���g�̃|�C���^�̒ǉ��ƍ폜
	//

	void AddRendererComponentAddress(class RendererComponent* rendererComponent);
	void RemoveRendererComponentAddress(class RendererComponent* rendererComponent);

	//
	// �����_���[�R���|�[�l���g�̃|�C���^�̒ǉ��ƍ폜
	//

	void AddCameraGameObjectAddress(class Camera* cameraGameObject);
	void RemoveCameraGameObjectAddress(class Camera* cameraGameObject);


	//�����_���[�R���|�[�l���g�̃\�[�g
	void SortByRendererComponent(void);

	class Game* GetGame(void) { return game_; }

private:
	//�����_���[�̏��L��
	class Game* game_;	

	//�V�F�[�_�̊Ǘ���
	class ShaderManager* shader_manager_;

	//�G�t�F�N�g�̊Ǘ���
	class EffectManager* effect_manager_;

	//Effekseer�̃G�t�F�N�g�`��p�����_���[
	class EffekseerRendererDX9::Renderer* effekseer_renderer_;

	//��ʂ̍����A���A��ʔ{��
	int	  screen_width_;
	int	  screen_height_;
	float screen_scaler_;

	//�J�����̃Q�[���I�u�W�F�N�g�̉ғ��R���e�i
	std::vector<class Camera*> camera_game_objects_;

	//�����_���[�R���|�[�l���g�̉ғ��R���e�i
	std::vector<class RendererComponent*> renderer_components_;

	//�J�������ݍ��W���A�P�t���[���O�ƈႤ�ꍇ�A�\�[�g������
	Vector3 now_camera_pos_; 
	Vector3 old_camera_pos_; 	
};	

#endif //RENDERER_H_
/*=============================================================================
/*		End of File
=============================================================================*/