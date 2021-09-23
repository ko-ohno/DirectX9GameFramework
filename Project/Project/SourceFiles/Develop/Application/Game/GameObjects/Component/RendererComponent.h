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
#include "../../ResourceManager/ShaderManager.h"
#include "../../ResourceManager/TextureManager.h"
#include "../../ResourceManager/MeshManager.h"
#include "../../ResourceManager/EffectManager.h"
#include "../../../DX9Graphics.h"
#include "../../VertexData.h"
#include "../Component/TransformComponent.h"

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

	bool Init(void) override;
	void Uninit(void) override;
	void Update(float deltaTime) override;
	virtual void Draw(class Shader* shader, class Camera* camera);

public:

	void SetVertexColor(int red = 255, int green = 255, int blue = 255, int alpha = 255)
	{
		vertex_color_ = D3DCOLOR_RGBA(red, green, blue, alpha);

		vector_vertex_color_.x = DIVIDE_COLOR_VALUE * red;
		vector_vertex_color_.y = DIVIDE_COLOR_VALUE * green;
		vector_vertex_color_.z = DIVIDE_COLOR_VALUE * blue;
		vector_vertex_color_.w = DIVIDE_COLOR_VALUE * alpha;

		vector_vertex_color_.x = Math::Clamp(vector_vertex_color_.x, 0.f, 1.f);
		vector_vertex_color_.y = Math::Clamp(vector_vertex_color_.y, 0.f, 1.f);
		vector_vertex_color_.z = Math::Clamp(vector_vertex_color_.z, 0.f, 1.f);
		vector_vertex_color_.w = Math::Clamp(vector_vertex_color_.w, 0.f, 1.f);
	}

	inline D3DXVECTOR4* GetVertexColor(void) { return &vector_vertex_color_; }

public:
	//�p������̊֐��Q

	//���s�ړ������̑���

	virtual inline void SetTranslation(float posX, float posY, float posZ = 0.f) { position_ = { posX, posY, posZ }; }
	virtual inline void SetTranslation(const D3DXVECTOR3& position) { position_ = position; }
	virtual inline void SetTranslationX(float posX) { position_.x = posX; }
	virtual inline void SetTranslationY(float posY) { position_.y = posY; }
	virtual inline void SetTranslationZ(float posZ) { position_.z = posZ; }

	virtual inline void AddTranslation(float addValueX, float addValueY, float addValueZ = 0.f) { position_ += { addValueX, addValueY, addValueZ }; }
	virtual inline void AddTranslation(const D3DXVECTOR3& addValue) { position_ += addValue; }
	virtual inline void AddTranslationX(float addValueX) { position_.x = addValueX; }
	virtual inline void AddTranslationY(float addValueY) { position_.y = addValueY; }
	virtual inline void AddTranslationZ(float addValueZ) { position_.z = addValueZ; }

	inline D3DXVECTOR3* GetPosition(void) { return &position_; }

	//�g�k�����̑���

	virtual inline void SetScale(float scaleValue) { scale_ = { scaleValue, scaleValue, scaleValue }; }
	virtual inline void SetScale(float scaleX, float scaleY, float scaleZ = 1.f) { scale_ = { scaleX, scaleY, scaleZ }; }
	virtual inline void SetScale(const D3DXVECTOR3& scale) { scale_ = scale; }
	virtual inline void SetScaleX(float scaleX) { scale_.x = scaleX; }
	virtual inline void SetScaleY(float scaleY) { scale_.y = scaleY; }
	virtual inline void SetScaleZ(float scaleZ) { scale_.z = scaleZ; }

	virtual inline void AddScale(float addValueX, float addValueY, float addValueZ = 0.f) { scale_ += { addValueX, addValueY, addValueZ }; }
	virtual inline void AddScale(const D3DXVECTOR3& addValue) { scale_ += addValue; }
	virtual inline void AddScaleX(float addValueX) { scale_.x = addValueX; }
	virtual inline void AddScaleY(float addValueY) { scale_.y = addValueY; }
	virtual inline void AddScaleZ(float addValueZ) { scale_.z = addValueZ; }

	inline D3DXVECTOR3* GetScale(void) { return &scale_; }

public: 
	// ���̃R���|�[�l���g�̉�]���擾
	inline D3DXMATRIX* GetRotationMatrix(void) { return &rotation_matrix_; }
	inline void SetRotationMatrix(const D3DXMATRIX& rotationMatrix) { rotation_matrix_ = rotationMatrix; }

	// ���̃R���|�[�l���g�̃��[���h���W�����擾
	inline D3DXMATRIX* GetWorldMatrix(void) { return &world_matrix_; }

	// ���̃R���|�[�l���g�̌^
	inline TypeID GetComponentType(void) const override { return TypeID::RendererComponent; }
	
	// ���̃R���|�[�l���g�̌^
	inline bool IsGetDrawable(void) { return is_drawable_; }
	inline void IsSetDrawable(bool isDrawable) { is_drawable_ = isDrawable; }

	// ���̃R���|�[�l���g�������_�����O�����`�惌�C���[�̐ݒ�
	inline RendererLayerType GetRendererLayerType(void) const { return renderer_layer_type_; }
	inline void SetRendererLayerType(RendererLayerType rendererLayerType) { renderer_layer_type_ = rendererLayerType; }

	// ���̃R���|�[�l���g�������_�����O�����V�F�[�_�[�̎��
	inline ShaderType GetShaderType(void) const { return shader_type_; }
	inline void SetShaderType(ShaderType shaderType) { shader_type_ = shaderType; }

	// �`�施�ߏ���:���l���傫���قǕ`�揇�ʂ�����
	inline int GetDrawOrder(void) const   { return draw_order_; }

	// ���L�҂̎p������̉e�����󂯂邩�H
	inline void IsSetOwnerTransfromOrder(bool isOwnerTransformOrder) { is_owner_transform_order_ = isOwnerTransformOrder; }

	// �J��������̋���
	inline float GetCameraDistance(void) const { return camera_distance_; }
	inline void SetCameraDistance(float cameraDistance) { camera_distance_ = cameraDistance; }


protected:
	//
	//�@Renderer�p�̏��
	//

	// �`�悷�邩
	bool is_drawable_;

	// �`�悷�郌�C���[�̎��
	RendererLayerType renderer_layer_type_;

	// �`�悳���V�F�[�_�[�̎��
	ShaderType shader_type_;

	// �`��̗D�揇��
	int draw_order_;

	// �J�����܂ł̋���
	float camera_distance_;

protected:
	static constexpr float DIVIDE_COLOR_VALUE = 1.f / 255.f;

	//���_�J���[
	D3DCOLOR	vertex_color_;

	D3DXVECTOR4 vector_vertex_color_;

	//
	// RendererComponent�̎p�����
	//

	bool is_owner_transform_order_;

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