/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SceneResult.h] ���U���g��ʃN���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F���U���g��ʃN���X
=============================================================================*/
#ifndef SCENE_RESULT_H_
#define	SCENE_RESULT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../ISceneState.h"

/*-------------------------------------
/* ���U���g��ʃN���X
-------------------------------------*/
class SceneResult : public ISceneState
{
public:
	SceneResult(class Game* game);
	~SceneResult(void);

	bool Init(void) override;
	void Uninit(void) override;
	void Input(void) override;
	void Update(float deltaTime) override;

	void ChangeScene(void) override;

private:
};

#endif // SCENE_RESULT_H_
/*=============================================================================
/*		End of File
=============================================================================*/