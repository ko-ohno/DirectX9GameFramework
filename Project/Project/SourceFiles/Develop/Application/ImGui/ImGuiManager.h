/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ImGuiManager.h] ImGui�̊Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FImGui�̊Ǘ��N���X
=============================================================================*/
#ifndef IMGUI_MANAGER_H_
#define	IMGUI_MANAGER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../StdAfx.h"

/*--- ImGui�̃��C�u�������C���N���[�h ---*/
#include "../../../External/ImGui/include/imgui.h"
#include "../../../External/ImGui/include/imgui_impl_dx9.h"
#include "../../../External/ImGui/include/imgui_impl_win32.h"


/*-------------------------------------
/* ImGui�̃E�B���h�E�J���[�X�^�C��
-------------------------------------*/
enum class ImGuiColorStyle
{
	None = -1
	, Dark
	, Classic
	, Light
	, MAX
};

/*-------------------------------------
/* ImGui�Ǘ��N���X
-------------------------------------*/
class ImGuiManager
{
private:
	ImGuiManager(void);

public:
	~ImGuiManager(void);

	static ImGuiManager* Create(void);

	//ImGUI�̊Ǘ�
	bool StartUp(class DX9Graphics* dx9Graphics, const HWND& windowHandle);	//ImGui�̋N��
	void ShutDown(void);													//ImGui�̒�~								

	//�f�t�H���g�F���w��
	void SetDefaultColor(ImGuiColorStyle colorStyle = ImGuiColorStyle::Dark);	

	//ImGui���X�V�Ǘ�
	void UpdateBegin(void);		//GUI�̍X�V�J�n(�X�V���߂̈�ԍŏ��ɌĂяo��)
	void UpdateEnd(void);		//GUI�̍X�V�I��(�X�V���߂̈�ԍŌ�ɌĂяo��)

	//ImGui�̏o�͊Ǘ�
	void ImGuiRender(void);		//�`��J�n����(�`�施�߂̈�ԍŌ�ɌĂяo��)

	//�t���[�����[�g�̕\��
	void ShowFramerate(float deltaTime);

	//ImGui�p�̃e�N�X�`���ǂݍ��݊֐�
	bool ImGuiLoadTexture(const char* fileName
						 , LPDIRECT3DTEXTURE9* srcTexture
						 , class Vector2& textureSize);

private:
};



#endif //IMGUI_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/