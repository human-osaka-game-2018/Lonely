/**
* @file TriggerDoor.h
* @brief TriggerDoorクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "TriggerBase.h"

#include <d3dx9math.h>

#include "2DHelper/2DHelper.h"
#include "Scene/GameScene/Player/App/QRApp.h"

/**
* @brief ドア関係の処理のクラス
*/
class TriggerDoor : public TriggerBase
{
public:

	TriggerDoor();
	~TriggerDoor();

	/**
	* @brief コンストラクタ(当たり判定がBOXのとき）
	* @param 中心の位置
	* @param BOXの軸の長さ
	*/
	TriggerDoor(D3DXVECTOR3* position, D3DXVECTOR3* boxLength, QRApp* pQrApp);

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

	/**
	* @brief クリア条件数に現在保持してるQR数が達成しているか
	* @return 達成していたらTRUEを返す
	*/
	bool AchieveClearCondition(int retentionQrNum)
	{
		return (retentionQrNum >= m_ClearConditionQrNum) ? true : false;
	}

	const int       m_ClearConditionQrNum = 10;    //!< クリアに必要なQR数
	Simple2DVertex  m_vertices[4];                 //!< QR取得中表示の頂点
	QRApp*          m_pQrApp;                      //!< QRの管理クラス

};
