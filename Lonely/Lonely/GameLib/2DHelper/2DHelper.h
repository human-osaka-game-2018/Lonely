///**
//* @file 2DHelper.h
//* @brief 2DHelper�N���X�̃w�b�_�t�@�C��
//* @author shion-sagawa
//*/
//
#pragma once

#include <windows.h>
//
//#include "../DirectX/DirectX.h"
//#include "../FBX/Texture.h"
//
//
//#define FVF_SIMPLE_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
//#define FVF_SIMPLE_TEX_2D   (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//
//

// �V���v���ȃe�N�X�`���\�t�����_���
struct Simple2DVertex
{
	float x, y, z;
	float rhw;
	DWORD color;
	float u, v;
};

/**
* @brief �QD�̃Q�[���̂悭�g�p���鏈�����܂Ƃ߂��N���X
*/
class Helper2D
{
public:

	Helper2D();
	~Helper2D();

	/**
	* @brief ���S�_���牡���A�c�����g���ċ�`�����֐�
	* @param ���_���
	* @param ���S�_��X���W
	* @param ���S�_��Y���W
	* @param ���S�_����̉���
	* @param ���S�_����̏c��
	* @param ��`�̉E��TU�i�f�t�H���g�Ȃ�P�����j
	* @param ��`�̉���TV�i�f�t�H���g�Ȃ�P�����j
	* @param ��`�̍���TU�i�f�t�H���g�Ȃ�O�����j
	* @param ��`�̏��TV�i�f�t�H���g�Ȃ�O�����j
	*/
	void SetVerticesFromCenterType(Simple2DVertex* vertices, float posCenterX, float posCenterY, float posWidthFromCenter, float posHeightFromCenter, float rightTU = 1.0f, float bottomTV = 1.0f, float leftTU = 0.0f, float topTV = 0.0f);

	/**
	* @brief ���㒸�_���牡���A�c�����g���ċ�`�����֐�
	* @param ���_���
	* @param ���㒸�_��X���W
	* @param ���㒸�_��Y���W
	* @param ��`�̉���
	* @param ��`�̏c��
	* @param ��`�̉E��TU�i�f�t�H���g�Ȃ�P�����j
	* @param ��`�̉���TV�i�f�t�H���g�Ȃ�P�����j
	* @param ��`�̍���TU�i�f�t�H���g�Ȃ�O�����j
	* @param ��`�̏��TV�i�f�t�H���g�Ȃ�O�����j
	*/
	void SetVerticesFromLeftTopType(Simple2DVertex* vertices, float posLeftTopX, float posLeftTopY, float rectWidth, float rectHeight, float rightTU = 1.0f, float bottomTV =1.0f, float leftTU = 0.0f, float topTV = 0.0f);

	/**
	* @brief ��`�S���_�̐F����ς���֐�
	* @param ���_�̐擪�A�h���X
	* @param �ς������F���iARGB�j 
	*/
	void SetVerticesColor(Simple2DVertex* vertices, DWORD color);

	/**
	* @brief �P���_�̐F����ς���֐�
	* @param ���_�̐擪�A�h���X
	* @param �ς������F���iARGB�j
	*/
	void SetVertexColor(Simple2DVertex* vertices, DWORD color);

private:

};
