/**
* @file	GameLib.h
* @brief GameLibクラスのヘッダファイル
* @author 佐川　嗣苑
*/

#pragma once

#include "DirectX\DirectX.h"
#include "FBX\FBX.h"
#include "Window\Window.h"
#include "Input\Input.h"
#include "Font\Font.h"
#include "SceneManager\SceneManager.h"
#include "ObjectManager\ObjectManager.h"

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

public:

	/**GameLibの実体*/
	static GameLib Instance;

private:

	Window		   m_window;
	DirectX		   m_directX;
	Input		   m_input;
	Font		   m_font;
	FbxModel	   m_fbx;
	SceneManager   m_sceneManager;
	ObjectManager  m_objectManager;

};

#define	DEBUGFONT		(GameLib::Instance.GetDebugFont())
#define	INPUT			(GameLib::Instance.GetInput())
#define	SCENEMANAGER	(GameLib::Instance.GetSceneManager())