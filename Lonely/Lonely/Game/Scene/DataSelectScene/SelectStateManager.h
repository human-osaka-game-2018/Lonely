/**
* @file SelectStateManager.h
* @brief SelectStateManagerクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include "../../../GameLib/ObjectManager/Object.h"
#include <vector>

/**
* データセレクトシーンの状態やオブジェクトを管理するクラス
*/
class SelectStateManager
{
public:

	enum CAT_CURSOR_STATE
	{
		DATA1,        //!< データ１にカーソルがあるとき
		DATA2,        //!< データ２にカーソルがあるとき
		DATA3         //!< データ３にカーソルがあるとき
	};

	enum MINI_CURSOR_STATE
	{
		CONTINUE,     //!< 続きから
		NEWGAME,      //!< 初めから
		BACK          //!< 戻る
	};

	SelectStateManager();
	~SelectStateManager();

	/**
	* @brief インスタンスを生成する関数
	*/
	void Initialize();

	/**
	* @brief インスタンスを破棄する関数
	*/
	void Finalize();

	/**
	* @brief オブジェクトを登録する関数
	* @param 登録したい派生クラスのポインタ
	*/
	void RegisterObject(Object*);

	/**
	* @brief オブジェクトを解放する関数
	*/
	void ReleaseObject();

	/**
	* @brief 操作関数
	*/
	void Update();

	/**
	* @brief 描画関数
	*/
	void Render();

private:

	std::vector<Object*>     m_pObjectVec;				 //!< ObjectクラスポインタのVector配列
	int                      m_catCursorState;           //!< 猫型カーソル（データ１か２か３の項目）の情報を持つ
	int                      m_miniCursorState;          //!< 続きから、初めから、削除の項目の情報を持つ
												
};
