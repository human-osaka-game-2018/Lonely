/**
* @file SelectCursorInformation.h
* @brief SelectCursorInformation�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include <d3dx9math.h>

/**
* @brief �L�^�J�[�\���̏��
*/
enum CAT_CORSOR_STATE
{
	DATA1,        //!< �f�[�^�P��I�����Ă���Ƃ�
	DATA2,        //!< �f�[�^�Q��I�����Ă���Ƃ�
	DATA3,        //!< �f�[�^�R��I�����Ă���Ƃ�
};

/**
* @brief �~�j�J�[�\���i��������A���߂���A�߂�j�̏��
*/
enum MINI_CORSOR_STATE
{
	CONTINUE,     //!< �u��������v��I�����Ă���Ƃ�
	NEWGAME,      //!< �u���߂���v��I�����Ă���Ƃ�
	BACK,         //!< �u�߂�v��I�����Ă���Ƃ�
};


/**
* @brief ���L���������܂Ƃ߂��N���X
*/
class SelectCursorInformation
{
public:

	SelectCursorInformation();
	~SelectCursorInformation();

	/**
	* @brief �������֐�
	*/
	bool Initialize();

	/**
	* @brief ����֐�
	*/
	void Finalize();

	/**
	* @brief �X�V�֐�
	*/
	void Update();

	
public://�Z�b�^�[�ƃQ�b�^�[

	//�L�^�J�[�\���̏��
	void SetCatCursorState(int state) { m_catCursorState = state; }
	int GetCatCursorState() { return m_catCursorState; }

	//�~�j�J�[�\���̏��
	void SetMiniCursorState(int state) { m_miniCursorState = state; }
	int GetMiniCursorState() { return m_miniCursorState; }
	
private:

	void SelectCursorInformation::UpdateCatCursorState();
	void SelectCursorInformation::UpdateMiniCursorState();

	int  m_catCursorState = DATA1;        //!< �L�^�J�[�\���̏��
	int  m_miniCursorState = CONTINUE;    //!< �~�j�J�[�\���i��������A���߂���A�߂�j�̏��
	bool m_catCursorIsActive = true;      //!< �L�^�J�[�\�����哱���������Ă��邩                       
	bool m_miniCursorIsActive = false;    //!< �~�j�J�[�\�����哱���������Ă��邩

};
