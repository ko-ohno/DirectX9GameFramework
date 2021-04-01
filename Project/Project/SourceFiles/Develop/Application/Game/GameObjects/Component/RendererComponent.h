/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[RendererComponent.h] �����_���[�R���|�[�l���g�̃x�[�X�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�����_���[�R���|�[�l���g�̃x�[�X�ɂȂ�N���X��`
=============================================================================*/
#ifndef RENDER_COMPONENT_H_
#define	RENDER_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Component.h"
#include "../../Game.h"
#include "../../Manager/ShaderManager.h"
#include "../../Manager/TextureManager.h"
#include "../../Manager/MeshManager.h"
#include "../../../DX9Graphics.h"
#include "../../VertexData.h"

/*-------------------------------------
/* �����_���[���ۗL����郌�C���[�̌^
-------------------------------------*/
enum class RendererLayerType
{
	None = -1
	, Sky				//�X�J�C�{�b�N�X�Ȃǃ��b�V��
	, BackGround		//�w�i�ƂȂ�n��Ȃǂ̃��b�V��
	, Game				//�Q�[���p�̃I�u�W�F�N�g(���b�V����r���{�[�h)���z�u����郌�C���[
	, ParticleEffect	//�p�[�e�B�N���p(���Z�����G�t�F�N�g�Ȃ�)�̃��C���[
	, UI				//HUD��^�C�g����ʂȂ�
	, Fade				//�t�F�[�h�p�̃��C���[

	, Max
};

/*-------------------------------------
/* �����_���[�R���|�[�l���g�̃x�[�X�N���X
-------------------------------------*/
class RendererComponent : public Component
{
public:
	RendererComponent(class GameObject* owner, int drawOrder = 100);
	~RendererComponent(void);

	//������
	bool Init(void) override;

	//�I����
	void Uninit(void) override;
	
	//�X�V����
	void Update(float deltaTime) override;

	//�`�揈��
	virtual void Draw(class Shader* shader, class Camera* camera);

public:

	void SetVertexColor(int red = 255, int green = 255, int blue = 255, int alpha = 255)
	{
		vertex_color_ = D3DCOLOR_RGBA(red, green, blue, alpha);
	}

	void SetVertexColor(D3DCOLOR color = D3DCOLOR_RGBA(255, 255, 255, 255))
	{
		vertex_color_ = color;
	}


public:
	//�p������̊֐��Q

	//���s�ړ������̑���

	inline void SetTranslation(float posX, float posY, float posZ = 0.f) { position_ = { posX, posY, posZ }; }
	inline void SetTranslation(const D3DXVECTOR3& position) { position_ = position; }
	inline void SetTranslationX(float posX) { position_.x = posX; }
	inline void SetTranslationY(float posY) { position_.y = posY; }
	inline void SetTranslationZ(float posZ) { position_.z = posZ; }

	inline void AddTranslation(float addValueX, float addValueY, float addValueZ = 0.f) { position_ += { addValueX, addValueY, addValueZ }; }
	inline void AddTranslation(const D3DXVECTOR3& addValue) { position_ += addValue; }
	inline void AddTranslationX(float addValueX) { position_.x = addValueX; }
	inline void AddTranslationY(float addValueY) { position_.y = addValueY; }
	inline void AddTranslationZ(float addValueZ) { position_.z = addValueZ; }

	inline D3DXVECTOR3 GetPositon(void) const { return position_; }

	//�g�k�����̑���

	inline void SetScale(float scaleX, float scaleY, float scaleZ = 1.f) { scale_ = { scaleX, scaleY, scaleZ }; }
	inline void SetScale(const D3DXVECTOR3& scale) { scale_ = scale; }
	inline void SetScaleX(float scaleX) { scale_.x = scaleX; }
	inline void SetScaleY(float scaleY) { scale_.y = scaleY; }
	inline void SetScaleZ(float scaleZ) { scale_.z = scaleZ; }

	inline void AddScale(float addValueX, float addValueY, float addValueZ = 0.f) { scale_ += { addValueX, addValueY, addValueZ }; }
	inline void AddScale(const D3DXVECTOR3& addValue) { scale_ += addValue; }
	inline void AddScaleX(float addValueX) { scale_.x = addValueX; }
	inline void AddScaleY(float addValueY) { scale_.y = addValueY; }
	inline void AddScaleZ(float addValueZ) { scale_.z = addValueZ; }

	inline D3DXVECTOR3 GetScale(void) const { return scale_; }

public:

	// ���̃R���|�[�l���g�̌^
	inline TypeID GetComponentType(void) const override { return TypeID::RendererComponent; }
	
	// ���̃R���|�[�l���g�������_�����O�����`�惌�C���[�̎��
	inline RendererLayerType GetRendererLayerType(void) const { return renderer_layer_type_; }

	// ���̃R���|�[�l���g�������_�����O�����V�F�[�_�[�̎��
	inline ShaderType GetShaderType(void) const { return shader_type_; }

	// �`�施�ߏ���:���l���傫���قǕ`�揇�ʂ�����
	inline int GetDrawOrder(void) const   { return draw_order_; }

	// �J��������̋���
	inline float GetCameraDistance(void) const { return camera_distance_; }
	inline void SetCameraDistance(float cameraDistance) { camera_distance_ = cameraDistance; }


protected:
	//
	//�@Renderer�p�̏��
	//

	// �`�悷�郌�C���[�̎��
	RendererLayerType renderer_layer_type_;

	// �`�悳���V�F�[�_�[�̎��
	ShaderType shader_type_;

	// �`��̗D�揇��
	int draw_order_;

	// �J�����܂ł̋���
	float camera_distance_;

protected:

	//���_�J���[
	D3DCOLOR vertex_color_;

	//
	// RendererComponent�̎p�����
	//

	//��]���
	D3DXMATRIX rotation_matrix_;

	//���[���h���W
	D3DXMATRIX world_matrix_;

	//���W
	D3DXVECTOR3 position_;

	//�|���S���̃T�C�Y
	D3DXVECTOR3 scale_;
};

#endif //RENDER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/