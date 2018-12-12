/**
* @file	Input.h
* @brief Inputクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include <windows.h>

/** 
* @brief DirectInput関係の処理をまとめたクラス
*/
class Input
{
public:

	/**
	* @brief キー入力の構造体
	*/
	enum EKeyBind
	{
		Option,	//!< Option
		A,		//!< A
		B,		//!< B

		Up,		//!< ↑
		Down,	//!< ↓
		Left,	//!< ←
		Right,	//!< →


		KeyBindMax,
	};

	Input();
	~Input();

	/** 
	* @brief 入力システムの初期化を行う関数
	*/
	void Initialize();

	/** 
	* @brief 入力システムの解放を行う関数
	*/
	void Finalize();

	/** 
	* @brief 入力状況の更新を行う関数
	*/
	void Update();

	/** 
	* @brief キーバインドの設定を行う関数
	* @param キー入力情報をまとめた構造体
	* @param どのキー入力情報が欲しいか
	*/
	void BindKey(EKeyBind key, int keycode);

	/** 
	* @brief キーが押されているかを取得する関数
	* @param キー入力情報をまとめた構造体
	* @return キーが押されていたらTRUE
	*/
	bool IsKeyPress(EKeyBind key);

	/**
	* @brief キーが押されたか？
	* @param 入力情報をまとめた構造体
	* @return キーが押されていたらTRUE
	*/
	bool IsKeyPush(EKeyBind key);

	/** 
	* @brief キーが離されたか取得する関数
	* @return キーが離されていたらTRUE
	*/
	bool IsKeyReleases(EKeyBind key);

private:
	
	/**
	* @brief キー入力情報を持つ構造体
	*/
	struct KeyInfo
	{
		int keyBind[KeyBindMax];
		int keyState;
		int keyStateOld;
	};

	/** KeyInfo構造体の実態 */
	KeyInfo	m_keyState;
};
