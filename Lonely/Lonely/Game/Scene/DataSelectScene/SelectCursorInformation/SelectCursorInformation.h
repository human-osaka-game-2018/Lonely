/**
* @file SelectCursorInformation.h
* @brief SelectCursorInformationクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include <d3dx9math.h>

/**
* @brief 猫型カーソルの状態
*/
enum CAT_CORSOR_STATE
{
	DATA1,        //!< データ１を選択しているとき
	DATA2,        //!< データ２を選択しているとき
	DATA3,        //!< データ３を選択しているとき
};

/**
* @brief ミニカーソル（続きから、初めから、戻る）の状態
*/
enum MINI_CORSOR_STATE
{
	CONTINUE,     //!< 「続きから」を選択しているとき
	NEWGAME,      //!< 「初めから」を選択しているとき
	BACK,         //!< 「戻る」を選択しているとき
};


/**
* @brief 共有したい情報まとめたクラス
*/
class SelectCursorInformation
{
public:

	SelectCursorInformation();
	~SelectCursorInformation();

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

	
public://セッターとゲッター

	//猫型カーソルの状態
	void SetCatCursorState(int state) { m_catCursorState = state; }
	int GetCatCursorState() { return m_catCursorState; }

	//ミニカーソルの状態
	void SetMiniCursorState(int state) { m_miniCursorState = state; }
	int GetMiniCursorState() { return m_miniCursorState; }
	
private:

	void SelectCursorInformation::UpdateCatCursorState();
	void SelectCursorInformation::UpdateMiniCursorState();

	int  m_catCursorState = DATA1;        //!< 猫型カーソルの状態
	int  m_miniCursorState = CONTINUE;    //!< ミニカーソル（続きから、初めから、戻る）の状態
	bool m_catCursorIsActive = true;      //!< 猫型カーソルが主導権を持っているか                       
	bool m_miniCursorIsActive = false;    //!< ミニカーソルが主導権を持っているか

};
