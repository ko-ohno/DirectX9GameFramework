/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GizmoRendererComponent.h]  �M�Y���`��R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�M�Y���`��R���|�[�l���g
=============================================================================*/
#ifndef GIZMO_RENDERER_COMPONENT_H_
#define	GIZMO_RENDERER_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../RendererComponent.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �R���|�[�l���g
-------------------------------------*/
class GizmoRendererComponent : public RendererComponent
{
public:
	GizmoRendererComponent(class GameObject* owner, int drawOrder = 100);
	~GizmoRendererComponent(void);

public:
	bool Init(void) override;
	void Uninit(void) override;
	void Draw(class Shader* shader, class Camera* camera) override;

	virtual TypeID GetComponentType() const override { return TypeID::GizmoRendererComponent; };

private:
};

#endif //GIZMO_RENDERER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/