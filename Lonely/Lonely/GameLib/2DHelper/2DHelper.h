/**
* @file 2DHelper.h
* @brief 2DHelper�N���X�̃w�b�_�t�@�C��
* @author ���� �k��
*/

#pragma once

#include "../DirectX/DirectX.h"
#include "../FBX/Texture.h"


#define FVF_SIMPLE_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#define FVF_SIMPLE_TEX_2D   (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)


// �V���v���ȃe�N�X�`���\�t�����_���
struct Simple2DVertex
{
	float x, y, z;
	float rhw;
	DWORD color;
	float u, v;
};


/**	
* @brief �X�v���C�g�N���X
*/
class Sprite
{
public:
	Sprite();
	~Sprite();

	/** 
	* @brief �X�v���C�g�̐���
	* @param 
	* @return
	*/
	bool Create(const char* pTexturePath = NULL);
	
	/** 
	* @brief �X�v���C�g�̉��
	*/
	void Finalize();


	/** 
	* @brief �X�v���C�g�`��
	*/
	void Render();

	/** 
	* @brief �X�v���C�g�̍��W�ݒ�
	* @param
	* @param 
	*/
	void SetPos(float x, float y);

	/** 
	* @brief �X�v���C�g�̃T�C�Y�ݒ�
	* @param 
	* @param 
	*/
	void SetSize(float width, float height);

	/** 
	* @brief �X�v���C�g�̉�]�ݒ�
	* @param 
	*/
	void SetRotation(float angle);

	/** 
	* @brief �X�v���C�g�̌��_�ݒ�
	* @param 
	* @param
	*/
	void SetOrigin(float x, float y);

	/** 
	* @brief �X�v���C�g��UV�ݒ�
	* @param 
	* @param
	* @param
	*/
	void SetUV(int u, int v, int width, int height);

	/** 
	* @brief �X�v���C�g�̃J���[�ݒ�
	* @param 
	*/
	void SetColor(D3DCOLOR color);

	/** 
	* @brief �X�v���C�g�̍��W�擾
	*/
	float GetX() const { return m_x; }

	/**
	* @brief �X�v���C�g�̍��W�擾
	*/
	float GetY() const { return m_y; }

	/** 
	* @brief �X�v���C�g�̃T�C�Y�擾
	*/
	float GetWidth() const { return m_width; }

	/**
	* @brief �X�v���C�g�̃T�C�Y�擾
	*/
	float GetHeight() const { return m_height; }

	/** 
	* @brief �X�v���C�g�̉�]�ݒ�
	*/
	float GetRotation() const { return m_angle; }

	/** 
	* @brief �X�v���C�g�̌��_�ݒ�
	*/
	float GetOriginX() const { return m_cx; }

	/**
	* @brief �X�v���C�g�̌��_�ݒ�
	*/
	float GetOriginY() const { return m_cy; }

	/** 
	* @brief �X�v���C�g��UV�擾
	*/
	float GetU() const { return m_u1; }
	float GetV() const { return m_v1; }
	float GetUWidth() const { return m_u2 - m_u1; }
	float GetVHeight() const { return m_v2 - m_v1; }

	/** 
	* @brief �X�v���C�g�̃J���[�ݒ�
	*/
	D3DCOLOR GetColor() const { return m_color; }

	/** 
	* @brief �e�N�X�`���[�̎擾
	*/
	Texture* GetTexture(void) { return &m_texture; }

private:
	float		m_x, m_y;
	float		m_width, m_height;
	float		m_u1, m_v1;
	float		m_u2, m_v2;
	float		m_angle;
	float		m_cx, m_cy;
	D3DCOLOR	m_color;
	Texture		m_texture;
};

