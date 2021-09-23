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

public:
	void Draw(class Shader* shader, class Camera* camera) override;

	virtual TypeID GetComponentType() const override { return TypeID::SphereGizmoRendererComponent; };

	//�g�k�����̑���

	virtual inline void SetScale(float scaleValue) override { scale_ = { scaleValue * 2.f, scaleValue * 2.f, scaleValue * 2.f }; }
	virtual inline void SetScale(float scaleX, float scaleY, float scaleZ = 1.f)  override { scale_ = { scaleX * 2.f, scaleY * 2.f, scaleZ * 2.f }; }
	virtual inline void SetScale(const D3DXVECTOR3& scale)  override { scale_ = (scale * 2.f); }
	virtual inline void SetScaleX(float scaleX)  override { scale_.x = (scaleX * 2.f); }
	virtual inline void SetScaleY(float scaleY)  override { scale_.y = (scaleY * 2.f); }
	virtual inline void SetScaleZ(float scaleZ)  override { scale_.z = (scaleZ * 2.f); }

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