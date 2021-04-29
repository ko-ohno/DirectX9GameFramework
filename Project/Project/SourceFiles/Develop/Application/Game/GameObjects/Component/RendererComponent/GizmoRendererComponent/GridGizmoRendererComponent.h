/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GridRendererComponent.h]  �O���b�h�M�Y���`��R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�O���b�h�M�Y���`��R���|�[�l���g
=============================================================================*/
#ifndef GRID_GIZMO_RENDERER_COMPONENT_H_
#define	GRID_GIZMO_RENDERER_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../GizmoRendererComponent.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �O���b�h�M�Y���`��R���|�[�l���g
-------------------------------------*/
class GridRendererComponent : public GizmoRendererComponent
{
public:
	GridRendererComponent(class GameObject* owner, int updateOrder = 100);
	~GridRendererComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Input(void) override;
	void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::GridRendererComponent; };

	void WireFlameON(void);
	void WireFlameOFF(void);

private:
};

#endif //GRID_GIZMO_RENDERER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/