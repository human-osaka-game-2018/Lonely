/**
* @file Main.cpp
* @brief エントリー関数のソースファイル
* @author shion-sagawa
*/

#include "GameLib.h"

// エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// GameLibの初期化
	GameLib::Instance.Initialize(L"Lonely", 1280, 720, false);

	// ゲームのメインループ
	GameLib::Instance.MainLoop();

	// DirectXLibの解放
	GameLib::Instance.Finalize();

	return 0;
}
