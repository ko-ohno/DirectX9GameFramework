/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StdAfx.h] �W���A�v���P�[�V�����g���t���[�����[�N
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h�t�@�C���A
/*	�܂��͎Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p��
/*	�C���N���[�h�t�@�C�� ���L�q���܂��B
=============================================================================*/
#ifndef STDAFX_H_
#define	STDAFX_H_

//�W���A�v���P�[�V�����g���t���[�����[�N
//"StdAfx" Standard Application Framework Extensions.

/*--- �C���N���[�h�t�@�C�� ---*/
#include <Windows.h>	// WindowsAPI�̋@�\�𗘗p���邽�߂̃w�b�_�[�t�@�C���B

//Windows.h�̃}�N���֐��Amin��max�̏��O�B
#undef min
#undef max

/*--- �Q�[���ɕK�v�ȃ��C�u�����̌Ăяo�� ---*/
//�O���t�B�b�N�X�n
#include <d3d9.h>		//DirectX9�̃C���^�[�t�F�[�X
#include <d3dx9.h>		//DirectX9�̋@�\�𗘗p���邽�߂̃w�b�_

//���͌n
#define DIRECTINPUT_VERSION (0x0800) //DirectInput�̃o�[�W�������w��B
#include<dinput.h>		//���͗p���C�u����

/*--- C�����^�C���w�b�_�[�t�@�C�� ---*/
#include <cstdio>	
#include <cstdlib>	
#include <cassert>
#include <crtdbg.h>
#include <cmath>	
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

/*--- STL�̃t�@�C�����C���N���[�h ---*/
#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <algorithm>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>

/*--- ���C�u�����̃����N ---*/
#pragma comment(lib,"winmm.lib")	//WindowsAPI�̃��C�u�����������N
#pragma comment(lib,"d3d9.lib")		//DirectX9�̋@�\���g�����߂Ƀ��C�u�����������N
#if defined(_DEBUG)||(DEBUG)
#pragma comment(lib,"d3dx9d.lib")	//�f�o�b�O��	
#else
#pragma comment(lib,"d3dx9.lib")	//�����[�X��
#endif
#pragma comment(lib,"dxguid.lib")	//���͂≹���̏����ɕK�v�B
#pragma comment(lib,"dinput8.lib")	//���͗p�̃��C�u�����������N

/*--- �}�N���̒�` ---*/

//�������[���[�N�����m�p�̏���
#if defined(_DEBUG) || defined(DEBUG) && !defined(NEW)
#define _CRTDBG_MAP_ALLOC //new��operator��override������`���Ăяo�����߂̃}�N��
#define NEW  ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define NEW  new
#endif

//����������}�N���֐�
#define SAFE_RELEASE_(x) if((x) != NULL){ (x)->Release(); x = nullptr; }

//���g��delete����}�N���֐�
#define SAFE_DELETE_(p) { if(p) { delete p; p = nullptr; } }

//�z��̒��g��delete����}�N���֐�
#define SAFE_DELETE_ARRAY_(p) { if(p) { delete []p;   p = nullptr; } }

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/

#endif //STDAFX_H_
/*=============================================================================
/*		End of File
=============================================================================*/