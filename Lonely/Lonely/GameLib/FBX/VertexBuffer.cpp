/**
* @file VertexBuffer.h
* @brief VertexBufferクラスのヘッダファイル
* @author 佐川 嗣苑
*/

#include "VertexBuffer.h"
#include "../GameLib.h"

VertexBuffer::VertexBuffer(void)
	: m_pBuffer(NULL)
{}
VertexBuffer::~VertexBuffer(void)
{
	Finalize();
}

// 頂点バッファの生成
bool VertexBuffer::Create(UINT size, const void* pVertices)
{
	IDirect3DVertexBuffer9* pVertexBuffer;
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	// 指定したサイズの頂点バッファを作成
	if (FAILED(pDevice->CreateVertexBuffer(size, 0, 0, D3DPOOL_MANAGED, &pVertexBuffer, NULL)))
	{
		return NULL;
	}

	if (pVertices)
	{
		void* pData;
		// バッファをロックしてデータを書き込む
		if (SUCCEEDED(pVertexBuffer->Lock(0, size, &pData, 0)))
		{
			memcpy(pData, pVertices, size);
			pVertexBuffer->Unlock();
		}
	}
	m_pBuffer = pVertexBuffer;
	return pVertexBuffer != NULL;
}

void VertexBuffer::Finalize(void)
{
	SAFE_RELEASE(m_pBuffer);
}
