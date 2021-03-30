/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ImGuiManager.cpp] ImGui�Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FImGui�Ǘ��N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../StdAfx.h"
#include "ImGuiManager.h"
#include "../DX9Graphics.h"
#include "../Math.h"
#include "../../DebugCode/DebugFunction.h"

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
bool ImGuiManager::StartUp(DX9Graphics* dx9Graphics, const HWND& windowHandle)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	//ImGui�̎��s����WindowsAPI�ł��邱�Ƃ̏�����
	const bool imgui_environment_init = ImGui_ImplWin32_Init(windowHandle);
	if (imgui_environment_init == false)
	{
		std::string msg_str = OUTPUT_FORMAT_STRING("ImGui�̎��s���̏��������ł��܂���ł����I");
		DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
		return false;
	}
	
	//ImGui�̃����_���[��DirectX9�̃O���t�B�b�N�X�f�o�C�X��n���ď�����
	const bool imgui_renderer_init = ImGui_ImplDX9_Init(*dx9Graphics->GetLPD3DDevice());
	if (imgui_renderer_init == false)
	{
		std::string msg_str = OUTPUT_FORMAT_STRING("ImGui�̃����_���[�̏��������ł��܂���ł����I");
		DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
		return false;
	}

	//�r���h�̐ݒ�ɂ����ImGui��.ini�t�@�C���𐶐����Ȃ��悤�ɂ���@
#if defined(_DEBUG) || defined(DEBUG)
	io.IniFilename;				//����
#else
	io.IniFilename = nullptr;	//�񐶐�
#endif // RELEASE

	//ImGui�̐F��I��
	ImGuiManager::SetDefaultColor();

	return true;
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
	case ImGuiColorStyle::Dark:
		ImGui::StyleColorsDark();
		break;

	case ImGuiColorStyle::Classic:
		ImGui::StyleColorsClassic();
		break;

	case ImGuiColorStyle::Light:
		ImGui::StyleColorsLight();
		break;

	default:
		std::string msg_str = OUTPUT_FORMAT_STRING("ImGui�͎w�肳�ꂽ�J���[�X�^�C��������܂���I");
		DebugFunction::PrintfToWarningMessageBox(msg_str.c_str());
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
	ImGuiWindowFlags gui_window_style = (ImGuiWindowFlags_NoMove);
	static bool is_open = false;
	ImGui::SetNextWindowPos(ImVec2(-5.f, -5.f));
	ImGui::SetNextWindowSize(ImVec2(400.f, 100.f));
	ImGui::Begin("DebugWindow", &is_open, gui_window_style);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("deltaTime is : %.3f ms", deltaTime);
	ImGui::End();
}


/*-----------------------------------------------------------------------------
/* ImGui�̃E�B���h�E�p�̃e�N�X�`���ǂݍ���
-----------------------------------------------------------------------------*/
bool ImGuiManager::ImGuiLoadTexture(const char* fileName, LPDIRECT3DTEXTURE9* srcTexture, Vector2& textureSize)
{
	//�e�N�X�`�����̎擾
	LPDIRECT3DTEXTURE9	lpd3d_texture;
	D3DXIMAGE_INFO		image_info;
	Vector2				image_size;

	HRESULT hr = D3DXCreateTextureFromFile(*DX9Graphics::GetLPD3DDevice(), fileName, &lpd3d_texture);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�X�v���b�V���X�N���[���p�̃e�N�X�`���\���ǂݍ��߂܂���ł����B", "�x��", (MB_OK | MB_ICONWARNING));
		return false;
	}

	hr = D3DXGetImageInfoFromFile(fileName, &image_info);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�X�v���b�V���X�N���[���p�̃e�N�X�`���\�̏�񂪎擾�ł��܂���ł����B", "�x��", (MB_OK | MB_ICONWARNING));
		return false;
	}

	//�e�N�X�`�����̕ۑ�
	{
		image_size.x_ = (float)image_info.Width;
		image_size.y_ = (float)image_info.Height;

		textureSize = image_size;
		*srcTexture = lpd3d_texture;
	}
	return true;
}


/*=============================================================================
/*		End of File
=============================================================================*/