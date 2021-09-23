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
class GridGizmoRendererComponent : public GizmoRendererComponent
{
public:
	GridGizmoRendererComponent(class GameObject* owner, int drawOrder = 100);
	~GridGizmoRendererComponent(void);

private:
	bool Init(void) override;
	void Uninit(void) override;

public:
	void Draw(class Shader* shader, class Camera* camera) override;

	virtual TypeID GetComponentType() const override { return TypeID::GridGizmoRendererComponent; };

private:
	bool CreateVertexBuffer(void);

private:
	// �O���b�h�̃T�C�Y
	static constexpr int GRID_SIZE = 10;

	// ��̕ӂ̒��_��
	static constexpr int ONE_EDGE_VERTEX_COUNT = 2;

	// ��̃X�g���C�v�̒��_��
	static constexpr int ONE_STRIPES_VERTEX_COUNT = ONE_EDGE_VERTEX_COUNT * (GRID_SIZE + 1);

	//
	// �e�����Ƃ̃X�g���C�v�̒��_��
	//

	static constexpr int X_AXIS_STRIPES_VERTEX_COUNT = ONE_STRIPES_VERTEX_COUNT;
	static constexpr int Y_AXIS_STRIPES_VERTEX_COUNT = 0;
	static constexpr int Z_AXIS_STRIPES_VERTEX_COUNT = ONE_STRIPES_VERTEX_COUNT;

	// ���v�̍ő咸�_��
	static constexpr int MAX_VERTEX_COUNT = X_AXIS_STRIPES_VERTEX_COUNT
										  + Y_AXIS_STRIPES_VERTEX_COUNT
										  + Z_AXIS_STRIPES_VERTEX_COUNT;	//���_�o�b�t�@��

	static LPDIRECT3DVERTEXBUFFER9	vertex_buffer_;				//���_�o�b�t�@

	static VERTEX_GIZMO*			vertex_buffer_address_;	//���_�o�b�t�@�̃A�h���X
};

#endif //GRID_GIZMO_RENDERER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/