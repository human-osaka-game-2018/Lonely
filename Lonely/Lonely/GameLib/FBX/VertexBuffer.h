/**
* @file VertexBuffer.h
* @brief VertexBuffer�N���X�̃w�b�_�t�@�C��
* @author ���� �k��
*/

#pragma once

//#include "../../GameLib/GameLib.h"
#include "d3d9.h"

/**
* @brief �o�[�e�b�N�X�o�b�t�@�̏���������܂Ƃ߂��N���X
*/
class VertexBuffer
{
public:

	VertexBuffer(void);
	~VertexBuffer(void);

	/**
	* @brief �o�b�t�@�̐������s���֐�
	* @param 
	* @param 
	*/
	bool Create(UINT size, const void* pData = NULL);
	/** 
	* @brief �o�b�t�@�̉�����s���֐�
	*/
	void Finalize(void);

	/** 
	* @brief �o�b�t�@�̎擾���s���֐�
	*/
	IDirect3DVertexBuffer9*	GetBuffer(void) { return m_pBuffer; }

private:

	IDirect3DVertexBuffer9 * m_pBuffer;
};