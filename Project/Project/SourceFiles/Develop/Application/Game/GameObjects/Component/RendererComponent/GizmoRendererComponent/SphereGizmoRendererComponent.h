/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[SphereGizmoRendererComponent.h]  �X�t�B�A�M�Y���`��R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�X�t�B�A�M�Y���`��R���|�[�l���g
=============================================================================*/
#ifndef SPHERE_GIZMO_RENDERER_COMPONENT_H_
#define	SPHERE_GIZMO_RENDERER_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../GizmoRendererComponent.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* �X�t�B�A�M�Y���`��R���|�[�l���g
-------------------------------------*/
class SphereGizmoRendererComponent : public GizmoRendererComponent
{
public:
	SphereGizmoRendererComponent(class GameObject* owner, int drawOrder = 100);
	~SphereGizmoRendererComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;
	void Draw(class Shader* shader, class Camera* camera) override;

	virtual TypeID GetComponentType() const override { return TypeID::SphereGizmoRendererComponent; };

	// ���b�V�����̎擾
	class XFileMesh* GetMesh(void);

private:
	// ���b�V���̃f�[�^
	class XFileMesh* xfile_mesh_;
};

#endif //SPHERE_GIZMO_RENDERER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/