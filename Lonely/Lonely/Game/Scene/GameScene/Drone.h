/**
* @file Drone.h
* @brief Drone�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include "../../../GameLib/ObjectManager/Object3DBase.h"
#include "../../../GameLib/FBX/FBX.h"

/**
* @brief �v���C���[�֌W�̏������܂Ƃ߂��N���X
*/
class Drone : public Object3DBase
{
public:

	Drone();
	~Drone();

	/**
	* @brief �������֐�
	*/
	bool Initialize();
	/**
	* @brief ����֐�
	*/
	void Finalize();

	/**
	* @brief �X�V���s���֐�
	*/
	void Update();
	/**
	* @brief �`����s���֐�
	*/
	void Render();

private:

	// ���C�g�̐ݒ�
	void SetLight(void);
	// �v���C���[�̍X�V
	void UpdatePlayer(void);

private:

	FbxModel	m_fbxModel;
	Model		m_shpere;
	D3DXVECTOR3 m_playerPos;
	float		m_playerRadius;
	float		m_playerSpeed;
};
