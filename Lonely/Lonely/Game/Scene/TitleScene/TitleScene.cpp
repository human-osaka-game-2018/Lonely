/**
* @file TitleScene.h
* @brief TitleSceneクラスのヘッダファイル
* @author 佐川　嗣苑
*/

#include "TitleScene.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

//操作を更新する
void TitleScene::Update()
{
	//オブジェクトUpdate 
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
	m_pObjectManager->ResisterObject(new TitleBackGround);
	return true;
	//return true;
	//m_pObjectManager->ResisterObject(new TitleLogo);
	//m_pObjectManager->ResisterObject(new Cursor);
	//m_pObjectManager->ResisterObject(new TitleMenu1);
	//m_pObjectManager->ResisterObject(new TitleMenu2);
}

//解放する
void TitleScene::Finalize()
{

}