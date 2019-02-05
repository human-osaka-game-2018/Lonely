/**
* @file TexStorage.h
* @brief テクスチャ管理クラスのヘッダ
* @author Harutaka-Tsujino
*/

#include "TexStorage.h"
#include "../GameLib.h"

TexStorage::TexStorage() 
{
	Initialize();
}

void TexStorage::Initialize()
{
	m_rpDX3D_DEV = GameLib::Instance.GetDirect3DDevice();

}
