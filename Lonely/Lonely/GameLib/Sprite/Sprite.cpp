/**
* @file Sprite.cpp
* @brief Spriteクラスのソースファイル
* @author shion-sagawa
*/

#include "../GameLib.h"

Sprite::Sprite(void)
	: m_x(0.0f), m_y(0.0f)
	, m_width(0.0f), m_height(0.0f)
	, m_u1(0.0f), m_v1(0.0f)
	, m_u2(0.0f), m_v2(0.0f)
	, m_angle(0.0f)
	, m_cx(0.0f), m_cy(0.0f)
	, m_color(0)
{}

Sprite::~Sprite(void)
{
	Finalize();
}

// スプライトの生成
bool Sprite::Create(const char* pTexturePath)
{
	float width = 1.0f;
	float height = 1.0f;
	if (pTexturePath)
	{
		if (!m_texture.Load(pTexturePath))
		{
			return false;
		}
		width = static_cast<float>(m_texture.GetSrcWidth());
		height = static_cast<float>(m_texture.GetSrcHeight());
	}

	SetPos(0.0f, 0.0f);
	SetSize(width, height);
	SetRotation(0.0f);
	SetOrigin(0, 0);
	SetUV(0, 0, (int)width, (int)height);
	SetColor(0xffffffff);

	return true;
}

// スプライトの解放
void Sprite::Finalize(void)
{
	m_texture.Finalize();
}

// スプライトの座標設定
void Sprite::SetPos(float x, float y)
{
	m_x = x;
	m_y = y;
}

// スプライトのサイズ設定
void Sprite::SetSize(float width, float height)
{
	m_width = width;
	m_height = height;
}

// スプライトの回転設定
void Sprite::SetRotation(float angle)
{
	m_angle = angle;
}

// スプライトの原点設定
void Sprite::SetOrigin(float x, float y)
{
	m_cx = x;
	m_cy = y;
}

// スプライトのUV設定
void Sprite::SetUV(int u, int v, int width, int height)
{
	float imageW = static_cast<float>(m_texture.GetWidth());
	float imageH = static_cast<float>(m_texture.GetHeight());
	m_u1 = static_cast<float>(u) / imageW;
	m_v1 = static_cast<float>(v) / imageH;
	m_u2 = static_cast<float>(u + width) / imageW;
	m_v2 = static_cast<float>(v + height) / imageH;
}

// スプライトのカラー設定
void Sprite::SetColor(D3DCOLOR color)
{
	m_color = color;
}


// スプライト描画
void Sprite::Render(void)
{
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();

	pDevice->SetTexture(0, m_texture.GetD3DTexture());
	pDevice->SetFVF(FVF_SIMPLE_TEX_2D);

	Simple2DVertex vertices[4];
	vertices[0].x = 0.0f;
	vertices[0].y = 0.0f;
	vertices[0].u = m_u1;
	vertices[0].v = m_v1;

	vertices[1].x = m_width;
	vertices[1].y = 0.0f;
	vertices[1].u = m_u2;
	vertices[1].v = m_v1;

	vertices[2].x = 0.0f;
	vertices[2].y = m_height;
	vertices[2].u = m_u1;
	vertices[2].v = m_v2;

	vertices[3].x = m_width;
	vertices[3].y = m_height;
	vertices[3].u = m_u2;
	vertices[3].v = m_v2;

	vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color = m_color;
	vertices[0].z = vertices[1].z = vertices[2].z = vertices[3].z = 0.0f;
	vertices[0].rhw = vertices[1].rhw = vertices[2].rhw = vertices[3].rhw = 1.0f;

	for (int i = 0; i < 4; i++)
	{
		D3DXVECTOR2 pos(vertices[i].x - m_cx, vertices[i].y - m_cy);
		D3DXMATRIX rot;
		D3DXMatrixRotationZ(&rot, m_angle);
		D3DXVec2TransformCoord(&pos, &pos, &rot);
		vertices[i].x = pos.x + m_x;
		vertices[i].y = pos.y + m_y;
	}

	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(Simple2DVertex));
}