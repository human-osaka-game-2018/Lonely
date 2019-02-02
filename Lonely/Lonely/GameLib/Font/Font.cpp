/**
* @file	Font.cpp
* @brief Fontクラスのソースファイル
* @author shion-sagawa
*/

#include "../GameLib.h"
#include "Font.h"

Font::Font()
	: m_fontSize(0)
	, m_pFont(nullptr)
{
}

Font::~Font()
{
	Finalize();
}

// フォントの生成
bool Font::Initialize(int size)
{
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	if (pDevice == nullptr) return false;

	D3DXFONT_DESCA desc;
	desc.Height = size;
	desc.Width = size / 2;
	desc.Weight = 400;
	desc.MipLevels = D3DX_DEFAULT;
	desc.Italic = FALSE;
	desc.CharSet = DEFAULT_CHARSET;
	desc.OutputPrecision = OUT_DEFAULT_PRECIS;
	desc.Quality = DEFAULT_QUALITY;
	desc.PitchAndFamily = FIXED_PITCH | FF_MODERN;
	ZeroMemory(desc.FaceName, sizeof(desc.FaceName));

	D3DXCreateFontIndirectA(
		pDevice,
		&desc,
		&m_pFont
	);

	m_fontSize = size;
	return true;
}

// フォントの破棄
void Font::Finalize()
{
	SAFE_RELEASE(m_pFont);
	m_fontSize = 0;
}

// フォントの高さを取得
int Font::GetHeight()
{
	return m_fontSize;
}

// メッセージの表示
void Font::DrawText(int X, int Y, D3DCOLOR color, const char* pText)
{
	if (m_pFont == nullptr) return;

	RECT rect;
	SetRect(&rect, 0, 0, 0, 0);
	// 描画範囲の取得
	m_pFont->DrawTextA(NULL, pText, -1, &rect, DT_LEFT | DT_CALCRECT, color);

	// 描画
	OffsetRect(&rect, X, Y);
	m_pFont->DrawTextA(NULL, pText, -1, &rect, DT_LEFT, color);
}

// メッセージの表示
void Font::DrawFormatText(int X, int Y, D3DCOLOR color, const char* pFormat, ...)
{
	char temp[MAX_PATH];

	va_list list;
	va_start(list, pFormat);
	vsprintf_s(temp, pFormat, list);
	va_end(list);

	DrawText(X, Y, color, temp);
}
