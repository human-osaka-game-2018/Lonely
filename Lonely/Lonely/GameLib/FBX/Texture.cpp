/**
* @file Texture.h
* @brief Texture�N���X�̃w�b�_�t�@�C��
* @author ���� �k��
*/

#include "Texture.h"
#include "../GameLib.h"

#define	TEXTURE_MAX	1000

// �e�N�X�`���[�f�[�^
struct TextureData
{
	UINT				width;		// �e�N�X�`���[�̕�
	UINT				height;		// �e�N�X�`���[�̍���
	UINT				srcWidth;	// �摜�̕�
	UINT				srcHeight;	// �摜�̍���
	IDirect3DTexture9*	pTexture;	// ���������e�N�X�`���[�̃|�C���^
};

struct LoadedTextureInfo
{
	char		filename[MAX_PATH];
	int			count;
	TextureData	texData;
};
static LoadedTextureInfo g_loadedTextures[TEXTURE_MAX] = {};

// �e�N�X�`���[�̓ǂݍ���
static const TextureData* LoadTexture(const char* pFileName)
{
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		LoadedTextureInfo* pInfo = &g_loadedTextures[i];
		if (pInfo->count == 0) continue;

		if (strcmp(pInfo->filename, pFileName) == 0)
		{
			pInfo->count++;
			return &pInfo->texData;
		}
	}

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		LoadedTextureInfo* pInfo = &g_loadedTextures[i];
		if (pInfo->count != 0) continue;

		IDirect3DTexture9* pTexture;
		D3DXIMAGE_INFO info;
		// �t�@�C������e�N�X�`���[�𐶐�����
		HRESULT hr = D3DXCreateTextureFromFileExA(
			GameLib::Instance.GetDirect3DDevice(),	// Direct3DDevice
			pFileName,				// �t�@�C����
			D3DX_DEFAULT,			// ����(D3DX_DEFAULT�Ńt�@�C�����画��)
			D3DX_DEFAULT,			// ����(D3DX_DEFAULT�Ńt�@�C�����画��)
			1,						// �~�b�v�}�b�v�̐�
			0,						// �g�p�p�r
			D3DFMT_A8R8G8B8,		// �t�H�[�}�b�g
			D3DPOOL_MANAGED,		// �������̊Ǘ��ݒ�
			D3DX_FILTER_NONE,		// �t�B���^�[�ݒ�
			D3DX_DEFAULT,			// �~�b�v�}�b�v�t�B���^�[�̐ݒ�
			0x00000000,				// �J���[�L�[
			&info,					// �摜���
			NULL,					// �p���b�g�f�[�^
			&pTexture);				// ���������e�N�X�`���[�̊i�[��
		if (SUCCEEDED(hr))
		{
			D3DSURFACE_DESC desc;
			// ���������e�N�X�`���[�̏����擾
			pTexture->GetLevelDesc(0, &desc);
			// �e�N�X�`���[���̐ݒ�
			pInfo->texData.pTexture = pTexture;
			pInfo->texData.srcWidth = info.Width;
			pInfo->texData.srcHeight = info.Height;
			pInfo->texData.width = desc.Width;
			pInfo->texData.height = desc.Height;

			return &pInfo->texData;
		}
		break;
	}
	return NULL;
}

// �e�N�X�`���[�̉��
void ReleaseTexture(IDirect3DTexture9* pTexture)
{
	if (pTexture == NULL) return;

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		LoadedTextureInfo* pInfo = &g_loadedTextures[i];
		if (pInfo->count == 0) continue;

		if (pInfo->texData.pTexture == pTexture)
		{
			pInfo->count--;
			if (pInfo->count == 0)
			{
				ZeroMemory(pInfo, sizeof(*pInfo));

				SAFE_RELEASE(pTexture);
			}
		}
	}
}

Texture::Texture(void)
	: m_width(0)
	, m_height(0)
	, m_srcWidth(0)
	, m_srcHeight(0)
	, m_pTexture(NULL)
{
}

Texture::~Texture(void)
{
	Finalize();
}

// �e�N�X�`���[�̓ǂݍ���
bool Texture::Load(const char* pFileName)
{
	const TextureData* pData = LoadTexture(pFileName);
	if (pData == NULL) return false;

	m_pTexture = pData->pTexture;
	m_srcWidth = pData->srcWidth;
	m_srcHeight = pData->srcHeight;
	m_width = pData->width;
	m_height = pData->height;
	return true;
}

// �e�N�X�`���[�̓ǂݍ���
bool Texture::CreateFromMemory(const void* pData, UINT size)
{
	IDirect3DTexture9* pTexture;
	D3DXIMAGE_INFO info;

	HRESULT hr = D3DXCreateTextureFromFileInMemoryEx(
		GameLib::Instance.GetDirect3DDevice(),
		pData,
		size,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		1,
		0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0x00000000,
		&info,
		NULL,
		&pTexture);
	if (FAILED(hr))
	{
		return false;
	}
	D3DSURFACE_DESC desc;
	pTexture->GetLevelDesc(0, &desc);

	m_pTexture = pTexture;
	m_srcWidth = info.Width;
	m_srcHeight = info.Height;
	m_width = desc.Width;
	m_height = desc.Height;

	return true;
}

// �e�N�X�`���[�̉��
void Texture::Finalize(void)
{
	if (m_pTexture)
	{
		ReleaseTexture(m_pTexture);
		m_pTexture = NULL;
	}
}
