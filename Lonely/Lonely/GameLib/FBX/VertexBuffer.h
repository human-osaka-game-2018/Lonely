/**
* @file VertexBuffer.h
* @brief VertexBuffer�N���X�̃w�b�_�t�@�C��
* @author ���� �k��
*/

#pragma once

#include "d3d9.h"

/**
* @brief �o�[�e�b�N�X�o�b�t�@�̏���������܂Ƃ߂��N���X
*/
class VertexBuffer
{
public:

	VertexBuffer();
	~VertexBuffer();

	/**
	* @brief �o�b�t�@�̐������s���֐�
	* @param 
	* @param 
	* @return 
	*/
	bool Create(UINT size, const void* pData = NULL);
	/** 
	* @brief �o�b�t�@�̉�����s���֐�
	*/
	void Finalize();

	/** 
	* @brief �o�b�t�@�̎擾���s���֐�
	*/
	IDirect3DVertexBuffer9*	GetBuffer() { return m_pBuffer; }

private:

	IDirect3DVertexBuffer9 * m_pBuffer;
};