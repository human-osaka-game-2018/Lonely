/**
* @file VertexBuffer.h
* @brief VertexBufferクラスのヘッダファイル
* @author 佐川 嗣苑
*/

#pragma once

#include "d3d9.h"

/**
* @brief バーテックスバッファの処理や情報をまとめたクラス
*/
class VertexBuffer
{
public:

	VertexBuffer();
	~VertexBuffer();

	/**
	* @brief バッファの生成を行う関数
	* @param 
	* @param 
	* @return 
	*/
	bool Create(UINT size, const void* pData = NULL);
	/** 
	* @brief バッファの解放を行う関数
	*/
	void Finalize();

	/** 
	* @brief バッファの取得を行う関数
	*/
	IDirect3DVertexBuffer9*	GetBuffer() { return m_pBuffer; }

private:

	IDirect3DVertexBuffer9 * m_pBuffer;
};