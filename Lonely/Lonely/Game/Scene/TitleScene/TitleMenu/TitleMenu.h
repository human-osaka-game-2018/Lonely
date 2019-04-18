/**
* @file TitleMenu.h
* @brief TitleMenuクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "SoundLib/Include/SoundsManager.h"
#include "SoundLib/Include/SoundLibCWrapper.h"

#include "MenuPressEnter.h"
#include "MenuGameStart.h"
#include "MenuGameEnd.h"
#include "MenuCursor.h"

/**
* @brief タイトルメニューの操作手順
*/
enum TITLEMENU_STEP
{
	STEP1,      //!< エンターが押されるまでのステップ
	STEP2,      //!< カーソルがゲームスタートにあるステップ
	STEP3       //!< カーソルがゲームエンドにあるステップ
};


/**
* @brief タイトルメニューの処理をまとめたクラス
*/
class TitleMenu : public Object
{
public:

	TitleMenu();
	~TitleMenu();

	/**
	* @brief 初期化する関数
	* @param
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

	MenuPressEnter m_menuPressEnter;    //!< 「プレスエンター」関係のクラスの実体
	MenuGameStart  m_menuGameStart;     //!< 「ゲームスタート」関係のクラスの実体
	MenuGameEnd    m_menuGameEnd;       //!< 「ゲームエンド」関係のクラスの実体
	MenuCursor     m_menuCursor;        //!< メニューカーソル関係のクラスの実体

	int            m_step = STEP1;

	SoundLib::SoundsManager* m_pSoundsManager;

};
