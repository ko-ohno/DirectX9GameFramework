#include "../../../StdAfx.h"
#include "MeshManager.h"
#include "../Game.h"
#include "../../DX9Graphics.h"

MeshManager::MeshManager(Game* game)
	: game_(game)
{
}

MeshManager::~MeshManager(void)
{
}

MeshManager* MeshManager::Create(Game* game)
{
	return nullptr;
}

bool MeshManager::StartUp(void)
{
	auto lpd3d_device = *game_->GetGraphics()->GetLPD3DDevice();

	//D3DXCreatePolygon(lpd3d_device, 1.f, 4, pmesh, nullptr);
	//D3DXCreateBox();
	//D3DXCreateCylinder();
	//D3DXCreateSphere();
	//D3DXCreateTorus();


	return false;
}

void MeshManager::Shutdown(void)
{
}

bool MeshManager::Init(void)
{
	return false;
}

void MeshManager::Uninit(void)
{
}

void MeshManager::LoadShaders(void)
{
}

void MeshManager::UnloadShaders(void)
{
}
