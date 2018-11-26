/**
* @file IndexBuffer.h
* @brief IndexBuffer�N���X�̃w�b�_�t�@�C��
* @author ���� �k��
*/

#pragma once

#include "d3d9.h"
//#include "..\GameLib.h"

/** 
* @brief IndexBuffer�֌W�̏���������܂Ƃ߂��N���X
*/
class IndexBuffer
{
public:

	IndexBuffer();
	~IndexBuffer();

	/** 
	* @brief �o�b�t�@�̐������s���֐�
	* @param 
	* @param 
	*/
	bool Create(UINT size, const UINT16* pIndeces = NULL);

	/** 
	* @brief �o�b�t�@�̉�����s���֐�
	*/
	void Finalize();

	/** 
	* @brief �o�b�t�@�̎擾���s���֐�
	*/
	IDirect3DIndexBuffer9*	GetBuffer() { return m_pBuffer; }

private:

	IDirect3DIndexBuffer9 * m_pBuffer;
};
