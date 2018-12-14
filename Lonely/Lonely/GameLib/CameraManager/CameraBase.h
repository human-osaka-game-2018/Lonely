/**
* @file CameraBase.h
* @brief CameraBase�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

/**
* @brief �J�����̊��N���X
*/
class CameraBase
{
public:

	CameraBase();
	virtual~CameraBase();

	/**
	* @brief ���������s���֐�
	*/
	virtual void Initialize();

	/**
	* @brief ������s���֐�
	*/
	virtual void Finalize();

	/**
	* @brief ����֐�
	*/
	virtual void Update();

protected:

};
