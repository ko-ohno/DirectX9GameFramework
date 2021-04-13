#include "../../../../../../StdAfx.h"
#include "GridGizmoRendererComponent.h"

GridRendererComponent::GridRendererComponent(void)
{
}

GridRendererComponent::~GridRendererComponent(void)
{
}

void GridRendererComponent::WireFlameON(void)
{
	LPDIRECT3DDEVICE9 lpd3d_device = nullptr;
	lpd3d_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}

void GridRendererComponent::WireFlameOFF(void)
{
	LPDIRECT3DDEVICE9 lpd3d_device = nullptr;
	lpd3d_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}
