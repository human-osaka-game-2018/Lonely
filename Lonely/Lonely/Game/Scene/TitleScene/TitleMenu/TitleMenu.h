/**
* @file TitleMenu.h
* @brief TitleMenuクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "../../../../GameLib/ObjectManager/Object.h"
#include "../../../../GameLib/DirectX/DirectX.h"
#include "../../../../GameLib/2DHelper/2DHelper.h"
#include "../../../../GameLib/FBX/VertexBuffer.h"
#include "../../../../GameLib/FBX/Texture.h"
#include "MenuPressEnter.h"
#include "MenuGameStart.h"
#include "MenuGameEnd.h"
#include "MenuCursor.h"

#include "../../../../SoundLib/Include/SoundsManager.h"
#include "../../../../SoundLib/Include/SoundLibCWrapper.h"


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

	MenuPressEnter m_menuPressEnter;
	MenuGameStart  m_menuGameStart;
	MenuGameEnd    m_menuGameEnd;
	MenuCursor     m_menuCursor;

	int            m_step = STEP1;

	SoundLib::SoundsManager* m_pSoundsManager;

};
