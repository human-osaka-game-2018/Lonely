/**
* @file	Font.h
* @brief Fontクラスのヘッダファイル
* @author 佐川　嗣苑
*/

#pragma once

//#include "../GameLib.h"
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>
#undef DrawText

/** 
* @brief Font関係の処理をまとめたクラス
*/
class Font
{
public:

	Font();
	~Font();

	/** 
	* @brief フォントを生成する関数
	* @param フォントのサイズ
	* @return フォントを作成できていたらTRUE
	*/
	bool Initialize(int size = 14);

	/** 
	* @briefフォントを破棄する関数
	*/
	void Finalize();

	/** 
	* @brief フォントの高さを取得する関数
	* @return フォントの高さ
	*/
	int GetHeight();

	/** 
	* @brief メッセージの表示を行う関数
	* @param 描画したい範囲の横幅
	* @param 描画したい範囲の縦幅
	* @param フォントのカラー
	* @param 描画したいフォントの内容
	*/
	void DrawText(int X, int Y, D3DCOLOR color, const char* pText);
	
	/** 
	* @brief メッセージの表示を行う関数
	* @param 描画したい範囲の横幅
	* @param 描画したい範囲の縦幅
	* @param フォントのカラー
	* @param フォントのフォーマット
	*/
	void DrawFormatText(int X, int Y, D3DCOLOR color, const char* pFormat, ...);

private:

	/** フォントの高さを保存する変数 */
	int			m_fontSize;

	/** フォントの情報を持つ */
	ID3DXFont*	m_pFont;
};