/**
* @file	DirectX.h
* @brief DirectX�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

/**
* @brief ����������s���}�N��
*/
#define SAFE_RELEASE(x) { if(x) { (x)->Release(); (x) = NULL; } }

/** 
* @brief DirectX�֌W�̏�����������܂Ƃ߂��N���X
*/
class DirectX
{
public:

	/** 
	* @brief �`�惂�[�h
	*/
	enum ERenderMode
	{
		Normal,		//!< �������� 
		Add,		//!< ���Z 
		Subtract,	//!< ���Z 
		Multiple,	//!< ��Z 
	};

	DirectX();
	~DirectX();

	/** 
	* @brief DirectX�̏��������s���֐�
	* @param �E�B���h�E�n���h��
	* @param �E�B���h�E�̉���
	* @param �E�B���h�E�̏c��
	* @param �E�B���h�E���t���X�N���[�����ǂ���
	* @return ������������������TRUE
	*/
	bool Initialize(HWND hWnd, int width, int height, bool isFullscreen);
	
	/** 
	* @brief DirectX�̏I���������s���֐�
	*/
	void Finalize();

	/** 
	* @brief �`��V�[���̊J�n��錾����֐�
	*/
	void BeginRenderScene();

	/** 
	* @brief �`��V�[���̏I����錾����֐�
	*/
	void EndRenderScene();

	/** 
	* @brief �o�b�N�o�b�t�@�̃N���A���s���֐�
	* @param �X�e���V���A�^�[�Q�b�g�A�[�x�o�b�t�@�̑g�ݍ��킹
	* @param �N���A�������J���[
	* @param �[�x�o�b�t�@���N���A����Z�l�i0����P�܂Łj
	* @param �X�e���V���o�b�t�@���N���A����l
	*/
	void ClearBackBuffer(DWORD target, D3DCOLOR color, float depth = 1.0f, DWORD stencil = 0);
	
	/** 
	* @brief ��ʂ̃t���b�v���s���֐�
	*/
	void FlipDisp();

	/** 
	* @brief �����̕`��X�e�[�g�̐ݒ���s���֐�
	*/
	void SetDefaultRenderState();

	/** 
	* @brief �`��X�e�[�g�̐ݒ���s���֐�
	* @param �ǂ̕`��X�e�[�g���[�h�ɂ��邩
	* @param ���������\�Ƃ��邩
	*/
	void SetRenderMode(ERenderMode mode, bool enableAlpha);

	/** 
	* @brief Direct3D�I�u�W�F�N�g�̎擾���s���֐�
	* @return Direct3D�I�u�W�F�N�g�̃A�h���X
	*/
	IDirect3D9* GetDirect3D() { return m_pD3D; }

	/** 
	* @brief Direct3DDevice�I�u�W�F�N�g�̎擾���s���֐�
	* @return Direct3DDevice�I�u�W�F�N�g�̃A�h���X
	*/
	IDirect3DDevice9* GetDirect3DDevice() { return m_pDevice; }

private:

	IDirect3D9* m_pD3D;
	IDirect3DDevice9*		m_pDevice;
	D3DPRESENT_PARAMETERS	m_d3dpp;
};
