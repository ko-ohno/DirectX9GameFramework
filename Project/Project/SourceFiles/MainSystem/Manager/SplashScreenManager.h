/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SplashScreenManager.h] �A�v���S�̂̏����̊Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�S�̂̏����̊Ǘ��N���X
=============================================================================*/
#ifndef SPLASHSCREEN_MANAGER_H_
#define	SPLASHSCREEN_MANAGER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../IManager.h"
#include "../Win32APIWindow.h"

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
	~SplashScreenManager(void);

	bool Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;
	void GenerateOutput(void) override;

private:
	HWND					window_handle_;
	class Win32APIWindow*	splash_window_;
	class DX9Graphics*		dx9_graphics_;
	class ImGuiManager*		imgui_manager_;

};

#endif //SPLASHSCREEN_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/