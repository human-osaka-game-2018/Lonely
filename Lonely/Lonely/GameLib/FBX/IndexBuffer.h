/**
* @file IndexBuffer.h
* @brief IndexBufferクラスのヘッダファイル
* @author 佐川 嗣苑
*/

#pragma once

#include "d3d9.h"
//#include "..\GameLib.h"

/** 
* @brief IndexBuffer関係の処理や情報をまとめたクラス
*/
class IndexBuffer
{
public:

	IndexBuffer();
	~IndexBuffer();

	/** 
	* @brief バッファの生成を行う関数
	* @param 
	* @param 
	*/
	bool Create(UINT size, const UINT16* pIndeces = NULL);

	/** 
	* @brief バッファの解放を行う関数
	*/
	void Finalize();

	/** 
	* @brief バッファの取得を行う関数
	*/
	IDirect3DIndexBuffer9*	GetBuffer() { return m_pBuffer; }

private:

	IDirect3DIndexBuffer9 * m_pBuffer;
};
