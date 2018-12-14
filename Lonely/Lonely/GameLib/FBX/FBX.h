/**
* @file FBX.h
* @brief FBX�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include ".\\3DHelper.h"
#include <fbxsdk.h>
#include <vector>
#include <map>
#include <windows.h>
#include <stdio.h>
#include <d3dx9.h>
#include <dinput.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dinput8.lib")


static const int MOTION_MAX = 256;
static const int BONE_MAX = 256;

// �{�[�����
struct Bone
{
	char		name[64];
	D3DXMATRIX	offset;
	D3DXMATRIX	transform;
};

//	�A�j���[�V����
struct Motion
{
	Motion() {}

	UINT					numFrame;		// �t���[����
	std::vector<D3DXMATRIX> Key[BONE_MAX];	// �L�[�t���[��
};


// FBX���f���N���X
class FbxModel: public Model
{
public:
	FbxModel(void);
	~FbxModel(void);

	// FBX���b�V���̓ǂݍ���
	bool Load(const char* pFilename);
	// FBX���b�V���̉��
	void Finalize(void);

	// FBX���b�V���̕`��
	void Render(void);


	// �A�j���[�V�����̍Đ�
	void Play(std::string name);
	// �A�j���[�V�����̍X�V
	void Animate(float sec = 1.0f / 60.0f);

private:
	void Skinning(void);

	// FBX�̉��
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
	char							m_rootDir[MAX_PATH];	// ���[�g�p�X
	std::string						m_playMotion;			// ���[�V������
	float							m_frame;				// �t���[��
	int								m_startFrame;			// �J�n�t���[��
	UINT							m_boneNum;				// �{�[����
	Bone							m_bone[BONE_MAX];		// �{�[�����
	std::map<std::string, Motion>	m_motion;				// ���[�V����
	std::vector<MeshVertex*>		m_pVertices;			// ���_�f�[�^
};
