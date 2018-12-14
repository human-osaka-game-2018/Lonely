/**
* @file Texture.h
* @brief Texture�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include "d3d9.h"

/**
* @brief �e�N�X�`���֌W�̏���������܂Ƃ߂��N���X
*/
class Texture
{
public:

	Texture();
	~Texture();

	/** 
	* @brief �e�N�X�`���[�̓ǂݍ���
	*/
	bool Load(const char* pFileName);

	/** 
	* @brief �e�N�X�`���[�̓ǂݍ��݂��s���֐�
	* @param 
	* @param 
	*/
	bool CreateFromMemory(const void* pData, UINT size);
	
	/** 
	* @brief �e�N�X�`���[�̉�����s���֐�
	*/
	void Finalize();

	/** 
	* @brief �����̎擾���s���֐�
	*/
	UINT GetWidth() const { return m_width; }
	
	/** 
	* @brief �c���̎擾���s���֐�
	*/
	UINT GetHeight() const { return m_height; }

	/** 
	* @brief �摜�̉����̎擾���s���֐�
	*/
	UINT GetSrcWidth() const { return m_srcWidth; }

	/** 
	* @brief �摜�̏c���̎擾���s���֐�
	*/
	UINT GetSrcHeight() const { return m_srcHeight; }

	/** 
	* @brief D3D�e�N�X�`���\�̎擾���s���֐�
	*/
	IDirect3DTexture9* GetD3DTexture() { return m_pTexture; }

private:

	UINT				m_width;		// �e�N�X�`���[�̕�
	UINT				m_height;		// �e�N�X�`���[�̍���
	UINT				m_srcWidth;		// �摜�̕�
	UINT				m_srcHeight;	// �摜�̍���
	IDirect3DTexture9*	m_pTexture;		// ���������e�N�X�`���[�̃|�C���^

};
