/**
* @file Sumahoneko.cpp
* @brief Sumahonekoクラスのソースファイル
* @author shion-sagawa
*/

#include "Sumahoneko.h"
#include "../../../GameLib/GameLib.h"

Sumahoneko::Sumahoneko()
{
	Initialize();
}

Sumahoneko::~Sumahoneko()
{
	Finalize();
}

//初期化する
bool Sumahoneko::Initialize()
{
	m_fbxStage.Load("../Graphics/stage2_1.fbx");
	m_fbxModel.Load("../Graphics/sumahoneko.fbx");
	m_shpere.CreateShpere(32);

	m_playerRadius = 0.1f;
	m_playerSpeed = 0.1f;
	return true;
}

//解放する
void Sumahoneko::Finalize()
{
	m_fbxModel.Finalize();
	m_fbxStage.Finalize();
	m_shpere.Finalize();
}

//更新する
void Sumahoneko::Update()
{

}

//描画する
void Sumahoneko::Render()
{
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	// 通常書き込みモードに設定
	pDirectX->SetRenderMode(DirectX::Normal, false);

	// Zテストの比較方法
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// モデルの描画
	m_fbxModel.Render();
	m_fbxStage.Render();
}
