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
	return true;
	//m_pObjectManager->RegisterObject(new Cursor);
	//m_pObjectManager->RegisterObject(new TitleMenu);
	//m_pObjectManager->RegisterObject(new TitleMenu2);
}

//解放する
void TitleScene::Finalize()
{
	m_pObjectManager->ReleaseObject();
}
