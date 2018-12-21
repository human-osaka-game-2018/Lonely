/**
* @file SelectStateManager.h
* @brief SelectStateManager�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include "../../../GameLib/ObjectManager/Object.h"
#include <vector>

/**
* �f�[�^�Z���N�g�V�[���̏�Ԃ�I�u�W�F�N�g���Ǘ�����N���X
*/
class SelectStateManager
{
public:

	enum CAT_CURSOR_STATE
	{
		DATA1,        //!< �f�[�^�P�ɃJ�[�\��������Ƃ�
		DATA2,        //!< �f�[�^�Q�ɃJ�[�\��������Ƃ�
		DATA3         //!< �f�[�^�R�ɃJ�[�\��������Ƃ�
	};

	enum MINI_CURSOR_STATE
	{
		CONTINUE,     //!< ��������
		NEWGAME,      //!< ���߂���
		BACK          //!< �߂�
	};

	SelectStateManager();
	~SelectStateManager();

	/**
	* @brief �C���X�^���X�𐶐�����֐�
	*/
	void Initialize();

	/**
	* @brief �C���X�^���X��j������֐�
	*/
	void Finalize();

	/**
	* @brief �I�u�W�F�N�g��o�^����֐�
	* @param �o�^�������h���N���X�̃|�C���^
	*/
	void RegisterObject(Object*);

	/**
	* @brief �I�u�W�F�N�g���������֐�
	*/
	void ReleaseObject();

	/**
	* @brief ����֐�
	*/
	void Update();

	/**
	* @brief �`��֐�
	*/
	void Render();

private:

	std::vector<Object*>     m_pObjectVec;				 //!< Object�N���X�|�C���^��Vector�z��
	int                      m_catCursorState;           //!< �L�^�J�[�\���i�f�[�^�P���Q���R�̍��ځj�̏�������
	int                      m_miniCursorState;          //!< ��������A���߂���A�폜�̍��ڂ̏�������
												
};
