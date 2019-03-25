/**
* @file	GameLib.h
* @brief GameLibクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "DirectX\DirectX.h"
#include "FBX\FBX.h"
#include "Window\Window.h"
#include "Input\Input.h"
#include "Font\Font.h"
#include "SceneManager\SceneManager.h"
#include "ObjectManager\ObjectManager.h"
#include "CollisionManager\CollisionManager.h"
#include "CameraManager\CameraManager.h"
#include "Sprite\Sprite.h"
#include "2DHelper\2DHelper.h"
#include "DXInput\DXInput.h"
#include "TexStorage\TexStorage.h"

#include "../SoundLib/Include/SoundsManager.h"
#include "../SoundLib/Include/SoundLibCWrapper.h"


/**
* @brief 解放を行うマクロ
*/
#define SAFE_DELETE(x)			{ if(x) { delete (x); (x) = NULL; } }

/**
* @brief 解放を行うマクロ
*/
#define SAFE_DELETE_ARRAY(x)	{ if(x) { delete[] (x); (x) = NULL; } }

/**
* @brief ゲーム関係の処理を行うライブラリのクラス
*/
class GameLib
{
public:

	GameLib();
	~GameLib();

	/**
	* @brief DirectXLibの初期化を行う関数
	* @param pName ウィンドウの名前
	* @param width ウィンドウの横幅
	* @param height ウィンドウの縦幅
	* @param isFullscreen ウィンドウがフルスクリーンかどうか
	* @return GameLibが問題なく初期化できていたらTRUE
	*/
	bool Initialize(const wchar_t* pName, int width, int height, bool isFullscreen);

	/**
	* @brief DirectXLibの解放を行う関数
	*/
	void Finalize();

	/**
	* @brief ゲームのメインループ処理を行う関数
	*/
	void MainLoop();

	/**
	* @brief ウィンドウの取得を行う関数
	*/
	Window* GetWindow() { return &m_window; }

	/**
	* @brief DirectXの取得を行う関数
	*/
	DirectX* GetDirectX() { return &m_directX; }

	/** 
	* @brief Direct3DDeviceの取得を行う関数
	*/
	IDirect3DDevice9* GetDirect3DDevice() { return m_directX.GetDirect3DDevice(); }

	/** 
	* @brief Fontの取得を行う関数
	*/
	Font* GetDebugFont() { return &m_font; }

	/**
	* @brief Inputの取得を行う関数
	*/
	Input* GetInput() { return &m_input; }

	/** 
	* @brief SceneManagerの取得を行う関数
	*/
	SceneManager* GetSceneManager() { return &m_sceneManager; }

	/**
	* @brief ObjectManagerの取得を行う関数
	*/
	ObjectManager* GetObjectManager() { return &m_objectManager; }

	/**
	* @brief CollisionManagerの取得を行う関数
	*/
	CollisionManager* GetCollisionManager() { return &m_collisionManager; }

	/**
	* @brief CameraManagerの取得を行う関数
	*/
	CameraManager* GetCameraManager() { return &m_cameraManager; }


	/**
	* @brief Helper2Dの取得を行う関数
	*/
	Helper2D* GetHelper2D() { return &m_helper2D; }

	/**
	* @brief DirectInputの取得を行う関数
	*/
	DXInput* GetDXInput() { return &m_dxInput; }

	/**
	* @brief TexStorageの取得を行う関数
	*/
	TexStorage* GetTexStorage() { return &m_texStorage; }

	/**
	* @brief SoundsManagerの取得を行う関数
	*/
	SoundLib::SoundsManager* GetSoundsManager() { return &m_soundsManager; }

public:

	/**GameLibの実体*/
	static GameLib Instance;

private:

	Window		            m_window;
	DirectX		            m_directX;
	Input		            m_input;
	Font		            m_font;
	FbxModel	            m_fbx;
	SceneManager            m_sceneManager;
	ObjectManager           m_objectManager;
	CollisionManager        m_collisionManager;
	CameraManager           m_cameraManager;
	Helper2D                m_helper2D;
	DXInput                 m_dxInput;
	TexStorage              m_texStorage;
	SoundLib::SoundsManager m_soundsManager;
};

#define	DEBUGFONT		(GameLib::Instance.GetDebugFont())
#define	INPUT			(GameLib::Instance.GetInput())
#define	SCENEMANAGER	(GameLib::Instance.GetSceneManager())
#define WINDOW          (GameLib::Instance.GetWindow())
#define DIRECT_3DDEVICE (GameLib::Instance.GetDirect3DDevice())
#define HELPER_2D       (GameLib::Instance.GetHelper2D())
#define DIRECT_INPUT    (GameLib::Instance.GetDXInput())
