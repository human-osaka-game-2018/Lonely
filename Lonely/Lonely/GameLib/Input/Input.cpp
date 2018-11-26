/**
* @file	Input.cpp
* @brief Input�N���X�̃\�[�X�t�@�C��
* @author ����@�k��
*/

#include "Input.h"

Input::Input()
{
	Initialize();
}
Input::~Input()
{
	Finalize();
}

// ���̓V�X�e���̏�����
void Input::Initialize()
{
	for (int i = 0; i < KeyBindMax; i++)
	{
		m_keyState.keyBind[i] = -1;
	}
	m_keyState.keyState = 0;
	m_keyState.keyStateOld = 0;
}

// ���̓V�X�e���̉��
void Input::Finalize()
{
	//����͕K�v�Ȃ����A�L�[���͏����O�ŏ��������Ă���
	Initialize();
}

// ���͏󋵂̍X�V
void Input::Update()
{
	BYTE keyboardState[256];
	// �L�[�{�[�h��Ԃ̎擾
	GetKeyboardState(keyboardState);

	int keyState = 0;
	for (int i = 0; i < KeyBindMax; i++)
	{
		// �L�[���o�C���h����Ă��Ȃ���΃X���[����
		int key = m_keyState.keyBind[i];
		if (key == -1) continue;

		// ���͂���Ă���ꍇ�̓L�[�̃r�b�g�𗧂Ă�
		if (keyboardState[key] & 0x80)
		{
			keyState |= (1 << i);
		}
	}
	// �X�e�[�g�̍X�V
	m_keyState.keyStateOld = m_keyState.keyState;
	m_keyState.keyState = keyState;
}

// �L�[�o�C���h�̐ݒ�
void Input::BindKey(EKeyBind key, int keycode)
{
	m_keyState.keyBind[key] = keycode;
}

// �L�[��������Ă��邩�H
bool Input::IsKeyPress(EKeyBind key)
{
	int bit = (1 << key);
	int state = m_keyState.keyState;
	return (state & bit) ? true : false;
}

// �L�[�������ꂽ���H
bool Input::IsKeyPush(EKeyBind key)
{
	int bit = (1 << key);
	int state = m_keyState.keyState & ~m_keyState.keyStateOld;
	return (state & bit) ? true : false;
}

// �L�[�������ꂽ���H
bool Input::IsKeyReleases(EKeyBind key)
{
	int bit = (1 << key);
	int state = m_keyState.keyStateOld & ~m_keyState.keyState;
	return (state & bit) ? true : false;
}
