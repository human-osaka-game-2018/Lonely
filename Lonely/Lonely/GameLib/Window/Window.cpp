/**
* @file	Window.cpp
* @brief Windowクラスのソースファイル
* @author 佐川　嗣苑
*/

#include "Window.h"

// ウインドウプロシージャー
static LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uiMsg)
	{
	case WM_DESTROY:			//閉じるボタンでウィンドウを破棄
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch ((CHAR)wParam)
		{
		case VK_ESCAPE:			//ESCAPEキーでウィンドウを破棄
			PostQuitMessage(0);
			break;

		}
		break;


		break;
	}
	// 既定のウィンドウプロシージャを呼び出す
	return DefWindowProc(hWnd, uiMsg, wParam, lParam);
}

// コンストラクタ
Window::Window(void)
	: m_hWnd(NULL)
	, m_isQuitMessage(false)
	, m_width(0)
	, m_height(0)
{
}

// デストラクタ
Window::~Window(void)
{
}

// ウィンドウの生成
bool Window::Create(const wchar_t* pName, int width, int height)
{
	WNDCLASSEX wndClass;
	// ウインドウの設定
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = GetModuleHandle(NULL);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = pName;
	wndClass.hIcon = LoadIcon(NULL, IDC_ARROW);
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassExW(&wndClass);

	DWORD dwStyle = WS_OVERLAPPEDWINDOW;

	RECT Rect;
	Rect.left = 0;
	Rect.top = 0;
	Rect.right = width;
	Rect.bottom = height;
	// ウィンドウのスタイルに合わせた適切なサイズを取得する
	AdjustWindowRect(&Rect, dwStyle, false);

	width = Rect.right - Rect.left;
	height = Rect.bottom - Rect.top;

	// ウインドウの生成
	m_hWnd = CreateWindowW(wndClass.lpszClassName,
		pName,
		dwStyle,
		0,
		0,
		width,
		height,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		NULL);
	if (m_hWnd == NULL)
	{
		return false;
	}

	m_width = width;
	m_height = height;
	// ウインドウの表示
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return true;
}

// メッセージの更新
bool Window::UpdateMessage(void)
{
	MSG msg;
	// メッセージが存在するか確認
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		// 終了通知が来ている場合は抜ける
		if (msg.message == WM_QUIT)
		{
			m_isQuitMessage = true;
		}
		else
		{
			// メッセージをウインドウプロシージャに転送
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return true;
	}
	return false;
}
//
//void Window::ChangeDisplayMode(void)
//{
//	HRESULT hr = NULL;
//	m_isWindowMode = !m_isWindowMode;//違うモードを代入
//
//	if (m_isWindowMode) {
//		g_D3dPresentParameters = d3dppWin;
//	}
//	else {
//		g_D3dPresentParameters = d3dppFull;
//		GetWindowRect(hWnd, &WinRect);
//	}
//	hr = g_pD3Device->Reset(&g_D3dPresentParameters);
//	FreeDx();
//	soundsManager.Initialize();
//	BuildDXDevice();
//	//画像の引用
//	LoadTexture();
//	LoadFont();
//
//	if (FAILED(hr)) {
//		if (hr == D3DERR_DEVICELOST) {
//			DeviceLost = true;//名残
//		}
//		if (hr == D3DERR_DRIVERINTERNALERROR) {
//			DestroyWindow(hWnd);
//		}
//		return;
//	}
//
//	if (m_isWindowMode) {
//		SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);//
//		SetWindowPos(hWnd, HWND_NOTOPMOST,
//			WinRect.left, WinRect.top,
//			WinRect.right - WinRect.left,
//			WinRect.bottom - WinRect.top,
//			SWP_SHOWWINDOW);
//	}
//	else {
//		SetWindowLong(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
//	}
//}