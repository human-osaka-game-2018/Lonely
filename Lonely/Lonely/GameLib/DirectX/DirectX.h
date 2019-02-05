/**
* @file	DirectX.h
* @brief DirectXクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

/**
* @brief 解放処理を行うマクロ
*/
#define SAFE_RELEASE(x) { if(x) { (x)->Release(); (x) = NULL; } }

/** 
* @brief DirectX関係の処理や情報ををまとめたクラス
*/
class DirectX
{
public:

	/** 
	* @brief 描画モード
	*/
	enum ERenderMode
	{
		Normal,		//!< 書き込み 
		Add,		//!< 加算 
		Subtract,	//!< 減算 
		Multiple,	//!< 乗算 
	};

	DirectX();
	~DirectX();

	/** 
	* @brief DirectXの初期化を行う関数
	* @param ウィンドウハンドル
	* @param ウィンドウの横幅
	* @param ウィンドウの縦幅
	* @param ウィンドウがフルスクリーンかどうか
	* @return 初期化が完了したらTRUE
	*/
	bool Initialize(HWND hWnd, int width, int height, bool isFullscreen);
	
	/** 
	* @brief DirectXの終了処理を行う関数
	*/
	void Finalize();

	/** 
	* @brief 描画シーンの開始を宣言する関数
	*/
	void BeginRenderScene();

	/** 
	* @brief 描画シーンの終了を宣言する関数
	*/
	void EndRenderScene();

	/** 
	* @brief バックバッファのクリアを行う関数
	* @param ステンシル、ターゲット、深度バッファの組み合わせ
	* @param クリアしたいカラー
	* @param 深度バッファをクリアするZ値（0から１まで）
	* @param ステンシルバッファをクリアする値
	*/
	void ClearBackBuffer(DWORD target, D3DCOLOR color, float depth = 1.0f, DWORD stencil = 0);
	
	/** 
	* @brief 画面のフリップを行う関数
	*/
	void FlipDisp();

	/** 
	* @brief 初期の描画ステートの設定を行う関数
	*/
	void SetDefaultRenderState();

	/** 
	* @brief 描画ステートの設定を行う関数
	* @param どの描画ステートモードにするか
	* @param 透明化を可能とするか
	*/
	void SetRenderMode(ERenderMode mode, bool enableAlpha);

	/** 
	* @brief Direct3Dオブジェクトの取得を行う関数
	* @return Direct3Dオブジェクトのアドレス
	*/
	IDirect3D9* GetDirect3D() { return m_pD3D; }

	/** 
	* @brief Direct3DDeviceオブジェクトの取得を行う関数
	* @return Direct3DDeviceオブジェクトのアドレス
	*/
	IDirect3DDevice9* GetDirect3DDevice() { return m_pDevice; }

private:

	IDirect3D9*             m_pD3D;
	IDirect3DDevice9*		m_pDevice;
	D3DPRESENT_PARAMETERS	m_d3dpp;
};
