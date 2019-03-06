/**
* @file UI.h
* @brief UIのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "../../../../GameLib/ObjectManager/Object2DBase.h"
#include "../../../../GameLib/2DHelper/2DHelper.h"
#include "../../../../GameLib/TexStorage/TexStorage.h"
#include "../../../../GameLib/GameLib.h"
#include "../SharedInformation/SharedInformation.h"

enum APP_MENU_STATE
{
	USING,
	NOT_USING,
	STARTING,
	STOPPING
};


/**
* @brief UIの処理をまとめたクラス
*/
class UI : public Object2DBase
{
public:

	UI();
	~UI();


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

	/**
	* @brief アプリメニュの状態を変えるための関数
	*/
	void ChangeAppMenuState();

private:

	float m_width = 230.f;           
	float m_height = 400.f;    

	float m_positionY = 0.f;
	float m_maxPositionY = 0.f;
	float m_minPositionY = 0.f;

	int   m_appMenuState = NOT_USING;
	int   m_appMenuMoveCount = 0;

	TexStorage* m_pTexStorage;
	SoundLib::SoundsManager* m_pSoundsManager;
	SharedInformation*       m_pSharedInformation;
};
