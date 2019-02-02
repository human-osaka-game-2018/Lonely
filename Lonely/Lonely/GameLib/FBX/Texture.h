/**
* @file Texture.h
* @brief Textureクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "d3d9.h"

/**
* @brief テクスチャ関係の処理や情報をまとめたクラス
*/
class Texture
{
public:

	Texture();
	~Texture();

	/** 
	* @brief テクスチャーの読み込み
	*/
	bool Load(const char* pFileName);

	/** 
	* @brief テクスチャーの読み込みを行う関数
	* @param 
	* @param 
	*/
	bool CreateFromMemory(const void* pData, UINT size);
	
	/** 
	* @brief テクスチャーの解放を行う関数
	*/
	void Finalize();

	/** 
	* @brief 横幅の取得を行う関数
	*/
	UINT GetWidth() const { return m_width; }
	
	/** 
	* @brief 縦幅の取得を行う関数
	*/
	UINT GetHeight() const { return m_height; }

	/** 
	* @brief 画像の横幅の取得を行う関数
	*/
	UINT GetSrcWidth() const { return m_srcWidth; }

	/** 
	* @brief 画像の縦幅の取得を行う関数
	*/
	UINT GetSrcHeight() const { return m_srcHeight; }

	/** 
	* @brief D3Dテクスチャ―の取得を行う関数
	*/
	IDirect3DTexture9* GetD3DTexture() { return m_pTexture; }

private:

	UINT				m_width;		// テクスチャーの幅
	UINT				m_height;		// テクスチャーの高さ
	UINT				m_srcWidth;		// 画像の幅
	UINT				m_srcHeight;	// 画像の高さ
	IDirect3DTexture9*	m_pTexture;		// 生成したテクスチャーのポインタ

};
