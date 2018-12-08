/**
* @file SceneBase.h
* @brief SceneBaseクラスのヘッダファイル
* @author 佐川 嗣苑
*/

#include "SceneBase.h"
#include "../../GameLib.h"

SceneBase::SceneBase()
	: m_pObjectManager(GameLib::Instance.GetObjectManager())
{
}

SceneBase::~SceneBase()
{
}
