#include ""
#include "Scene/SystemScene.h"


// エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// DirectXLibの初期化
	DirectXLib::Instance.Initialize("DirectXLib", 1280, 720, false);

	// システムシーンへ遷移する
	SCENEMANAGER->JumpScene(new SystemScene);

	DirectXLib::Instance.MainLoop();

	// DirectXLibの解放
	DirectXLib::Instance.Finalize();

	return 0;
}
