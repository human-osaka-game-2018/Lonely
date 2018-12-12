/**
* @file	Input.h
* @brief Input�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include <windows.h>

/** 
* @brief DirectInput�֌W�̏������܂Ƃ߂��N���X
*/
class Input
{
public:

	/**
	* @brief �L�[���͂̍\����
	*/
	enum EKeyBind
	{
		Option,	//!< Option
		A,		//!< A
		B,		//!< B

		Up,		//!< ��
		Down,	//!< ��
		Left,	//!< ��
		Right,	//!< ��


		KeyBindMax,
	};

	Input();
	~Input();

	/** 
	* @brief ���̓V�X�e���̏��������s���֐�
	*/
	void Initialize();

	/** 
	* @brief ���̓V�X�e���̉�����s���֐�
	*/
	void Finalize();

	/** 
	* @brief ���͏󋵂̍X�V���s���֐�
	*/
	void Update();

	/** 
	* @brief �L�[�o�C���h�̐ݒ���s���֐�
	* @param �L�[���͏����܂Ƃ߂��\����
	* @param �ǂ̃L�[���͏�񂪗~������
	*/
	void BindKey(EKeyBind key, int keycode);

	/** 
	* @brief �L�[��������Ă��邩���擾����֐�
	* @param �L�[���͏����܂Ƃ߂��\����
	* @return �L�[��������Ă�����TRUE
	*/
	bool IsKeyPress(EKeyBind key);

	/**
	* @brief �L�[�������ꂽ���H
	* @param ���͏����܂Ƃ߂��\����
	* @return �L�[��������Ă�����TRUE
	*/
	bool IsKeyPush(EKeyBind key);

	/** 
	* @brief �L�[�������ꂽ���擾����֐�
	* @return �L�[��������Ă�����TRUE
	*/
	bool IsKeyReleases(EKeyBind key);

private:
	
	/**
	* @brief �L�[���͏������\����
	*/
	struct KeyInfo
	{
		int keyBind[KeyBindMax];
		int keyState;
		int keyStateOld;
	};

	/** KeyInfo�\���̂̎��� */
	KeyInfo	m_keyState;
};
