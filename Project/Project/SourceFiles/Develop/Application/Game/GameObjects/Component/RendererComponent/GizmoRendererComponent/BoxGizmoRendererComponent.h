/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[BoxGizmoRendererComponent.h]  �{�b�N�X�M�Y���`��R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�{�b�N�X�M�Y���`��R���|�[�l���g
=============================================================================*/
#ifndef BOX_GIZMO_RENDERER_COMPONENT_H_
#define	BOX_GIZMO_RENDERER_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../GizmoRendererComponent.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �{�b�N�X�M�Y���`��R���|�[�l���g
-------------------------------------*/
class BoxGizmoRendererComponent : public GizmoRendererComponent
{
public:
	BoxGizmoRendererComponent(class GameObject* owner, int drawOrder = 100);
	~BoxGizmoRendererComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;
	void Draw(class Shader* shader, class Camera* camera) override;

	virtual TypeID GetComponentType() const override { return TypeID::BoxGizmoRendererComponent; };

	// ���b�V�����̎擾
	class XFileMesh* GetMesh(void);

private:
	// ���b�V���̃f�[�^
	class XFileMesh* xfile_mesh_;
};

#endif //BOX_GIZMO_RENDERER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/