/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[Scene.h] �^�C�g����ʃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�^�C�g����ʃN���X
=============================================================================*/
#ifndef SCENE_TITLE_H_
#define	SCENE_TITLE_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../ISceneState.h"

/*-------------------------------------
/* �^�C�g����ʃN���X
-------------------------------------*/
class SceneTitle : public ISceneState
{
public:
	SceneTitle(class Game* game);
	~SceneTitle(void);

	bool Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;

	void ChangeScene(void) override;

private:
};


#endif //SCENE_H_
/*=============================================================================
/*		End of File
=============================================================================*/