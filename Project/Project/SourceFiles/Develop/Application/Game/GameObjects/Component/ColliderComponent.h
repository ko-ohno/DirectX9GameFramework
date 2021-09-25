/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[ColliderComponent.h] AI�r�w�C�r�A�̃x�[�X�R���|�[�l���g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FAI�r�w�C�r�A�R���|�[�l���g�̃x�[�X�ɂȂ�N���X��`
=============================================================================*/
#ifndef COLLIDER_COMPONENT_H_
#define	COLLIDER_COMPONENT_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Component.h"
#include "../../../Math.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* AI�r�w�C�r�A�R���|�[�l���g�̃x�[�X�N���X
-------------------------------------*/
class ColliderComponent : public Component
{
public:
	Vector3 position_;
	Vector3 offset_position_;

public:
	ColliderComponent(class GameObject* owner, int updateOrder = 100);
	~ColliderComponent(void);

	virtual void Update(float deltaTime) override;

	virtual TypeID GetComponentType() const override { return TypeID::ColliderComponent; };

	//
	// ���W�̐ݒ� 
	//

	inline void SetTranslation(Vector3& position) { offset_position_ = position; }
	inline void SetTranslation(D3DXVECTOR3& position) { offset_position_ = position; }
	inline void SetTranslation(float posX, float posY, float posZ) { offset_position_ = { posX, posY, posZ }; }
	inline void SetTranslationX(float posX) { offset_position_.x_ = posX; }
	inline void SetTranslationY(float posY) { offset_position_.y_ = posY; }
	inline void SetTranslationZ(float posZ) { offset_position_.z_ = posZ; }

	// �ʒu���W�̎擾
	inline Vector3* GetPosition(void) { return &position_; }

private:
protected:
};

#endif //COLLIDER_COMPONENT_H_
/*=============================================================================
/*		End of File
=============================================================================*/