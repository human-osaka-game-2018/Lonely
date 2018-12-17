/**
* @file TitleScene.cpp
* @brief TitleSceneクラスのソースファイル
* @author shion-sagawa
*/

#include "TitleScene.h"
#include "TitleBackGround.h"
#include "TitleLogo.h"
#include "TitleMenu/TitleMenu.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
	Finalize();
}

//操作を更新する
void TitleScene::Update()
{
	//シーンを切り替えるかどうかをチェックする


	//BGMを鳴らす
	bool isSuccess = soundsManager.Start(_T("TitleBGM"), true);

	//このシーンのオブジェクトの更新を行う
	m_pObjectManager->Update();

	//カメラUpdate
	//m_pCamera->Update();


}

//描画する
void TitleScene::Render()
{
	//オブジェクトのRender
	m_pObjectManager->Render();
}

//初期化する
bool TitleScene::Initialize()
{
	//オブジェクトをNEWして、オブまねのVectorにつめる
	m_pObjectManager->RegisterObject(new TitleBackground);
	m_pObjectManager->RegisterObject(new TitleMenu);
	m_pObjectManager->RegisterObject(new TitleLogo);

	// SoundsManagerインスタンス生成後に1度のみ行う。
	bool isSuccess = soundsManager.Initialize();
	// 音声ファイルオープン
	// 第2引数は音声ファイルを識別するための任意の文字列をキーとして指定する。
	// この後の操作関数の呼び出し時には、ここで設定したキーを指定して音声を識別する。
	const TCHAR* filePath = _T("../Sounds/BGM/TitleBGM.mp3");
	isSuccess = soundsManager.AddFile(filePath, _T("TitleBGM"));

	return true;
}

//解放する
void TitleScene::Finalize()
{
	m_pObjectManager->ReleaseObject();

	bool isSuccess = soundsManager.Stop(_T("TitleBGM"));
	SoundLibCWrapper_Free();
}
