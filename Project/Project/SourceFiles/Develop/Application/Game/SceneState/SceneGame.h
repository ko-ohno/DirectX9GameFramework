/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Scene.h] �Q�[����ʃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Q�[����ʃN���X
=============================================================================*/
#ifndef SCENE_GAME_H_
#define	SCENE_GAME_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../ISceneState.h"

/*-------------------------------------
/* �Q�[����ʃN���X
-------------------------------------*/
class SceneGame : public ISceneState
{
public:
	SceneGame(class Game* game);
	~SceneGame(void);

	bool Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;

	// �V�[���̐؂�ւ�����
	void ChangeScene(void) override;

private:
};

#endif //SCENE_H_
/*=============================================================================
/*		End of File
=============================================================================*/