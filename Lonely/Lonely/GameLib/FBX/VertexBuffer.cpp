/**
* @file VertexBuffer.cpp
* @brief VertexBuffer�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "VertexBuffer.h"
#include "../GameLib.h"

VertexBuffer::VertexBuffer()
	: m_pBuffer(NULL)
{}
VertexBuffer::~VertexBuffer()
{
	Finalize();
}

// ���_�o�b�t�@�̐���
bool VertexBuffer::Create(UINT size, const void* pVertices)
{
	IDirect3DVertexBuffer9* pVertexBuffer;
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	// �w�肵���T�C�Y�̒��_�o�b�t�@���쐬
	if (FAILED(pDevice->CreateVertexBuffer(size, 0, 0, D3DPOOL_MANAGED, &pVertexBuffer, NULL)))
	{
		return NULL;
	}

	if (pVertices)
	{
		void* pData;
		// �o�b�t�@�����b�N���ăf�[�^����������
		if (SUCCEEDED(pVertexBuffer->Lock(0, size, &pData, 0)))
		{
			memcpy(pData, pVertices, size);
			pVertexBuffer->Unlock();
		}
	}
	m_pBuffer = pVertexBuffer;
	return pVertexBuffer != NULL;
}

void VertexBuffer::Finalize()
{
	SAFE_RELEASE(m_pBuffer);
}
