#pragma once

#include "../../../StdAfx.h"

class Texture
{
public:
	Texture();
	~Texture();

	bool LoadTexture();

private:
	LPDIRECT3DTEXTURE9* lpd3d_texture_;
};

