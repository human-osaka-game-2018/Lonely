/**
* @file 2DHelper.h
* @brief 2DHelperクラスのヘッダファイル
* @author 佐川 嗣苑
*/

#pragma once

#include "../DirectX/DirectX.h"
#include "../FBX/Texture.h"


#define FVF_SIMPLE_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#define FVF_SIMPLE_TEX_2D   (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)


// シンプルなテクスチャ―付き頂点情報
struct Simple2DVertex
{
	float x, y, z;
	float rhw;
	DWORD color;
	float u, v;
};


/**	
* @brief スプライトクラス
*/
class Sprite
{
public:
	Sprite();
	~Sprite();

	/** 
	* @brief スプライトの生成
	* @param 
	* @return
	*/
	bool Create(const char* pTexturePath = NULL);
	
	/** 
	* @brief スプライトの解放
	*/
	void Finalize();


	/** 
	* @brief スプライト描画
	*/
	void Render();

	/** 
	* @brief スプライトの座標設定
	* @param
	* @param 
	*/
	void SetPos(float x, float y);

	/** 
	* @brief スプライトのサイズ設定
	* @param 
	* @param 
	*/
	void SetSize(float width, float height);

	/** 
	* @brief スプライトの回転設定
	* @param 
	*/
	void SetRotation(float angle);

	/** 
	* @brief スプライトの原点設定
	* @param 
	* @param
	*/
	void SetOrigin(float x, float y);

	/** 
	* @brief スプライトのUV設定
	* @param 
	* @param
	* @param
	*/
	void SetUV(int u, int v, int width, int height);

	/** 
	* @brief スプライトのカラー設定
	* @param 
	*/
	void SetColor(D3DCOLOR color);

	/** 
	* @brief スプライトの座標取得
	*/
	float GetX() const { return m_x; }

	/**
	* @brief スプライトの座標取得
	*/
	float GetY() const { return m_y; }

	/** 
	* @brief スプライトのサイズ取得
	*/
	float GetWidth() const { return m_width; }

	/**
	* @brief スプライトのサイズ取得
	*/
	float GetHeight() const { return m_height; }

	/** 
	* @brief スプライトの回転設定
	*/
	float GetRotation() const { return m_angle; }

	/** 
	* @brief スプライトの原点設定
	*/
	float GetOriginX() const { return m_cx; }

	/**
	* @brief スプライトの原点設定
	*/
	float GetOriginY() const { return m_cy; }

	/** 
	* @brief スプライトのUV取得
	*/
	float GetU() const { return m_u1; }
	float GetV() const { return m_v1; }
	float GetUWidth() const { return m_u2 - m_u1; }
	float GetVHeight() const { return m_v2 - m_v1; }

	/** 
	* @brief スプライトのカラー設定
	*/
	D3DCOLOR GetColor() const { return m_color; }

	/** 
	* @brief テクスチャーの取得
	*/
	Texture* GetTexture(void) { return &m_texture; }

private:
	float		m_x, m_y;
	float		m_width, m_height;
	float		m_u1, m_v1;
	float		m_u2, m_v2;
	float		m_angle;
	float		m_cx, m_cy;
	D3DCOLOR	m_color;
	Texture		m_texture;
};

