/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[LightManager.h] ���C�g�Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���C�g�Ǘ��N���X
=============================================================================*/
#ifndef LIGHT_MANAGER_H_
#define	LIGHT_MANAGER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"

enum class LightType
{
	None = -1
	, DirectionalLight
	, PointLight
	, SpotLight
	, Max
};

/*-------------------------------------
/* ���C�g�Ǘ��N���X
-------------------------------------*/
class LightManager
{
public:
	LightManager(class Game* game);
	~LightManager(void);

	static LightManager* Create(class Game* game);

	bool StartUp(void);	 //�N��
	void Shutdown(void); //��~

private:
	bool Init(void);	 //������
	void Uninit(void);	 //�I����

public:
	//
	// ���b�V���̒ǉ��ƍ폜
	//

	void AddLight(class Light* light);
	void RemoveLight(class Light* light);

	class Game* GetGame(void) { return game_; }

	std::vector<class Light*> GetLightList(void) { return light_list_; }
private:
	//�}�l�[�W���[�̏��L��
	class Game* game_;

	//���C�g�̃R���e�i
	std::vector<class Light*> light_list_;
};

#endif //LIGHT_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/