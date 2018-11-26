/**
* @file	Font.h
* @brief Font�N���X�̃w�b�_�t�@�C��
* @author ����@�k��
*/

#pragma once

//#include "../GameLib.h"
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>
#undef DrawText

/** 
* @brief Font�֌W�̏������܂Ƃ߂��N���X
*/
class Font
{
public:

	Font();
	~Font();

	/** 
	* @brief �t�H���g�𐶐�����֐�
	* @param �t�H���g�̃T�C�Y
	* @return �t�H���g���쐬�ł��Ă�����TRUE
	*/
	bool Initialize(int size = 14);

	/** 
	* @brief�t�H���g��j������֐�
	*/
	void Finalize();

	/** 
	* @brief �t�H���g�̍������擾����֐�
	* @return �t�H���g�̍���
	*/
	int GetHeight();

	/** 
	* @brief ���b�Z�[�W�̕\�����s���֐�
	* @param �`�悵�����͈͂̉���
	* @param �`�悵�����͈͂̏c��
	* @param �t�H���g�̃J���[
	* @param �`�悵�����t�H���g�̓��e
	*/
	void DrawText(int X, int Y, D3DCOLOR color, const char* pText);
	
	/** 
	* @brief ���b�Z�[�W�̕\�����s���֐�
	* @param �`�悵�����͈͂̉���
	* @param �`�悵�����͈͂̏c��
	* @param �t�H���g�̃J���[
	* @param �t�H���g�̃t�H�[�}�b�g
	*/
	void DrawFormatText(int X, int Y, D3DCOLOR color, const char* pFormat, ...);

private:

	/** �t�H���g�̍�����ۑ�����ϐ� */
	int			m_fontSize;

	/** �t�H���g�̏������� */
	ID3DXFont*	m_pFont;
};