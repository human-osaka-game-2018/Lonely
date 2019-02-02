/**
* @file TrigarQR.h
* @brief TrigarQRクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include <d3dx9math.h>

#include "TrigarBase.h"
#include "../../../../GameLib/FBX/3DHelper.h"
#include "../../../../GameLib/2DHelper/2DHelper.h"

enum QR_STATE
{
	IS_GETTED,
	IS_GETTING,
	IS_NOT_GETTED
};

/**
* @brief QRコード関係の処理のクラス
*/
class TrigarQR : public TrigarBase
{
public:

	TrigarQR();
	~TrigarQR();

	/**
	* @brief コンストラクタ(当たり判定がBOXのとき）
	* @param 中心の位置
	* @param BOXの軸の長さ
	*/
	TrigarQR(D3DXVECTOR3* position, D3DXVECTOR3* boxLength);

	/**
	* @brief 初期化関数
	*/
	bool Initialize();

	/**
	* @brief 解放関数
	*/
	void Finalize();

	/**
	* @brief 更新関数
	*/
	void Update();

	/**
	* @brief 描画関数
	*/
	void Render();

private:

	SimpleTexVertex m_verticesQR[4] =
	{
		//   x,  y,   z,      color,  tu,  tv
		-2.f,  2.f, 0.f, static_cast<DWORD>(0xffffffff), 0.f, 0.f,
		 2.f,  2.f, 0.f, static_cast<DWORD>(0xffffffff), 1.f, 0.f,
		 2.f, -2.f, 0.f, static_cast<DWORD>(0xffffffff), 1.f, 1.f,
		-2.f, -2.f, 0.f, static_cast<DWORD>(0xffffffff), 0.f, 1.f

	};

	SimpleTexVertex m_verticesIconQR[4] =
	{
		//   x,  y,   z,      color,  tu,  tv
		-2.f,  2.f, 0.f, static_cast<DWORD>(0xffffffff), 0.f, 0.f,
		 2.f,  2.f, 0.f, static_cast<DWORD>(0xffffffff), 1.f, 0.f,
		 2.f, -2.f, 0.f, static_cast<DWORD>(0xffffffff), 1.f, 1.f,
		-2.f, -2.f, 0.f, static_cast<DWORD>(0xffffffff), 0.f, 1.f

	};

	Texture         m_textureQR;               //!< QRのテクスチャ
	int             m_state;                   //!< プレイヤーに取得されているかどうか       
	int             m_gettingStateCount;       //!< QRを取得中表示をする間カウントする
	
	Texture         m_textureGettingQR;        //!< QR取得中表示のテクスチャ
	Simple2DVertex  m_verticesGettingQR[4];    //!< QR取得中表示の頂点

	Texture         m_textureIconQR;           //!< QRを取得できるというテクスチャ

};
