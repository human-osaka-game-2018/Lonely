/**
* @file TestCamera.h
* @brief TestCamera�N���X�̃w�b�_�t�@�C��
* @author ����
*/

#pragma once

#include <d3dx9math.h>
#include "../../../../GameLib/CameraManager/CameraBase.h"

/**
* @brief �Q�[���V�[���̃N���X
*/
class TestCamera : public CameraBase
{
public:

	TestCamera();
	~TestCamera();

	/**
	* @brief �������֐�
	*/
	void Initialize();

	/**
	* @brief ����֐�
	*/
	void Finalize();

	/**
	* @brief ����֐�
	*/
	void Update();

private:



	D3DXMATRIXA16 m_matProjection;    //!< �v���W�F�N�V�����s��
	float m_perspective;              //!< �J�����̎���p��ς��邽�߂̕ϐ�
	D3DXVECTOR3 m_position;           //!< �J�����̈ʒu
	D3DXVECTOR3 m_lookAt;             //!< �����_�̈ʒu
	D3DXVECTOR3 m_rotation;           //!< �J�����̉�]�p�x
};
