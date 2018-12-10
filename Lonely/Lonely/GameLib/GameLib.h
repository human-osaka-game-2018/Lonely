/**
* @file	GameLib.h
* @brief GameLib�N���X�̃w�b�_�t�@�C��
* @author ����@�k��
*/

#pragma once

#include "DirectX\DirectX.h"
#include "FBX\FBX.h"
#include "Window\Window.h"
#include "Input\Input.h"
#include "Font\Font.h"
#include "SceneManager\SceneManager.h"
#include "ObjectManager\ObjectManager.h"
#include "CameraManager\CameraManager.h"
#include "Sprite\Sprite.h"
#include "2DHelper\2DHelper.h"
#include "DXInput\DXInput.h"

/**
* @brief ������s���}�N��
*/
#define SAFE_DELETE(x)			{ if(x) { delete (x); (x) = NULL; } }

/**
* @brief ������s���}�N��
*/
#define SAFE_DELETE_ARRAY(x)	{ if(x) { delete[] (x); (x) = NULL; } }

/**
* @brief �Q�[���֌W�̏������s�����C�u�����̃N���X
*/
class GameLib
{
public:

	GameLib();
	~GameLib();

	/**
	* @brief DirectXLib�̏��������s���֐�
	* @param pName �E�B���h�E�̖��O
	* @param width �E�B���h�E�̉���
	* @param height �E�B���h�E�̏c��
	* @param isFullscreen �E�B���h�E���t���X�N���[�����ǂ���
	* @return GameLib�����Ȃ��������ł��Ă�����TRUE
	*/
	bool Initialize(const wchar_t* pName, int width, int height, bool isFullscreen);

	/**
	* @brief DirectXLib�̉�����s���֐�
	*/
	void Finalize();

	/**
	* @brief �Q�[���̃��C�����[�v�������s���֐�
	*/
	void MainLoop();

	/**
	* @brief �E�B���h�E�̎擾���s���֐�
	*/
	Window* GetWindow() { return &m_window; }

	/**
	* @brief DirectX�̎擾���s���֐�
	*/
	DirectX* GetDirectX() { return &m_directX; }

	/** 
	* @brief Direct3DDevice�̎擾���s���֐�
	*/
	IDirect3DDevice9* GetDirect3DDevice() { return m_directX.GetDirect3DDevice(); }

	/** 
	* @brief Font�̎擾���s���֐�
	*/
	Font* GetDebugFont() { return &m_font; }

	/**
	* @brief Input�̎擾���s���֐�
	*/
	Input* GetInput() { return &m_input; }

	/** 
	* @brief SceneManager�̎擾���s���֐�
	*/
	SceneManager* GetSceneManager() { return &m_sceneManager; }

	/**
	* @brief ObjectManager�̎擾���s���֐�
	*/
	ObjectManager* GetObjectManager() { return &m_objectManager; }


	/**
	* @brief CameraManager�̎擾���s���֐�
	*/
	CameraManager* GetCameraManager() { return &m_cameraManager; }


	/**
	* @brief Helper2D�̎擾���s���֐�
	*/
	Helper2D* GetHelper2D() { return &m_helper2D; }

	/**
	* @brief DirectInput�̎擾���s���֐�
	*/
	DXInput* GetDXInput() { return &m_dxInput; }

public:

	/**GameLib�̎���*/
	static GameLib Instance;

private:

	Window		   m_window;
	DirectX		   m_directX;
	Input		   m_input;
	Font		   m_font;
	FbxModel	   m_fbx;
	SceneManager   m_sceneManager;
	ObjectManager  m_objectManager;
	CameraManager  m_cameraManager;
	Helper2D       m_helper2D;
	DXInput        m_dxInput;

};

#define	DEBUGFONT		(GameLib::Instance.GetDebugFont())
#define	INPUT			(GameLib::Instance.GetInput())
#define	SCENEMANAGER	(GameLib::Instance.GetSceneManager())
#define WINDOW          (GameLib::Instance.GetWindow())
#define DIRECT_3DDEVICE (GameLib::Instance.GetDirect3DDevice())
#define HELPER_2D       (GameLib::Instance.GetHelper2D())
#define DIRECT_INPUT    (GameLib::Instance.GetDXInput())
