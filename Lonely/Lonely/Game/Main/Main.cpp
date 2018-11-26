///**
//* @file Main.cpp
//* @brief LonelyのMain.cpp
//* @author 佐川　嗣苑
//*/
//
//#include "Main.h"
//#include "../../GameLib/GameLib.h"
//#include <windows.h>
//#include <stdio.h>
//#include <d3dx9.h>
//#include <dinput.h>
//#include <crtdbg.h>
//#include <tchar.h>
//
//#pragma comment(lib, "winmm.lib")
//#pragma comment(lib, "d3dx9.lib")
//#pragma comment(lib, "dxguid.lib")
//#pragma comment(lib, "d3d9.lib")
//#pragma comment(lib, "dinput8.lib")
//
//#define WINDOW_MODE						// ウィンドウモード(通常)
//
//#define WINDOW_TITLE TEXT("Lonely")		// ウィンドウタイトル
//#define CLIENT_SIZE_W 1280				// クライアントサイズの幅
//#define CLIENT_SIZE_H 720 				// クライアントサイズの高さ
//#define GAME_FPS (1000 / 60)			// ゲームFPS
//#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
//
//LPDIRECT3D9 pD3d;
//LPDIRECT3DDEVICE9 pDevice;
//LPDIRECTINPUT8 pDinput = NULL;//キー入力のための変数
//LPDIRECTINPUTDEVICE8 pKeyDevice = NULL;
//LPDIRECTINPUTDEVICE8 pMouseDevice = NULL;
//
//HRESULT InitDinput(HWND hWnd);
//HRESULT InitD3d(HWND hWnd);
//
//// プロシージャ関数
//LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
//
//// エントリポイント
//INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
//{
//	// メモリリーク検出
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//
//	MSG msg;
//
//	//-------------------------------------------------------------------//
//	//				         ウィンドウ生成
//	//-------------------------------------------------------------------//	
////#ifdef WINDOW_MODE		//	ウィンドウモード(通常)
////	GameLib::Instance().InitGameLib(WINDOW_TITLE, CLIENT_SIZE_W, CLIENT_SIZE_H, WindowProc, false);
////#else					//　フルスクリーンモード
////	GameLib::Instance().InitGameLib(WINDOW_TITLE, CLIENT_SIZE_W, CLIENT_SIZE_H, WindowProc, true);
////#endif
////
//	HWND hWnd = NULL;
//	MSG msg;
//	// ウィンドウの初期化
//	static wchar_t szAppName[] = _T("Lonely");
//	WNDCLASSEX  wndclass;
//
//	wndclass.cbSize = sizeof(wndclass);
//	wndclass.style = CS_HREDRAW | CS_VREDRAW;
//	wndclass.lpfnWndProc = WndProc;
//	wndclass.cbClsExtra = 0;
//	wndclass.cbWndExtra = 0;
//	wndclass.hInstance = hInst;
//	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
//	wndclass.lpszMenuName = NULL;
//	wndclass.lpszClassName = szAppName;
//	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
//
//	RegisterClassEx(&wndclass);
//
//	hWnd = CreateWindowW(szAppName, szAppName, WS_OVERLAPPEDWINDOW,
//		0, 0, 1280, 720, NULL, NULL, hInst, NULL);
//
//	// ダイレクト３Dの初期化関数を呼ぶ
//	if (FAILED(InitD3d(hWnd)))
//	{
//		return 0;
//	}
//	//ダイレクトインプットの初期化関数を呼ぶ
//	if (FAILED(InitDinput(hWnd))) {
//		return 0;
//	}
//
//	//シーンマネージャの生成
//	SceneManager* pSceneManager = SceneManager::GetInstance();
//	//オブジェクトマネージャの生成
//	//ObjectManager* pObjectManager = ObjectManager::GetInstance();
//
//	//-------------------------------------------------------------------//
//	//						メッセージループ
//	//-------------------------------------------------------------------//
//
//	DWORD currentTime;						// 現在の時間
//	DWORD oldTime = timeGetTime();			// 前の時間
//
//	ZeroMemory(&msg, sizeof(msg));
//	while (msg.message != WM_QUIT)
//	{
//		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
//		{
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//		else
//		{
//			currentTime = timeGetTime();
//			if (currentTime - oldTime >= GAME_FPS)
//			{
//				//キーUpdate
//				m_pInput->Update();
//				pSceneManager->DevideSceneOperation();
//				oldTime = timeGetTime();
//			}
//		}
//	}
//
//	//シーンマネージャのインスタンスを破棄する
//	pSceneManager->ReleaseInstance();
//
//	//GameLib::Instance().ReleaseGameLib();
//
//	// メッセージループから抜けたらオブジェクトを全て開放する
//	FreeDx();
//	// OSに戻る（アプリケーションを終了する）
//	return (INT)msg.wParam;
//}
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
//{
//	switch (iMsg)
//	{
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	case WM_KEYDOWN:
//		switch ((CHAR)wParam)
//		{
//		case VK_ESCAPE:
//			PostQuitMessage(0);
//			break;
//
//		}
//		break;
//
//
//		break;
//	}
//	return DefWindowProc(hWnd, iMsg, wParam, lParam);
//}
//
////
////VOID FreeDx()
//// 作成したDirectXオブジェクトの開放
//VOID FreeDx()
//{
//	/*for (DWORD i = 0;i<THING_AMOUNT;i++)
//	{
//		SAFE_RELEASE(Thing[i].pMesh);
//	}*/
//	SAFE_RELEASE(pDevice);
//	SAFE_RELEASE(pD3d);
//}
//
////ダイレクトインプットの初期化関数
//HRESULT InitDinput(HWND hWnd)
//{
//	HRESULT hr;
//	//「DirectInput」オブジェクトの作成
//	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDinput, NULL)))
//	{
//		return hr;
//	}
//	//「DirectInputデバイス」
//	if (FAILED(hr = pDinput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, NULL)))
//	{
//		return hr;
//	}
//	//デバイスをキーボードに設定
//	if (FAILED(hr = pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
//	{
//		return hr;
//	}
//	//協調レベルの設定
//	if (FAILED(hr = pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
//	{
//		return hr;
//	}
//	////デバイスを「取得」する
//	//pKeyDevice->Acquire();
//
//	//デバイスを生成
//	if (FAILED(hr = pDinput->CreateDevice(GUID_SysMouse,
//		&pMouseDevice, NULL)))
//	{
//		return hr;
//	}
//
//	//デバイスをマウスに設定
//	if (FAILED(hr = pMouseDevice->SetDataFormat(&c_dfDIMouse)))
//	{
//		return hr;
//	}
//	//協調レベルの設定
//	if (FAILED(hr = pMouseDevice->SetCooperativeLevel(
//		hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
//	{
//		return hr;
//	}
//
//	DIPROPDWORD diprop;
//	diprop.diph.dwSize = sizeof(diprop);
//	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
//	diprop.diph.dwObj = 0;
//	diprop.diph.dwHow = DIPH_DEVICE;
//	diprop.dwData = DIPROPAXISMODE_REL;
//
//	if (FAILED(hr = pMouseDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
//	{
//		return hr;
//	}
//
//	//デバイスを取得
//	//pMouseDevice->Acquire();
//	//pMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &g_mouseState.directInputMouseState);
//
//	return S_OK;
//}
//
////HRESULT InitD3d(HWND hWnd)
////ダイレクト3Dの初期化関数
//HRESULT InitD3d(HWND hWnd)
//{
//	// 「Direct3D」オブジェクトの作成
//	if (NULL == (pD3d = Direct3DCreate9(D3D_SDK_VERSION)))
//	{
//		MessageBox(0, _T("Direct3Dの作成に失敗しました"),_T(""), MB_OK);
//		return E_FAIL;
//	}
//	// 「DIRECT3Dデバイス」オブジェクトの作成
//	D3DPRESENT_PARAMETERS d3dpp;
//	ZeroMemory(&d3dpp, sizeof(d3dpp));
//	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
//	d3dpp.BackBufferCount = 1;
//	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
//	d3dpp.Windowed = TRUE;
//	d3dpp.EnableAutoDepthStencil = TRUE;
//	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
//
//	if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
//		D3DCREATE_MIXED_VERTEXPROCESSING,
//		&d3dpp, &pDevice)))
//	{
//		MessageBox(0, _T("HALモードでDIRECT3Dデバイスを作成できません\nREFモードで再試行します"), NULL, MB_OK);
//		if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
//			D3DCREATE_MIXED_VERTEXPROCESSING,
//			&d3dpp, &pDevice)))
//		{
//			MessageBox(0, _T("DIRECT3Dデバイスの作成に失敗しました"), NULL, MB_OK);
//			return E_FAIL;
//		}
//	}
//	// Zバッファー処理を有効にする
//	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
//	// ライトを有効にする
//	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
//	// アンビエントライト（環境光）を設定する
//	pDevice->SetRenderState(D3DRS_AMBIENT, 0x00808080);
//	// スペキュラ（鏡面反射）を有効にする
//	pDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
//	return S_OK;
//}