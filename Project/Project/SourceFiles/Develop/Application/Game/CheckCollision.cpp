/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[CheckCollision.cpp] �Փ˔���̊֐��Q
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�Փ˔���̊֐��Q
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../StdAfx.h"
#include "CheckCollision.h"
#include "../Math.h"

//
// 2D�̏Փ˔���
//

D3DXVECTOR3* CheckCollision::ConvertDirectXVec3(Vector3* vec3)
{
    directx_vec3 = { vec3->x_, vec3->y_, vec3->z_ };
    return &directx_vec3;
}

/*-----------------------------------------------------------------------------
/* �~�ǂ����̏Փ˔���
-----------------------------------------------------------------------------*/
bool CheckCollision::CircleVSCircle(CircleColliderComponent* circleA, CircleColliderComponent* circleB)
{
    //�@nullptr�̃R���|�[�l���g�ƏՓ˔�����s��Ȃ��悤��
    if (circleA == nullptr) { return false; }
    if (circleB == nullptr) { return false; }

    const bool is_circleA_error = (circleA->GetComponentType() != Component::TypeID::CircleColliderComponent);
    const bool is_circleB_error = (circleB->GetComponentType() != Component::TypeID::CircleColliderComponent);
    {
        if (is_circleA_error)
        {
            assert(!"CheckCollision::CircleVSCircle()�FcircleA��CircleColliderComponent�ł͂���܂���ł���");
            return false;
        }

        if (is_circleB_error)
        {
            assert(!"CheckCollision::CircleVSCircle()�FcircleB��CircleColliderComponent�ł͂���܂���ł���");
            return false;
        }
    }

    // �������v�Z
    Vector2 distance = circleB->position_ + circleA->position_;

    // ���ꂼ���2��
    distance.x_ = distance.x_ * distance.x_;
    distance.y_ = distance.y_ * distance.y_;

    //���v�����x�N�g���̒������A���̔��a�𑫂���2�悵�������������������ꍇ
    float vec_length = distance.x_ + distance.y_;

	return vec_length <= (circleA->radius_ + circleB->radius_) * (circleA->radius_ + circleB->radius_);
}

/*-----------------------------------------------------------------------------
/* ��`�ǂ����̏Փ˔���
-----------------------------------------------------------------------------*/
bool CheckCollision::RectangleVSRectangle(RectangleColliderComponent* rectA, RectangleColliderComponent* rectB)
{
    //�@nullptr�̃R���|�[�l���g�ƏՓ˔�����s��Ȃ��悤��
    if (rectA == nullptr) { return false; }
    if (rectB == nullptr) { return false; }

    const bool is_rectA_error = (rectA->GetComponentType() != Component::TypeID::RectangleColliderComponent);
    const bool is_rectB_error = (rectB->GetComponentType() != Component::TypeID::RectangleColliderComponent);
    {
        if (is_rectA_error)
        {
            assert(!"CheckCollision::RectangleVSRectangle()�FrectA��RectangleColliderComponent�ł͂���܂���ł���");
            return false;
        }

        if (is_rectB_error)
        {
            assert(!"CheckCollision::RectangleVSRectangle()�FrectB��RectangleColliderComponent�ł͂���܂���ł���");
            return false;
        }
    }

    /* ��`A�̎l�� */
    float rect_a_left   = rectA->position_.x_;
    float rect_a_top    = rectA->position_.y_;
    float rect_a_right  = rectA->position_.x_ + rectA->width_;
    float rect_a_bottom = rectA->position_.y_ + rectA->height_;

    /* ��`B�̎l�� */
    float rect_b_left   = rectB->position_.x_;
    float rect_b_top    = rectB->position_.y_;
    float rect_b_right  = rectB->position_.x_ + rectB->width_;
    float rect_b_bottom = rectB->position_.y_ + rectB->height_;

    return (rect_a_left < rect_b_right) && (rect_a_top < rect_b_bottom) && (rect_a_right > rect_b_left) && (rect_a_bottom > rect_b_top);
}


//
// 3D�̏Փ˔���
//

