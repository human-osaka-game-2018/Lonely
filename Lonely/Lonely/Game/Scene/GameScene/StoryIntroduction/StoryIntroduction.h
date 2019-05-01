/**
* @file StoryIntroduction.h
* @brief StoryIntroductionクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "ObjectManager/Object.h"

#include "TexStorage/TexStorage.h"
#include "2DHelper/2DHelper.h"
#include "Scene/GameScene/SharedInformation/SharedInformation.h"


/**
* @brief 物語背景導入関係の処理をまとめたクラス
*/
class StoryIntroduction : public Object
{
public:

	StoryIntroduction();
	~StoryIntroduction();

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

	static const int TEXTURE_MAX = 9;
	const TCHAR* m_textureKeys[TEXTURE_MAX] = {

		_T("story1"),
		_T("story2"),
		_T("story3"),
		_T("story4"),
		_T("story5"),
		_T("story6"),
		_T("story7"),
		_T("story8"),
		_T("story9")
	};

	int                m_decrementCount = 0;    //!< 画像を減少させてどれくらい経ったかを保存する
	int                m_decrSkipCount = 0;     //!< Skip画像を減少させてどれくらい経ったかを保存する
	int                m_heldKeyCount = 0;      //!< キーが長押しされている時間を保存する
	int                m_currentTexNum = 0;     //!< 現在のテクスチャ番号
	int                m_nextTexNum = 1;        //!< 次のテクスチャ番号
	
	Simple2DVertex     m_vertices[4];           //!< 前に描画する頂点情報
	Simple2DVertex     m_backVertices[4];       //!< 後ろに描画する頂点情報
	Simple2DVertex     m_skipVertices[4];       //!< Skip可能画像の頂点情報

	TexStorage*        m_pTexStorage;           
	SharedInformation* m_pSharedInformation;
};
