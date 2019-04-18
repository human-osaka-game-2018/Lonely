/**
* @file TitleScene.cpp
* @brief TitleSceneクラスのソースファイル
* @author shion-sagawa
*/

#include "TitleScene.h"

#include "GameLib.h"

#include "TitleBackGround.h"
#include "TitleLogo.h"
#include "TitleMenu/TitleMenu.h"

TitleScene::TitleScene()
	: m_pSoundsManager(GameLib::Instance.GetSoundsManager())
{
}

TitleScene::~TitleScene()
{
	Finalize();
}

//操作を更新する
void TitleScene::Update()
{
	//このシーンのオブジェクトの操作の更新する
	m_pObjectManager->Update();
}

//描画する
void TitleScene::Render()
{
	//このシーンのオブジェクトの描画を更新する
	m_pObjectManager->Render();
}

//初期化する
bool TitleScene::Initialize()
{
	//このシーンで使うオブジェクトを生成し、ObjectManagerに登録する
	m_pObjectManager->RegisterObject(new TitleBackground);
	m_pObjectManager->RegisterObject(new TitleMenu);
	m_pObjectManager->RegisterObject(new TitleLogo);

	//音声を読み込むし、追加する
	const TCHAR* filePath = _T("../Sounds/BGM/sepianokaze.mp3");
	m_pSoundsManager->AddFile(filePath, _T("TitleBGM"));

	//BGMを鳴らす
	m_pSoundsManager->Start(_T("TitleBGM"), true);

	return true;
}

//解放する
void TitleScene::Finalize()
{
	m_pObjectManager->ReleaseObject();

	m_pSoundsManager->Stop(_T("TitleBGM"));
}
