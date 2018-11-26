/**
* @file Texture.h
* @brief Textureクラスのヘッダファイル
* @author 佐川 嗣苑
*/

#include "Texture.h"
#include "../GameLib.h"

#define	TEXTURE_MAX	1000

// テクスチャーデータ
struct TextureData
{
	UINT				width;		// テクスチャーの幅
	UINT				height;		// テクスチャーの高さ
	UINT				srcWidth;	// 画像の幅
	UINT				srcHeight;	// 画像の高さ
	IDirect3DTexture9*	pTexture;	// 生成したテクスチャーのポインタ
};

struct LoadedTextureInfo
{
	char		filename[MAX_PATH];
	int			count;
	TextureData	texData;
};
static LoadedTextureInfo g_loadedTextures[TEXTURE_MAX] = {};

// テクスチャーの読み込み
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
		// ファイルからテクスチャーを生成する
		HRESULT hr = D3DXCreateTextureFromFileExA(
			GameLib::Instance.GetDirect3DDevice(),	// Direct3DDevice
			pFileName,				// ファイル名
			D3DX_DEFAULT,			// 横幅(D3DX_DEFAULTでファイルから判定)
			D3DX_DEFAULT,			// 高さ(D3DX_DEFAULTでファイルから判定)
			1,						// ミップマップの数
			0,						// 使用用途
			D3DFMT_A8R8G8B8,		// フォーマット
			D3DPOOL_MANAGED,		// メモリの管理設定
			D3DX_FILTER_NONE,		// フィルター設定
			D3DX_DEFAULT,			// ミップマップフィルターの設定
			0x00000000,				// カラーキー
			&info,					// 画像情報
			NULL,					// パレットデータ
			&pTexture);				// 生成したテクスチャーの格納先
		if (SUCCEEDED(hr))
		{
			D3DSURFACE_DESC desc;
			// 生成したテクスチャーの情報を取得
			pTexture->GetLevelDesc(0, &desc);
			// テクスチャー情報の設定
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

// テクスチャーの解放
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

// テクスチャーの読み込み
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

// テクスチャーの読み込み
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

// テクスチャーの解放
void Texture::Finalize(void)
{
	if (m_pTexture)
	{
		ReleaseTexture(m_pTexture);
		m_pTexture = NULL;
	}
}
