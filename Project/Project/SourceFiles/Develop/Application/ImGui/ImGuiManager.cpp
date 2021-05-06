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
#include "../../../External/ImGui/include/imgui_internal.h"
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
void ImGui::ShowFramerate(float deltaTime)
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
bool ImGui::LoadTexture(const char* fileName, LPDIRECT3DTEXTURE9* srcTexture, Vector2& textureSize)
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

/*-----------------------------------------------------------------------------
/* �ǂݍ��ݗp�̃V�[�N�o�[��\��
-----------------------------------------------------------------------------*/
bool ImGui::BufferingBar(const char* label, float value, const ImVec2& size_arg, const ImU32& bg_col, const ImU32& fg_col)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);

	ImVec2 pos = window->DC.CursorPos;
	ImVec2 size = size_arg;
	size.x -= style.FramePadding.x * 2;

	const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
	ItemSize(bb, style.FramePadding.y);
	if (!ItemAdd(bb, id))
		return false;

	// Render
	const float circleStart = size.x * 0.7f;
	const float circleEnd = size.x;
	const float circleWidth = circleEnd - circleStart;

	window->DrawList->AddRectFilled(bb.Min, ImVec2(pos.x + circleStart, bb.Max.y), bg_col);
	window->DrawList->AddRectFilled(bb.Min, ImVec2(pos.x + circleStart * value, bb.Max.y), fg_col);

	const float t = static_cast<const float>(g.Time);
	const float r = size.y / 2;
	const float speed = 1.5f;

	const float a = speed * 0;
	const float b = speed * 0.333f;
	const float c = speed * 0.666f;

	const float o1 = (circleWidth + r) * (t + a - speed * (int)((t + a) / speed)) / speed;
	const float o2 = (circleWidth + r) * (t + b - speed * (int)((t + b) / speed)) / speed;
	const float o3 = (circleWidth + r) * (t + c - speed * (int)((t + c) / speed)) / speed;

	window->DrawList->AddCircleFilled(ImVec2(pos.x + (circleEnd - o1), bb.Min.y + r), r, bg_col);
	window->DrawList->AddCircleFilled(ImVec2(pos.x + (circleEnd - o2), bb.Min.y + r), r, bg_col);
	window->DrawList->AddCircleFilled(ImVec2(pos.x + (circleEnd - o3), bb.Min.y + r), r, bg_col);
	return true;
}

/*-----------------------------------------------------------------------------
/* �ǂݍ��ݗp�̉�]�V�[�N��\��
-----------------------------------------------------------------------------*/
bool ImGui::Spinner(const char* label, float radius, int thickness, const ImU32& color)
{
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);

	ImVec2 pos = window->DC.CursorPos;
	ImVec2 size((radius) * 2, (radius + style.FramePadding.y) * 2);

	const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
	ItemSize(bb, style.FramePadding.y);
	if (!ItemAdd(bb, id))
		return false;

	// Render
	window->DrawList->PathClear();

	int num_segments = 30;
	int start = static_cast<int>(abs(ImSin(static_cast<float>(g.Time * 1.8f)) * (num_segments - 5)));

	const float a_min = IM_PI * 2.0f * ((float)start) / (float)num_segments;
	const float a_max = IM_PI * 2.0f * ((float)num_segments - 3) / (float)num_segments;

	const ImVec2 centre = ImVec2(pos.x + radius, pos.y + radius + style.FramePadding.y);

	for (int i = 0; i < num_segments; i++) {
		const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
		window->DrawList->PathLineTo(ImVec2(centre.x + ImCos(static_cast<float>(a + g.Time * 8)) * radius,
											centre.y + ImSin(static_cast<float>(a + g.Time * 8)) * radius));
	}
	
	window->DrawList->PathStroke(color, false, static_cast<float>(thickness));
	return true;
}

/*=============================================================================
/*		End of File
=============================================================================*/