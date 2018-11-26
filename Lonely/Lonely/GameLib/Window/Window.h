/**
* @file	Window.h
* @brief Windowクラスのヘッダファイル
* @author 佐川　嗣苑
*/
#pragma once

#include <Windows.h>

/**
* @brief ウィンドウ関係の処理をまとめたクラス
*/
class Window
{
public:

	Window();
	~Window();

	/**
	* @brief ウィンドウ生成を行う関数
	* @param ウィンドウの名前
	* @param ウィンドウの横幅
	* @param ウィンドウの縦幅
	*/
	bool Create(const wchar_t* pName, int width, int height);

	/**
	* @brief メッセージの更新
	*/
	bool UpdateMessage();

	/**
	* @brief 終了通知が来ているか
	*/
	bool IsQuitMessage() { return m_isQuitMessage; }

	/**
	* @briefウィンドウハンドルの取得
	*/
	HWND GetHandle() { return m_hWnd; }

	/**
	* @briefウィンドウモードを変更する関数
	*/
	//void ChangeDisplayMode();

	/**
	* @brief ウィンドウのパラメータを初期化する関数
	*/
	//void InitPresentParameters();

private:

	/** ウィンドウハンドル */
	HWND m_hWnd;	

	/** ウィンドウかフルスクリーンか */
	bool m_isWindowMode;

	/** 終了通知が来ているか */
	bool m_isQuitMessage;

	/** ウィンドウの横幅 */
	int  m_width;

	/** ウィンドウの縦幅 */
	int  m_height;
};