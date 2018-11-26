/**
* @file	Input.cpp
* @brief Inputクラスのソースファイル
* @author 佐川　嗣苑
*/

#include "Input.h"

Input::Input()
{
	Initialize();
}
Input::~Input()
{
	Finalize();
}

// 入力システムの初期化
void Input::Initialize()
{
	for (int i = 0; i < KeyBindMax; i++)
	{
		m_keyState.keyBind[i] = -1;
	}
	m_keyState.keyState = 0;
	m_keyState.keyStateOld = 0;
}

// 入力システムの解放
void Input::Finalize()
{
	//解放は必要ないが、キー入力情報を０で初期化している
	Initialize();
}

// 入力状況の更新
void Input::Update()
{
	BYTE keyboardState[256];
	// キーボード状態の取得
	GetKeyboardState(keyboardState);

	int keyState = 0;
	for (int i = 0; i < KeyBindMax; i++)
	{
		// キーがバインドされていなければスルーする
		int key = m_keyState.keyBind[i];
		if (key == -1) continue;

		// 入力されている場合はキーのビットを立てる
		if (keyboardState[key] & 0x80)
		{
			keyState |= (1 << i);
		}
	}
	// ステートの更新
	m_keyState.keyStateOld = m_keyState.keyState;
	m_keyState.keyState = keyState;
}

// キーバインドの設定
void Input::BindKey(EKeyBind key, int keycode)
{
	m_keyState.keyBind[key] = keycode;
}

// キーが押されているか？
bool Input::IsKeyPress(EKeyBind key)
{
	int bit = (1 << key);
	int state = m_keyState.keyState;
	return (state & bit) ? true : false;
}

// キーが押されたか？
bool Input::IsKeyPush(EKeyBind key)
{
	int bit = (1 << key);
	int state = m_keyState.keyState & ~m_keyState.keyStateOld;
	return (state & bit) ? true : false;
}

// キーが離されたか？
bool Input::IsKeyReleases(EKeyBind key)
{
	int bit = (1 << key);
	int state = m_keyState.keyStateOld & ~m_keyState.keyState;
	return (state & bit) ? true : false;
}
