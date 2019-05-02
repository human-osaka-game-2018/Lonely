/**
* @file GameClear.h
* @brief GameClearクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "ObjectManager/Object.h"

#include "TexStorage/TexStorage.h"
#include "2DHelper/2DHelper.h"
#include "Scene/GameScene/SharedInformation/SharedInformation.h"


/**
* @brief ゲームクリアの処理をまとめたクラス
*/
class GameClear : public Object
{
public:

	GameClear();
	~GameClear();

	/**
	* @brief 初期化する関数
	*/
	bool Initialize();

	/**
	* @brief 解放する関数
	*/
	void Finalize();

	/**
	* @brief 操作関数
	*/
	void Update();

	/**
	* @brief 描画関数
	*/
	void Render();

private:

	static const int CLEAR_TEXTURE_MAX = 5;
	const TCHAR* m_textureKeys[CLEAR_TEXTURE_MAX] = {

		_T("gameClear1"),
		_T("gameClear2"),
		_T("gameClear3"),
		_T("gameClear4"),
		_T("gameClear5")
	};

	int                m_decrementCount = 0;    //!< 画像を減少させてどれくらい経ったかを保存する
	int                m_currentTexNum = 0;     //!< 現在のテクスチャ番号
	int                m_nextTexNum = 1;        //!< 次のテクスチャ番号

	Simple2DVertex     m_vertices[4];           //!< 前に描画する頂点情報
	Simple2DVertex     m_backVertices[4];       //!< 後ろに描画する頂点情報
	
	TexStorage*        m_pTexStorage;
	SharedInformation* m_pSharedInformation;
};
