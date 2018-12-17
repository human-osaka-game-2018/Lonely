/**
* @file Main.cpp
* @brief エントリー関数のソースファイル
* @author shion-sagawa
*/

#include "../../GameLib/GameLib.h"
#include "../Scene/TitleScene/TitleScene.h"

// エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// GameLibの初期化
	GameLib::Instance.Initialize(L"Lonely", 1280, 720, false);

	// システムシーンへ遷移する
	SCENEMANAGER->ChangeScene(new TitleScene);

	GameLib::Instance.MainLoop();

	// DirectXLibの解放
	GameLib::Instance.Finalize();

	return 0;
}
