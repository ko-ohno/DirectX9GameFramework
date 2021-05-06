/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[InputCheck.h] �f�o�C�X����̓��͏󋵂𒆌p����N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�f�o�C�X����̓��͏󋵂𒆌p���邽�߂̒�����N���X��`
=============================================================================*/
#ifndef INPUT_CHECK_H_
#define	INPUT_CHECK_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../../../StdAfx.h"
#include "../../InputDevice/InputDeviceXInput.h"

/*--- �\���̒�` ---*/


/*-------------------------------------
/* �}�E�X���͗p�萔
-------------------------------------*/
enum class MibNum :int
{
	MIB_LEFT = 0,
	MIB_RIGHT,
	MIB_CENTER,
};

enum class PadIndex : int
{
	Pad1 = 0,
	Pad2,
	Pad3,
	Pad4
};


/*-------------------------------------
/* ���͒��p�N���X
-------------------------------------*/
class InputCheck
{
private:
	InputCheck(void);

public:
	~InputCheck(void);
	//Press		//�{�^������������
	//Trigger	//�{�^�����������u��
	//Repeat	//�{�^�������������Ă�����
	//Release	//�{�^����������u��

	static void SetInputDeviceState(class InputDevice * inputDevice);

	static bool KeyPress(int dikKeynum);
	static bool KeyTrigger(int dikKeynum);
	static bool KeyRepeat(int dikKeynum);
	static bool KeyRelease(int dikKeynum);

	static bool MButtonPress(MibNum mibNum);
	static bool MButtonTrigger(MibNum mibNum);
	static bool MButtonRepeat(MibNum mibNum);
	static bool MButtonRelease(MibNum mibNum);
	static class Vector2 MouseCursorPos(void);

	static bool XInputPress(PadIndex padIndex, XInputButton xibIndex);
	static bool XInputTrigger(PadIndex padIndex, XInputButton xibIndex);
	static bool XInputRepeat(PadIndex padIndex, XInputButton xibIndex);
	static bool XInputRelease(PadIndex padIndex, XInputButton xibIndex);
	static class Vector2 XInputThumbLeft(PadIndex padIndex);
	static class Vector2 XInputThumbRight(PadIndex padIndex);

private:
	static class InputDevice *input_device_;
};

#endif //INPUT_CHECK_H_
/*=============================================================================
/*		End of File
=============================================================================*/