/*-----------------------------------------------------------------------------
/* ���ǂ����̏Փ˔���
-----------------------------------------------------------------------------*/
bool CheckCollision::SphereVSSpghre(SphereColliderComponent* sphereA, SphereColliderComponent* sphereB)
{
    //�@nullptr�̃R���|�[�l���g�ƏՓ˔�����s��Ȃ��悤��
    if (sphereA == nullptr) { return false; }
    if (sphereB == nullptr) { return false; }

    const bool is_sphereA_error = (sphereA->GetComponentType() != Component::TypeID::SphereColliderComponent);
    const bool is_sphereB_error = (sphereB->GetComponentType() != Component::TypeID::SphereColliderComponent);
    {
        if (is_sphereA_error)
        {
            assert(!"CheckCollision::SphereVSSpghre()�FsphereA��SphereColliderComponent�ł͂���܂���ł���");
            return false;
        }

        if (is_sphereB_error)
        {
            assert(!"CheckCollision::SphereVSSpghre()�FsphereB��SphereColliderComponent�ł͂���܂���ł���");
            return false;
        }
    }

	// �������v�Z
	Vector3 distance = (sphereB->position_ - sphereA->position_);

	// ���ꂼ���2��
	distance.x_ = distance.x_ * distance.x_;
	distance.y_ = distance.y_ * distance.y_;
	distance.z_ = distance.z_ * distance.z_;

	//���v�����x�N�g���̒������A���̔��a�𑫂���2�悵�������������������ꍇ
	float vec_length = distance.x_ + distance.y_ + distance.z_;

	return vec_length <= ((sphereA->radius_ + sphereB->radius_) * (sphereA->radius_ + sphereB->radius_));
}

