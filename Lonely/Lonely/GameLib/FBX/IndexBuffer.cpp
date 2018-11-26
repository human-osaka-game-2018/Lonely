/**
* @file IndexBuffer.cpp
* @brief IndexBufferクラスのソースファイル
* @author 佐川 嗣苑
*/

#include "IndexBuffer.h"
#include "../GameLib.h"

IndexBuffer::IndexBuffer(void)
	: m_pBuffer(NULL)
{}
IndexBuffer::~IndexBuffer(void)
{
	Finalize();
}
// インデックスバッファの生成
bool IndexBuffer::Create(UINT size, const UINT16* pIndeces)
{
	IDirect3DIndexBuffer9* pIndexBuffer;
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	// 16byte型のインデックスバッファを作成
	if (FAILED(pDevice->CreateIndexBuffer(size, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIndexBuffer, NULL)))
	{
		return NULL;
	}
	if (pIndeces)
	{
		void* pData;
		// バッファをロックしてデータを書き込む
		if (SUCCEEDED(pIndexBuffer->Lock(0, size, &pData, 0)))
		{
			memcpy(pData, pIndeces, size);
			pIndexBuffer->Unlock();
		}
	}
	m_pBuffer = pIndexBuffer;
	return pIndexBuffer != NULL;
}


void IndexBuffer::Finalize(void)
{
	SAFE_RELEASE(m_pBuffer);
}