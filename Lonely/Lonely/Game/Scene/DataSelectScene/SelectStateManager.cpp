/**
* @file SelectStateManager.cpp
* @brief SelectStateManagerクラスのソースファイル
* @author shion-sagawa
*/

#include "SelectStateManager.h"

SelectStateManager::SelectStateManager()
{
}

SelectStateManager::~SelectStateManager()
{
	//オブジェクトの全開放の関数を呼ぶ
}

//初期化する
void SelectStateManager::Initialize()
{
}

//解放する
void SelectStateManager::Finalize()
{
	ReleaseObject();
}

//このクラスを派生したクラスの操作関数を呼ぶ
void SelectStateManager::Update()
{
	for (int i = 0; i < m_pObjectVec.size(); i++)
	{
		m_pObjectVec[i]->Update();
	}
}

//このクラスを派生したクラスの描画関数を呼ぶ
void SelectStateManager::Render()
{
	for (int i = 0; i < m_pObjectVec.size(); i++) {
		m_pObjectVec[i]->Render();
	}
}

//このクラスを派生したクラスを登録する
void SelectStateManager::RegisterObject(Object* object)
{
	m_pObjectVec.push_back(object);
}

//このクラスを派生したクラスを解放する
void SelectStateManager::ReleaseObject()
{
	//Vector配列の要素が０なら関数から抜ける
	if (m_pObjectVec.size() == 0)
	{
		return;
	}

	for (Object* pI : m_pObjectVec)
	{
		delete pI;
	}

	//要素数を０にする
	m_pObjectVec.clear();
	//キャパシティーを０にする
	m_pObjectVec.shrink_to_fit();
}
