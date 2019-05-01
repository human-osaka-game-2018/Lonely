/**
* @file TriggerQR.h
* @brief TriggerQRクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "TriggerBase.h"

#include <d3dx9math.h>

#include "FBX/3DHelper.h"
#include "2DHelper/2DHelper.h"
#include "Scene/GameScene/Player/App/QRApp.h"

/**
* @brief QRコード関係の処理のクラス
*/
class TriggerQR : public TriggerBase
{
public:

	TriggerQR();
	~TriggerQR();

	/**
	* @brief コンストラクタ(当たり判定がBOXのとき）
	* @param 中心の位置
	* @param BOXの軸の長さ
	*/
	TriggerQR(D3DXVECTOR3* position, D3DXVECTOR3* boxLength, QRApp* pQrApp);

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

	Simple2DVertex  m_verticesCallout[4];      //!< 吹き出しの頂点情報
	Simple2DVertex  m_verticesGettingQR[4];    //!< QR取得中表示の頂点情報
	Simple2DVertex  m_verticesQrIcon[4];       //!< QRアイコンの頂点情報
	bool            m_isGetted;                //!< 取得されたかどうか

	QRApp*          m_pQrApp;                  //!< QRの管理クラス
};
