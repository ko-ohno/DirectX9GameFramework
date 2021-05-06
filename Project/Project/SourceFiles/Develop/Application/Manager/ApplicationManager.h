/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ApplicationManager.h] �A�v���S�̂̏����̊Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�A�v���S�̂̏����̊Ǘ��N���X
=============================================================================*/
#ifndef APPLICATION_MANAGER_H_
#define	APPLICATION_MANAGER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../IManager.h"
#include "../Win32APIWindow.h"

/*-------------------------------------
/* �\����
-------------------------------------*/

/*-------------------------------------
/* �A�v���S�̂̏����̊Ǘ��N���X
-------------------------------------*/
class ApplicationManager : public IManager
{
public:
	ApplicationManager(const WindowStyle& windowStyle);
	~ApplicationManager(void) override;

	bool Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;
	void GenerateOutput(void) override;

	// Application���� override ���Ȃ�
	// class Vector2* GetSelectedAspectRatio(void) override;
	// float GetScreenScaler(void) override;
	// bool IsLoopBreak(void) override;
	// bool IsShutDown(void) override;


private:
	HWND					window_handle_;
	class Win32APIWindow*	app_window_;
	class DX9Graphics*		dx9_graphics_;
	class InputDevice*		input_device_;	
	class ImGuiManager*		imgui_manager_;
	WindowStyle				window_style_;
	float					screen_scaler_;

	//�Q�[���p�̊�
	class Game*				game_;

	//�e�X�g�p
	class SpriteShader*		sprite_shader_;
	class TestCamera*		test_camera_;
};

#endif //APPLICATION_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/