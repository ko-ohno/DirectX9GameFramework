/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[FFPMeshRendererComponent.h] �Œ�@�\�p�C�v���C���ɂ�郁�b�V���`��
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Œ�@�\�p�C�v���C���ɂ�郁�b�V���`��R���|�[�l���g�N���X
=============================================================================*/
#ifndef FFP_MESH_RENDERER_COMPONENT_H_
#define	FFP_MESH_RENDERER_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../RendererComponent.h"

/*-----------------------------------------------
/* �W�����b�V�������_���[�R���|�[�l���g�N���X
-----------------------------------------------*/
class FFPMeshRendererComponent : public RendererComponent
{
public:
	FFPMeshRendererComponent(class GameObject* owner, int drawOrder = 100);
	~FFPMeshRendererComponent(void);

	bool Init(void) override;
	void Uninit(void) override;

	void Draw(class Shader* shader, class Camera* camera) override;

	virtual TypeID GetComponentType() const override { return TypeID::FFPMeshRendererComponent; };

	// ���b�V�����̐ݒ�
	void SetMesh(XFileMeshType xfileMeshTypeID);

	// ���b�V�����̎擾
	class XFileMesh* GetMesh(void);

private:
	// ���b�V���̃f�[�^
	class XFileMesh* xfile_mesh_;
};


#endif //FFP_MESH_RENDERER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/