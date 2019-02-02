
/**
* @file CameraManager.cpp
* @brief CameraManagerクラスのソースファイル
* @author shion-sagawa
*/

#include "CameraManager.h"
#include "../GameLib.h"



CameraManager::CameraManager()
	: m_pCamera(nullptr)
{}

CameraManager::~CameraManager()
{
	Finalize();
}

//初期化
void CameraManager::Initialize()
{
	m_pCamera = nullptr;
}

//解放
void CameraManager::Finalize()
{
	// 最後は解放して終わる
	if (m_pCamera) { m_pCamera->Finalize(); }
	SAFE_DELETE(m_pCamera);
}

//カメラの更新
void CameraManager::Update()
{
	if (m_pCamera) m_pCamera->Update();
}

//カメラの変更
void CameraManager::ChangeCamera(CameraBase* pCamera)
{
	// 現在のシーンを解放する
	if (m_pCamera)
	{
		m_pCamera->Finalize();
		SAFE_DELETE(m_pCamera);
	}

	// 次のシーンがあれば初期化する
	if (pCamera)
	{
		pCamera->Initialize();
	}

	m_pCamera = pCamera;
}
