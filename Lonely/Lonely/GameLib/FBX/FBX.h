/**
* @file FBX.h
* @brief FBXクラスのヘッダファイル
* @author shion-sagawa
*/

#pragma once

#include <windows.h>
#include <stdio.h>

#include <vector>
#include <map>

#include <d3dx9.h>
#include <dinput.h>

#include <fbxsdk.h>

#include "FBX/3DHelper.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"


static const int MOTION_MAX = 256;
static const int BONE_MAX = 256;

// ボーン情報
struct Bone
{
	char		name[64];
	D3DXMATRIX	offset;
	D3DXMATRIX	transform;
};

// アニメーション
struct Motion
{
	Motion() {}

	UINT					numFrame;		// フレーム数
	std::vector<D3DXMATRIX> Key[BONE_MAX];	// キーフレーム
};


// FBXモデルクラス
class FbxModel: public Model
{
public:
	FbxModel(void);
	~FbxModel(void);

	// FBXメッシュの読み込み
	bool Load(const char* pFilename);
	// FBXメッシュの解放
	void Finalize(void);

	// FBXメッシュの描画
	void Render(void);


	// アニメーションの再生
	void Play(std::string name);
	// アニメーションの更新
	void Animate(float sec = 1.0f / 60.0f);

private:
	void Skinning(void);

	// FBXの解析
	bool LoadMesh(UINT meshIdx, FbxMesh* pMesh);
	void LoadIndeces(UINT meshIdx, FbxMesh* pMesh);
	void LoadPosition(UINT meshIdx, FbxMesh* pMesh);
	void LoadNormal(UINT meshIdx, FbxMesh* pMesh);
	void LoadUV(UINT meshIdx, FbxMesh* pMesh);
	void LoadColor(UINT meshIdx, FbxMesh* pMesh);
	void LoadMaterial(UINT matIdx, FbxMesh* pMesh);

	int FindBone(const char* pName);
	void LoadBone(UINT matIdx, FbxMesh* pMesh);
	void LoadKeyFrames(std::string name, int bone, FbxNode* pBoneNode);
	void LoadMotion(std::string name, const char* pFilename);

private:
	char							m_rootDir[MAX_PATH];	// ルートパス
	std::string						m_playMotion;			// モーション名
	float							m_frame;				// フレーム
	int								m_startFrame;			// 開始フレーム
	UINT							m_boneNum;				// ボーン数
	Bone							m_bone[BONE_MAX];		// ボーン情報
	std::map<std::string, Motion>	m_motion;				// モーション
	std::vector<MeshVertex*>		m_pVertices;			// 頂点データ
};
