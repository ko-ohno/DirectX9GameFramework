/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[GameCamera.h] �J�����Q�[���I�u�W�F�N�g
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�J�����Q�[���I�u�W�F�N�g
=============================================================================*/
#ifndef GameCamera_H_
#define	GameCamera_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../Camera.h"

/*-------------------------------------
/* �J�����Q�[���I�u�W�F�N�g
-------------------------------------*/
class GameCamera : public Camera
{
public:
	GameCamera(class Game* game);
	~GameCamera(void);

	bool Init(void);	//������
	void Uninit(void);	//�I����

	//GameObject�̊֐�override���āA���g�̋����Ƃ��Ē�`����
	virtual void InputGameObject(void) override;
	virtual void UpdateGameObject(float deltaTime) override;

	virtual TypeID GetType(void) const { return TypeID::GameCamera; }

private:
	static constexpr float MAX_CAMERA_ANIMATION_TIME = 10.f;

	float camera_animation_time_;

private:
	// �����_���W�̃M�Y��
	class BoxGizmoRendererComponent* lookat_point_gizmo_;

	// �オ�邩�����邩
	bool is_move_top_;
	bool is_move_bottom_;

	// �l�����邩�A����邩
	bool is_value_over_;
	bool is_value_under_;

	// ����
	float vertical_camera_shake_;
};


#endif //GameCamera_H_
/*=============================================================================
/*		End of File
=============================================================================*/