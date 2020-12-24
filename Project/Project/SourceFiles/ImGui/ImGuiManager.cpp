/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ImGuiManager.cpp] ���W���[��
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../StdAfx.h"
#include "ImGuiManager.h"
#include "../MainSystem/DX9Graphics.h"

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
ImGuiManager::ImGuiManager(void)
{
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
ImGuiManager::~ImGuiManager(void)
{
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
ImGuiManager* ImGuiManager::Create(void)
{
	return NEW ImGuiManager();
}

/*-----------------------------------------------------------------------------
/* ImGui�̋N������
-----------------------------------------------------------------------------*/
void ImGuiManager::StartUp(DX9Graphics* dx9Graphics, const HWND& windowHandle)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX9_Init(*dx9Graphics->GetLPD3DDevice());

	//�r���h�̐ݒ�ɂ����ImGui��.ini�t�@�C���𐶐����Ȃ��悤�ɂ���@
#if defined(_DEBUG) || defined(DEBUG)
	io.IniFilename;				//����
#else
	io.IniFilename = nullptr;	//�񐶐�
#endif // 0

	//ImGui�̐F��I��
	ImGuiManager::SetDefaultColor();
}

/*-----------------------------------------------------------------------------
/* ImGui�̒�~����
-----------------------------------------------------------------------------*/
void ImGuiManager::ShutDown(void)
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

/*-----------------------------------------------------------------------------
/* ImGui�̐F�ʐݒ�Ăяo��
-----------------------------------------------------------------------------*/
void ImGuiManager::SetDefaultColor(ImGuiColorStyle colorStyle)
{
	// �F�̃X�^�C����ݒ�
	switch (colorStyle)
	{
	case ImGuiColorStyle::None:
		assert("�w�肳�ꂽ�J���[�͂���܂���B");
		break;

	case ImGuiColorStyle::Dark:
		ImGui::StyleColorsDark();
		break;

	case ImGuiColorStyle::Classic:
		ImGui::StyleColorsClassic();
		break;

	case ImGuiColorStyle::Light:
		ImGui::StyleColorsLight();
		break;

	case ImGuiColorStyle::MAX:
		assert("�w�肳�ꂽ�J���[�͂���܂���B");
		break;

	default:
		assert("�s���ȏ��������m");
		break;
	}
}

/*-----------------------------------------------------------------------------
/* ImGui�̃t���[���̍X�V�J�n�n���h��
-----------------------------------------------------------------------------*/
void ImGuiManager::UpdateBegin(void)
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

/*-----------------------------------------------------------------------------
/* ImGui�̃t���[���̍X�V�I���n���h��
-----------------------------------------------------------------------------*/
void ImGuiManager::UpdateEnd(void)
{
	ImGui::EndFrame();
}

/*-----------------------------------------------------------------------------
/* ImGui�̃t���[���̍X�V�I���n���h��
-----------------------------------------------------------------------------*/
void ImGuiManager::ImGuiRender(void)
{
	ImGui::Render();//ImGui�̕`��͂��߂�
	//ImGui_ImplDX9_set
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

/*-----------------------------------------------------------------------------
/* ImGui�̃t���[���̍X�V�I���n���h��
-----------------------------------------------------------------------------*/
void ImGuiManager::ShowFramerate(float deltaTime)
{
	ImGuiWindowFlags gui_window_style = (ImGuiWindowFlags_NoTitleBar
										//| ImGuiWindowFlags_NoMove
										| ImGuiWindowFlags_NoResize
										| ImGuiWindowFlags_NoCollapse);
	static bool is_open = true;
	//ImGui::SetNextWindowPos(ImVec2(-5.f, -5.f));
	ImGui::SetNextWindowSize(ImVec2(400.f, 100.f));
	ImGui::Begin("Framerate", &is_open, gui_window_style);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("deltaTime is : %.3f ms", deltaTime);
	ImGui::End();
}


/*-----------------------------------------------------------------------------
/* ImGui�̃E�B���h�E�p�̃e�N�X�`���ǂݍ���
-----------------------------------------------------------------------------*/
bool ImGuiManager::ImGuiLoadTexture(const char* fileName, LPDIRECT3DTEXTURE9* srcTexture, const Vector2* textureSize)
{
	////�e�N�X�`�����̎擾
	//LPDIRECT3DTEXTURE9	lpd3d_texture;
	//D3DXIMAGE_INFO		image_info;
	//Vector2				image_size;

	//HRESULT hr = D3DXCreateTextureFromFile(*DX9Graphics::GetLPD3DDevice(), file_name, &lpd3d_texture);
	//if (FAILED(hr))
	//{
	//	MessageBox(NULL, "�X�v���b�V���X�N���[���p�̃e�N�X�`���\���ǂݍ��߂܂���ł����B", "�x��", (MB_OK | MB_ICONWARNING));
	//	return false;
	//}

	//hr = D3DXGetImageInfoFromFile(file_name, &image_info);
	//if (FAILED(hr))
	//{
	//	MessageBox(NULL, "�X�v���b�V���X�N���[���p�̃e�N�X�`���\�̏�񂪎擾�ł��܂���ł����B", "�x��", (MB_OK | MB_ICONWARNING));
	//	return false;
	//}

	//{//�e�N�X�`�����̕ۑ�
	//	image_size.x_ = (float)image_info.Width;
	//	image_size.y_ = (float)image_info.Height;

	//	textureSize = image_size;
	//	*srcTexture = lpd3d_texture;
	//}

	return true;
}


/*=============================================================================
/*		End of File
=============================================================================*/