/*-----------------------------------------------------------------------------
/* �t�@�N�g�����\�b�h
-----------------------------------------------------------------------------*/
bool CheckCollision::ObbVSObb(OBBColliderComponent* obbA, OBBColliderComponent* obbB)
{
    //�@nullptr�̃R���|�[�l���g�ƏՓ˔�����s��Ȃ��悤��
    if (obbA == nullptr) { return false; }
    if (obbB == nullptr) { return false; }

    const bool is_obbA_error = (obbA->GetComponentType() != Component::TypeID::OBBColliderComponent);
    const bool is_obbB_error = (obbB->GetComponentType() != Component::TypeID::OBBColliderComponent);
    {
        if (is_obbA_error)
        {
            assert(!"CheckCollision::ObbVSObb()�FobbA��OBBColliderComponent�ł͂���܂���ł���");
            return false;
        }

        if (is_obbB_error)
        {
            assert(!"CheckCollision::ObbVSObb()�FobbB��OBBColliderComponent�ł͂���܂���ł���");
            return false;
        }
    }

    // �e�����x�N�g���̊m��
    // �iN***:�W���������x�N�g���j
    D3DXVECTOR3 NAe1 = *CheckCollision::ConvertDirectXVec3(obbA->GetDirElement(AxisType::X));
    D3DXVECTOR3 Ae1  = NAe1 * obbA->GetDirLength(AxisType::X);
              
    D3DXVECTOR3 NAe2 = *CheckCollision::ConvertDirectXVec3(obbA->GetDirElement(AxisType::Y));
    D3DXVECTOR3 Ae2  = NAe2 * obbA->GetDirLength(AxisType::Y);
              
    D3DXVECTOR3 NAe3 = *CheckCollision::ConvertDirectXVec3(obbA->GetDirElement(AxisType::Z));
    D3DXVECTOR3 Ae3  = NAe3 * obbA->GetDirLength(AxisType::Z);
              
    D3DXVECTOR3 NBe1 = *CheckCollision::ConvertDirectXVec3(obbB->GetDirElement(AxisType::X));
    D3DXVECTOR3 Be1  = NBe1 * obbB->GetDirLength(AxisType::X);
              
    D3DXVECTOR3 NBe2 = *CheckCollision::ConvertDirectXVec3(obbB->GetDirElement(AxisType::Y));
    D3DXVECTOR3 Be2  = NBe2 * obbB->GetDirLength(AxisType::Y);
              
    D3DXVECTOR3 NBe3 = *CheckCollision::ConvertDirectXVec3(obbB->GetDirElement(AxisType::Z));
    D3DXVECTOR3 Be3  = NBe3 * obbB->GetDirLength(AxisType::Z);

    D3DXVECTOR3 obbA_position = *CheckCollision::ConvertDirectXVec3(obbA->GetPosition());
    D3DXVECTOR3 obbB_position = *CheckCollision::ConvertDirectXVec3(obbB->GetPosition());

    D3DXVECTOR3 distance = obbA_position - obbB_position;

    {//�Փ˔��蕔��
        // ������ : Ae1
        float rA = D3DXVec3Length(&Ae1);
        float rB = OBBColliderComponent::LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
        float l = fabs(D3DXVec3Dot(&distance, &NAe1));
        if (l > rA + rB)
            return false; // �Փ˂��Ă��Ȃ�

         // ������ : Ae2
        rA = D3DXVec3Length(&Ae2);
        rB = OBBColliderComponent::OBBColliderComponent::LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
        l = fabs(D3DXVec3Dot(&distance, &NAe2));
        if (l > rA + rB)
            return false;

        // ������ : Ae3
        rA = D3DXVec3Length(&Ae3);
        rB = OBBColliderComponent::LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
        l = fabs(D3DXVec3Dot(&distance, &NAe3));
        if (l > rA + rB)
            return false;

        // ������ : Be1
        rA = OBBColliderComponent::LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
        rB = D3DXVec3Length(&Be1);
        l = fabs(D3DXVec3Dot(&distance, &NBe1));
        if (l > rA + rB)
            return false;

        // ������ : Be2
        rA = OBBColliderComponent::LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
        rB = D3DXVec3Length(&Be2);
        l = fabs(D3DXVec3Dot(&distance, &NBe2));
        if (l > rA + rB)
            return false;

        // ������ : Be3
        rA = OBBColliderComponent::LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
        rB = D3DXVec3Length(&Be3);
        l = fabs(D3DXVec3Dot(&distance, &NBe3));
        if (l > rA + rB)
            return false;

        // ������ : C11
        D3DXVECTOR3 Cross;
        D3DXVec3Cross(&Cross, &NAe1, &NBe1);
        rA = OBBColliderComponent::LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
        rB = OBBColliderComponent::LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
        l = fabs(D3DXVec3Dot(&distance, &Cross));
        if (l > rA + rB)
            return false;

        // ������ : C12
        D3DXVec3Cross(&Cross, &NAe1, &NBe2);
        rA = OBBColliderComponent::LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
        rB = OBBColliderComponent::LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
        l = fabs(D3DXVec3Dot(&distance, &Cross));
        if (l > rA + rB)
            return false;

        // ������ : C13
        D3DXVec3Cross(&Cross, &NAe1, &NBe3);
        rA = OBBColliderComponent::LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
        rB = OBBColliderComponent::LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
        l = fabs(D3DXVec3Dot(&distance, &Cross));
        if (l > rA + rB)
            return false;

        // ������ : C21
        D3DXVec3Cross(&Cross, &NAe2, &NBe1);
        rA = OBBColliderComponent::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
        rB = OBBColliderComponent::LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
        l = fabs(D3DXVec3Dot(&distance, &Cross));
        if (l > rA + rB)
            return false;

        // ������ : C22
        D3DXVec3Cross(&Cross, &NAe2, &NBe2);
        rA = OBBColliderComponent::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
        rB = OBBColliderComponent::LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
        l = fabs(D3DXVec3Dot(&distance, &Cross));
        if (l > rA + rB)
            return false;

        // ������ : C23
        D3DXVec3Cross(&Cross, &NAe2, &NBe3);
        rA = OBBColliderComponent::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
        rB = OBBColliderComponent::LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
        l = fabs(D3DXVec3Dot(&distance, &Cross));
        if (l > rA + rB)
            return false;

        // ������ : C31
        D3DXVec3Cross(&Cross, &NAe3, &NBe1);
        rA = OBBColliderComponent::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
        rB = OBBColliderComponent::LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
        l = fabs(D3DXVec3Dot(&distance, &Cross));
        if (l > rA + rB)
            return false;

        // ������ : C32
        D3DXVec3Cross(&Cross, &NAe3, &NBe2);
        rA = OBBColliderComponent::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
        rB = OBBColliderComponent::LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
        l = fabs(D3DXVec3Dot(&distance, &Cross));
        if (l > rA + rB)
            return false;

        // ������ : C33
        D3DXVec3Cross(&Cross, &NAe3, &NBe3);
        rA = OBBColliderComponent::LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
        rB = OBBColliderComponent::LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
        l = fabs(D3DXVec3Dot(&distance, &Cross));
        if (l > rA + rB)
            return false;

        // �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
        return true;

    }
}

/*=============================================================================
/*		End of File
=============================================================================*/