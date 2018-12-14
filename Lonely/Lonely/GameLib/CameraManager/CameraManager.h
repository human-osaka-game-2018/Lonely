/**
* @file CameraManager.h
* @brief CameraManager�N���X�̃w�b�_
* @author shion-sagawa
*/

#pragma once

#include <windows.h>
#include <tchar.h>
#include <map>
#include <d3dx9.h>
#include "CameraBase.h"

/**
* @brief �J������o�^���A�����n�����肷��N���X
*/
class CameraManager
{
public:

	CameraManager();
	~CameraManager();

	/**
	* @brierf ���������s���֐�
	*/
	void Initialize();

	/**
	* @brief ������s���֐�
	*/
	void Finalize();

	/**
	* @brief �X�V���s���֐�
	*/
	void Update();

	/**
	* @brief �J������ύX����֐�
	* @param �ύX�������J�����N���X�̃A�h���X
	*/
	void  ChangeCamera(CameraBase* pCamera);

private:

	CameraBase * m_pCamera;     //!< �J����ID�̃}�b�v�z��
};
