///**
//* @file Main.cpp
//* @brief Lonely��Main.cpp
//* @author ����@�k��
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
//#define WINDOW_MODE						// �E�B���h�E���[�h(�ʏ�)
//
//#define WINDOW_TITLE TEXT("Lonely")		// �E�B���h�E�^�C�g��
//#define CLIENT_SIZE_W 1280				// �N���C�A���g�T�C�Y�̕�
//#define CLIENT_SIZE_H 720 				// �N���C�A���g�T�C�Y�̍���
//#define GAME_FPS (1000 / 60)			// �Q�[��FPS
//#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
//
//LPDIRECT3D9 pD3d;
//LPDIRECT3DDEVICE9 pDevice;
//LPDIRECTINPUT8 pDinput = NULL;//�L�[���͂̂��߂̕ϐ�
//LPDIRECTINPUTDEVICE8 pKeyDevice = NULL;
//LPDIRECTINPUTDEVICE8 pMouseDevice = NULL;
//
//HRESULT InitDinput(HWND hWnd);
//HRESULT InitD3d(HWND hWnd);
//
//// �v���V�[�W���֐�
//LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
//
//// �G���g���|�C���g
//INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
//{
//	// ���������[�N���o
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//
//	MSG msg;
//
//	//-------------------------------------------------------------------//
//	//				         �E�B���h�E����
//	//-------------------------------------------------------------------//	
////#ifdef WINDOW_MODE		//	�E�B���h�E���[�h(�ʏ�)
////	GameLib::Instance().InitGameLib(WINDOW_TITLE, CLIENT_SIZE_W, CLIENT_SIZE_H, WindowProc, false);
////#else					//�@�t���X�N���[�����[�h
////	GameLib::Instance().InitGameLib(WINDOW_TITLE, CLIENT_SIZE_W, CLIENT_SIZE_H, WindowProc, true);
////#endif
////
//	HWND hWnd = NULL;
//	MSG msg;
//	// �E�B���h�E�̏�����
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
//	// �_�C���N�g�RD�̏������֐����Ă�
//	if (FAILED(InitD3d(hWnd)))
//	{
//		return 0;
//	}
//	//�_�C���N�g�C���v�b�g�̏������֐����Ă�
//	if (FAILED(InitDinput(hWnd))) {
//		return 0;
//	}
//
//	//�V�[���}�l�[�W���̐���
//	SceneManager* pSceneManager = SceneManager::GetInstance();
//	//�I�u�W�F�N�g�}�l�[�W���̐���
//	//ObjectManager* pObjectManager = ObjectManager::GetInstance();
//
//	//-------------------------------------------------------------------//
//	//						���b�Z�[�W���[�v
//	//-------------------------------------------------------------------//
//
//	DWORD currentTime;						// ���݂̎���
//	DWORD oldTime = timeGetTime();			// �O�̎���
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
//				//�L�[Update
//				m_pInput->Update();
//				pSceneManager->DevideSceneOperation();
//				oldTime = timeGetTime();
//			}
//		}
//	}
//
//	//�V�[���}�l�[�W���̃C���X�^���X��j������
//	pSceneManager->ReleaseInstance();
//
//	//GameLib::Instance().ReleaseGameLib();
//
//	// ���b�Z�[�W���[�v���甲������I�u�W�F�N�g��S�ĊJ������
//	FreeDx();
//	// OS�ɖ߂�i�A�v���P�[�V�������I������j
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
//// �쐬����DirectX�I�u�W�F�N�g�̊J��
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
////�_�C���N�g�C���v�b�g�̏������֐�
//HRESULT InitDinput(HWND hWnd)
//{
//	HRESULT hr;
//	//�uDirectInput�v�I�u�W�F�N�g�̍쐬
//	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDinput, NULL)))
//	{
//		return hr;
//	}
//	//�uDirectInput�f�o�C�X�v
//	if (FAILED(hr = pDinput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, NULL)))
//	{
//		return hr;
//	}
//	//�f�o�C�X���L�[�{�[�h�ɐݒ�
//	if (FAILED(hr = pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
//	{
//		return hr;
//	}
//	//�������x���̐ݒ�
//	if (FAILED(hr = pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
//	{
//		return hr;
//	}
//	////�f�o�C�X���u�擾�v����
//	//pKeyDevice->Acquire();
//
//	//�f�o�C�X�𐶐�
//	if (FAILED(hr = pDinput->CreateDevice(GUID_SysMouse,
//		&pMouseDevice, NULL)))
//	{
//		return hr;
//	}
//
//	//�f�o�C�X���}�E�X�ɐݒ�
//	if (FAILED(hr = pMouseDevice->SetDataFormat(&c_dfDIMouse)))
//	{
//		return hr;
//	}
//	//�������x���̐ݒ�
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
//	//�f�o�C�X���擾
//	//pMouseDevice->Acquire();
//	//pMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &g_mouseState.directInputMouseState);
//
//	return S_OK;
//}
//
////HRESULT InitD3d(HWND hWnd)
////�_�C���N�g3D�̏������֐�
//HRESULT InitD3d(HWND hWnd)
//{
//	// �uDirect3D�v�I�u�W�F�N�g�̍쐬
//	if (NULL == (pD3d = Direct3DCreate9(D3D_SDK_VERSION)))
//	{
//		MessageBox(0, _T("Direct3D�̍쐬�Ɏ��s���܂���"),_T(""), MB_OK);
//		return E_FAIL;
//	}
//	// �uDIRECT3D�f�o�C�X�v�I�u�W�F�N�g�̍쐬
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
//		MessageBox(0, _T("HAL���[�h��DIRECT3D�f�o�C�X���쐬�ł��܂���\nREF���[�h�ōĎ��s���܂�"), NULL, MB_OK);
//		if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
//			D3DCREATE_MIXED_VERTEXPROCESSING,
//			&d3dpp, &pDevice)))
//		{
//			MessageBox(0, _T("DIRECT3D�f�o�C�X�̍쐬�Ɏ��s���܂���"), NULL, MB_OK);
//			return E_FAIL;
//		}
//	}
//	// Z�o�b�t�@�[������L���ɂ���
//	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
//	// ���C�g��L���ɂ���
//	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
//	// �A���r�G���g���C�g�i�����j��ݒ肷��
//	pDevice->SetRenderState(D3DRS_AMBIENT, 0x00808080);
//	// �X�y�L�����i���ʔ��ˁj��L���ɂ���
//	pDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
//	return S_OK;
//}