/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SplashScreenManager.h] �X�v���b�V���X�N���[���S�̂̏����̊Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�X�v���b�V���X�N���[���̑S�̂̏����̊Ǘ��N���X
=============================================================================*/
#ifndef SPLASHSCREEN_MANAGER_H_
#define	SPLASHSCREEN_MANAGER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../IManager.h"
#include "../Win32APIWindow.h"
#include "../../Generic/Math.h"

/*-------------------------------------
/* �\����
-------------------------------------*/

/*-------------------------------------
/* �A�v���S�̂̏����̊Ǘ��N���X
-------------------------------------*/
class SplashScreenManager : public IManager
{
public:
	SplashScreenManager(const WindowStyle& windowStyle);
	~SplashScreenManager(void) override;

	bool Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;
	void GenerateOutput(void) override;

	//�X�v���b�V���X�N���[��������A�v���P�[�V�������ɁA�A�X�y�N�g�䗦��n��
	class Vector2* GetSelectedAspectRatio(void) override;

	// ���b�Z�[�W���[�v�̏�Ԃ��}�l�[�W�������琧��
	bool IsLoopBreak(void) override;
	bool IsShutDown(void) override;

private:
	//�A�X�y�N�g�䗦�̍쐬
	void MakeListAspectRatio(void);

private:
	//�A�X�y�N�g�䗦�̌v�Z
	std::vector<std::string> aspact_ratio_string_array_;
	std::vector<Vector2>	 aspect_ratio_size_array_;
	Vector2					 aspect_ratio_size_;

	//�X�v���b�V���X�N���[���p�̉摜�f�[�^
	LPDIRECT3DTEXTURE9		 texture_;
	Vector2					 texture_size_;

	HWND					 window_handle_;
	class Win32APIWindow*	 splash_window_;
	class DX9Graphics*		 dx9_graphics_;
	class ImGuiManager*		 imgui_manager_;
	bool					 is_loop_break_;
	bool					 is_shutdown_;
};

#endif //SPLASHSCREEN_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/