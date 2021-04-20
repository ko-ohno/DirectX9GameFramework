/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StdMeshRendererComponent.h] �W�����b�V�������_���[�R���|�[�l���g�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�W�����b�V�������_���[�R���|�[�l���g�N���X
=============================================================================*/
#ifndef STD_MESH_RENDERER_COMPONENT_H_
#define	STD_MESH_RENDERER_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../RendererComponent.h"
#include "../../../../Math.h"


/*-----------------------------------------------
/* �W�����b�V�������_���[�R���|�[�l���g�N���X
-----------------------------------------------*/
class StdMeshRendererComponent : public RendererComponent
{
public:
	StdMeshRendererComponent(class GameObject* owner, int drawOrder = 100);
	~StdMeshRendererComponent(void);

	bool Init(void) override;
	void Uninit(void) override;

	void Draw(class Shader* shader, class Camera* camera) override;

	virtual TypeID GetComponentType() const override { return TypeID::StdMeshRendererComponent; };

	// ���b�V���̐ݒ�
	void SetMesh(XFileMeshType xfileMeshTypeID);

	// ���b�V�����̎擾
	class XFileMesh* GetMesh(void);

private:
	// ���b�V���̃f�[�^
	class XFileMesh* xfile_mesh_;
};


#endif //STD_MESH_RENDERER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/