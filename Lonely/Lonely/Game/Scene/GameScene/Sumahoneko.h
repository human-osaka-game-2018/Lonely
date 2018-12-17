
/**
* @file Sumahoneko.h
* @brief Sumahoneko�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include "../../../GameLib/ObjectManager/Object3DBase.h"
#include "../../../GameLib/FBX/FBX.h"
#include "SharedInformation/SharedInformation.h"

/**
* @brief �v���C���[�֌W�̏������܂Ƃ߂��N���X
*/
class Sumahoneko : public Object3DBase
{
public:

	Sumahoneko();
	~Sumahoneko();

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
	D3DXVECTOR3 m_position;
	float		m_playerRadius;
	float		m_playerSpeed;
	float       m_playerDirection;

	SharedInformation* m_pSharedInformation;

	FbxModel    m_fbxStage;//���͂Ƃ肠�������̃N���X�ɒu���Ă��邾��
};
