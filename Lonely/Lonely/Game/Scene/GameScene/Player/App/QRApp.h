/**
* @file QRApp.h
* @brief QRAppクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "ObjectManager/Object.h"

#include "TexStorage/TexStorage.h"
#include "2DHelper/2DHelper.h"
#include "Scene/GameScene/SharedInformation/SharedInformation.h"


/**
* @brief QRの状態を管理するEnum変数
*/
enum QR_STATE
{
	IS_GETTED,
	IS_GETTING,
	IS_NOT_GETTING
};

/**
* @brief QRアプリの処理をまとめたクラス
*/
class QRApp : Object
{
public:

	QRApp();
	~QRApp();

	/**
	* @brief 初期化関数
	*/
	bool Initialize();
	/**
	* @brief 解放関数
	*/
	void Finalize();

	/**
	* @brief 更新を行う関数
	*/
	void Update();
	/**
	* @brief 描画を行う関数
	*/
	void Render();

	/**
	* @brief QRを取得する関数
	*/
	void Acquire();

private:

	int                m_state;                   //!< プレイヤーに取得されているかどうか       
	int                m_gettingStateCount;       //!< QRを取得中表示をする間カウントする
	int                m_numQR;                   //!< QRコードをいくつ取得したか
	const int          m_totalNumQr = 10;         //!< QRコードの最大数

	Simple2DVertex     m_verticesGettingQR[4];    //!< QR取得しました、の画像の頂点情報

	TexStorage*        m_pTexStorage;
	SharedInformation* m_pSharedInformation;
};