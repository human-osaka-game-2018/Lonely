/**
* @file FBX.cpp
* @brief FBXクラスのソースファイル
* @author shion-sagawa
*/


#include "../GameLib.h"
#define FBXSDK_SHARED
#include "FBX.h"
#include <stdio.h>

#pragma comment( lib, "libfbxsdk.lib")

#define	SAFE_DESTROY(x)	{ if(x) { (x)->Destroy(); (x) = NULL; } }


FbxModel::FbxModel(void)
	: m_frame(0.0f)
	, m_startFrame(0)
	, m_boneNum(0)
	, m_pVertices(NULL)
{
}
FbxModel::~FbxModel(void)
{
	Finalize();
}

// FBXの読み込み
bool FbxModel::Load(const char* pFileName)
{
	strcpy_s(m_rootDir, pFileName);
	size_t i;
	for (i = strlen(m_rootDir); 0 < i; i--)
	{
		if (m_rootDir[i] == '/') break;
	}
	m_rootDir[i] = '\0';

	// FBXのマネージャーとインポーターの生成
	FbxManager* pManager = FbxManager::Create();
	FbxScene* pScene = FbxScene::Create(pManager, "");

	// ファイルのインポート
	FbxImporter* pImpoter = FbxImporter::Create(pManager, "");
	pImpoter->Initialize(pFileName);
	pImpoter->Import(pScene);
	SAFE_DESTROY(pImpoter);


	fbxsdk::FbxGeometryConverter converter(pManager);
	// マテリアルと1メッシュ毎に分ける
	converter.SplitMeshesPerMaterial(pScene, true);
	// 全てを三角形にする
	converter.Triangulate(pScene, true);

	// メッシュ分のバッファを確保
	UINT meshNum = (UINT)pScene->GetSrcObjectCount<FbxMesh>();
	// マテリアル分のバッファを確保
	UINT materialNum = meshNum;

	// モデルの初期化
	Initialize(meshNum, materialNum);

	m_boneNum = 0;
	ZeroMemory(m_bone, sizeof(m_bone));

	//	モーション情報取得
	FbxArray<FbxString*> names;
	pScene->FillAnimStackNameArray(names);

	int StartFrame = 0;
	if (names != NULL) {
		//	モーションが存在するとき
		FbxTakeInfo* take = pScene->GetTakeInfo(names[0]->Buffer());
		FbxLongLong start = take->mLocalTimeSpan.GetStart().Get();
		FbxLongLong stop = take->mLocalTimeSpan.GetStop().Get();
		FbxLongLong fps60 = FbxTime::GetOneFrameValue(FbxTime::eFrames60);
		StartFrame = (int)(start / fps60);

		m_motion["default"].numFrame = (int)((stop - start) / fps60);
	}
	m_startFrame = StartFrame;


	m_pVertices.resize(meshNum);
	// メッシュ単位で展開していく
	for (UINT i = 0; i < meshNum; i++)
	{
		FbxMesh* pMesh = pScene->GetSrcObject<FbxMesh>(i);

		LoadMesh(i, pMesh);
		LoadMaterial(i, pMesh);
		LoadBone(i, pMesh);

		MeshData* pMeshData = GetMesh(i);
		pMeshData->materialIndex = i;

		UINT size = (UINT)(pMeshData->vertexNum * sizeof(MeshVertex));
		MeshVertex* pVertices;
		// バッファをロックしてデータを書き込む
		pMeshData->vertexBuffer.GetBuffer()->Lock(0, size, (void**)&pVertices, 0);

		m_pVertices[i] = new MeshVertex[size];
		memcpy(m_pVertices[i], pVertices, size);

		pMeshData->vertexBuffer.GetBuffer()->Unlock();
	}


	SAFE_DESTROY(pScene);
	SAFE_DESTROY(pManager);

	Play("default");

	return true;
}

// メッシュの解放
void FbxModel::Finalize(void)
{
	for (size_t i = 0; i < m_pVertices.size(); i++)
	{
		SAFE_DELETE(m_pVertices[i]);
	}

	std::map<std::string, Motion> empty;
	m_motion.swap(empty);

	Model::Finalize();
}

// FBXメッシュの描画
void FbxModel::Render(void)
{
	Skinning();

	Model::Render();
}

void FbxModel::Play(std::string name)
{
	m_playMotion = name;
	m_frame = 0.0f;
}

void FbxModel::Animate(float sec)
{
	//	モーション時間の更新
	m_frame += sec * 60.0f;

	//	ループチェック
	if (m_frame >= m_motion[m_playMotion].numFrame - 1)
	{
		// ループ
		m_frame = 0;
	}
}


//	ボーン行列の補間
static void MatrixInterporate(D3DXMATRIX& out, D3DXMATRIX& A, D3DXMATRIX B, float rate)
{
	out = A * (1.0f - rate) + B * rate;
}

void FbxModel::Skinning(void)
{
	if (m_motion.empty()) return;

	Motion* pMotion = &m_motion[m_playMotion];
	if (pMotion == NULL) return;
	if (pMotion->numFrame < 0) return;

	float Frame = m_frame;
	//	配列用変数
	int f = (int)Frame;
	//	行列準備
	D3DXMATRIX KeyMatrix[256];
	for (UINT b = 0; b < m_boneNum; b++)
	{
		if (pMotion->Key[b].empty()) continue;
		//	行列補間
		D3DXMATRIX m;
		MatrixInterporate(m, pMotion->Key[b][f], pMotion->Key[b][f + 1], Frame - (int)Frame);
		m_bone[b].transform = m;
		//	キーフレーム
		KeyMatrix[b] = m_bone[b].offset * m;
	}

	//	頂点変形
	for (UINT meshIdx = 0; meshIdx < m_meshNum; meshIdx++)
	{
		MeshData* pMeshData = GetMesh(meshIdx);
		MeshVertex* pSrcVertices = m_pVertices[meshIdx];

		UINT size = (UINT)(pMeshData->vertexNum * sizeof(MeshVertex));
		MeshVertex* pVertices = NULL;
		// バッファをロックしてデータを書き込む
		pMeshData->vertexBuffer.GetBuffer()->Lock(0, size, (void**)&pVertices, 0);
		if (pVertices == NULL) {
			continue;
		}
		for (UINT v = 0; v < pMeshData->vertexNum; v++)
		{
			//	頂点 * ボーン行列
			// b = v番目の頂点の影響ボーン[n]
			if (pVertices[v].weight[0] <= 0) continue;

			pVertices[v].x = 0;
			pVertices[v].y = 0;
			pVertices[v].z = 0;

			//	影響個数分ループ
			for (int n = 0; n < 4; n++)
			{
				if (pVertices[v].weight[n] <= 0) break;

				int b = (int)pVertices[v].index[n];

				float x = pSrcVertices[v].x;
				float y = pSrcVertices[v].y;
				float z = pSrcVertices[v].z;
				//	座標を影響力分移動
				pVertices[v].x += (x*KeyMatrix[b]._11 + y * KeyMatrix[b]._21 + z * KeyMatrix[b]._31 + 1 * KeyMatrix[b]._41)*pVertices[v].weight[n];
				pVertices[v].y += (x*KeyMatrix[b]._12 + y * KeyMatrix[b]._22 + z * KeyMatrix[b]._32 + 1 * KeyMatrix[b]._42)*pVertices[v].weight[n];
				pVertices[v].z += (x*KeyMatrix[b]._13 + y * KeyMatrix[b]._23 + z * KeyMatrix[b]._33 + 1 * KeyMatrix[b]._43)*pVertices[v].weight[n];

				float nx = pSrcVertices[v].nx;
				float ny = pSrcVertices[v].ny;
				float nz = pSrcVertices[v].nz;
				//	法線を影響力分変換
				pVertices[v].nx += (nx*KeyMatrix[b]._11 + ny * KeyMatrix[b]._21 + nz * KeyMatrix[b]._31)*pVertices[v].weight[n];
				pVertices[v].ny += (nx*KeyMatrix[b]._12 + ny * KeyMatrix[b]._22 + nz * KeyMatrix[b]._32)*pVertices[v].weight[n];
				pVertices[v].nz += (nx*KeyMatrix[b]._13 + ny * KeyMatrix[b]._23 + nz * KeyMatrix[b]._33)*pVertices[v].weight[n];
			}
		}
		pMeshData->vertexBuffer.GetBuffer()->Unlock();
	}
}

// FBXの解析
bool FbxModel::LoadMesh(UINT meshIdx, FbxMesh* pMesh)
{
	LoadIndeces(meshIdx, pMesh);

	LoadPosition(meshIdx, pMesh);
	LoadUV(meshIdx, pMesh);
	LoadColor(meshIdx, pMesh);
	LoadNormal(meshIdx, pMesh);

	return true;
}


void FbxModel::LoadIndeces(UINT meshIdx, FbxMesh* pMesh)
{
	MeshData* pMeshData = GetMesh(meshIdx);

	int polyCount = pMesh->GetPolygonCount();
	UINT size = (UINT)((polyCount * 3) * sizeof(UINT16));

	pMeshData->fvf = FVF_MESH_TEX_VERTEX;
	pMeshData->primType = D3DPT_TRIANGLELIST;
	pMeshData->primNum = (UINT)polyCount;
	pMeshData->indexNum = (UINT)(polyCount * 3);
	pMeshData->indexBuffer.Create(size);

	IDirect3DIndexBuffer9* pIndexBuffer = pMeshData->indexBuffer.GetBuffer();
	UINT16* pIndeces;
	// バッファをロックしてデータを書き込む
	pIndexBuffer->Lock(0, size, (void**)&pIndeces, 0);

	for (int polyIdx = 0; polyIdx < polyCount; polyIdx++)
	{
		pIndeces[polyIdx * 3 + 0] = polyIdx * 3 + 2;
		pIndeces[polyIdx * 3 + 1] = polyIdx * 3 + 1;
		pIndeces[polyIdx * 3 + 2] = polyIdx * 3 + 0;
	}
	pIndexBuffer->Unlock();
}

void FbxModel::LoadPosition(UINT meshIdx, FbxMesh* pMesh)
{
	MeshData* pMeshData = GetMesh(meshIdx);

	int vertexNum = pMesh->GetPolygonVertexCount();
	UINT size = (UINT)(vertexNum * sizeof(MeshVertex));

	FbxVector4* source = pMesh->GetControlPoints();
	// メッシュのトランスフォーム
	FbxVector4 T = pMesh->GetNode()->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4 R = pMesh->GetNode()->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4 S = pMesh->GetNode()->GetGeometricScaling(FbxNode::eSourcePivot);
	FbxAMatrix TRS = FbxAMatrix(T, R, S);
	//	全頂点変換
	for (int v = 0; v < pMesh->GetControlPointsCount(); v++)
	{
		source[v] = TRS.MultT(source[v]);
	}

	pMeshData->vertexNum = (UINT)vertexNum;
	pMeshData->vertexStride = sizeof(MeshVertex);
	pMeshData->vertexBuffer.Create(size);

	IDirect3DVertexBuffer9* pVertexBuffer = pMeshData->vertexBuffer.GetBuffer();
	MeshVertex* pVertices;
	// バッファをロックしてデータを書き込む
	pVertexBuffer->Lock(0, size, (void**)&pVertices, 0);

	int* pIndex = pMesh->GetPolygonVertices();
	for (int vtxIdx = 0; vtxIdx < vertexNum; vtxIdx++)
	{
		int index = pIndex[vtxIdx];
		FbxVector4& pos = source[index];

		pVertices[vtxIdx].x = -static_cast<float>(pos[0]);
		pVertices[vtxIdx].y = static_cast<float>(pos[1]);
		pVertices[vtxIdx].z = static_cast<float>(pos[2]);
		pVertices[vtxIdx].nx = 0.0f;
		pVertices[vtxIdx].ny = 1.0f;
		pVertices[vtxIdx].nz = 0.0f;
		pVertices[vtxIdx].u = 0.0f;
		pVertices[vtxIdx].v = 0.0f;
		pVertices[vtxIdx].color = 0xffffff;
	}
	pVertexBuffer->Unlock();
}

void FbxModel::LoadNormal(UINT meshIdx, FbxMesh* pMesh)
{
	MeshData* pMeshData = GetMesh(meshIdx);

	FbxArray<FbxVector4> normals;
	pMesh->GetPolygonVertexNormals(normals);

	UINT size = pMeshData->vertexNum * sizeof(MeshVertex);

	IDirect3DVertexBuffer9* pVertexBuffer = pMeshData->vertexBuffer.GetBuffer();

	MeshVertex* pVertices;
	// バッファをロックしてデータを書き込む
	pVertexBuffer->Lock(0, size, (void**)&pVertices, 0);

	for (int vtxIdx = 0; vtxIdx < normals.Size(); vtxIdx++)
	{
		FbxVector4& normal = normals[vtxIdx];

		pVertices[vtxIdx].nx = -static_cast<float>(normal[0]);
		pVertices[vtxIdx].ny = static_cast<float>(normal[1]);
		pVertices[vtxIdx].nz = static_cast<float>(normal[2]);
	}
	pVertexBuffer->Unlock();
}

void FbxModel::LoadUV(UINT meshIdx, FbxMesh* pMesh)
{
	MeshData* pMeshData = GetMesh(meshIdx);

	FbxStringList uvSetNames;
	pMesh->GetUVSetNames(uvSetNames);

	FbxArray<FbxVector2> uvSets;
	pMesh->GetPolygonVertexUVs(uvSetNames.GetStringAt(0), uvSets);

	UINT size = pMeshData->vertexNum * sizeof(MeshVertex);
	IDirect3DVertexBuffer9* pVertexBuffer = pMeshData->vertexBuffer.GetBuffer();

	MeshVertex* pVertices;
	// バッファをロックしてデータを書き込む
	pVertexBuffer->Lock(0, size, (void**)&pVertices, 0);

	for (int vtxIdx = 0; vtxIdx < uvSets.Size(); vtxIdx++)
	{
		FbxVector2& uvSet = uvSets[vtxIdx];

		pVertices[vtxIdx].u = static_cast<float>(uvSet[0]);
		pVertices[vtxIdx].v = static_cast<float>(1.0 - uvSet[1]);
	}
	pVertexBuffer->Unlock();
}

void FbxModel::LoadColor(UINT meshIdx, FbxMesh* pMesh)
{
	MeshData* pMeshData = GetMesh(meshIdx);

	int colorElementCount = pMesh->GetElementVertexColorCount();
	if (colorElementCount == 0) return;

	FbxGeometryElementVertexColor* pColor = pMesh->GetElementVertexColor(0);

	FbxLayerElement::EMappingMode mapMode = pColor->GetMappingMode();
	FbxLayerElement::EReferenceMode refMode = pColor->GetReferenceMode();

	if (mapMode == FbxLayerElement::eByPolygonVertex)
	{
		if (refMode == FbxLayerElement::eIndexToDirect)
		{
			IDirect3DVertexBuffer9* pVertexBuffer = pMeshData->vertexBuffer.GetBuffer();

			UINT size = pMeshData->vertexNum * sizeof(MeshVertex);
			MeshVertex* pVertices;
			// バッファをロックしてデータを書き込む
			pVertexBuffer->Lock(0, size, (void**)&pVertices, 0);

			FbxLayerElementArrayTemplate<FbxColor>& colors = pColor->GetDirectArray();
			FbxLayerElementArrayTemplate<int>& indeces = pColor->GetIndexArray();
			for (int i = 0; i < indeces.GetCount(); i++)
			{
				FbxColor color = colors.GetAt(indeces.GetAt(i));
				DWORD a = (DWORD)(color.mAlpha * 255.0);
				DWORD r = (DWORD)(color.mRed   * 255.0);
				DWORD g = (DWORD)(color.mGreen * 255.0);
				DWORD b = (DWORD)(color.mBlue  * 255.0);

				pVertices[i].color = (a << 24) + (r << 16) + (g << 8) + (b);
			}
			pVertexBuffer->Unlock();
		}
	}
}

void FbxModel::LoadMaterial(UINT matIdx, FbxMesh* pMesh)
{
	FbxLayerElementMaterial* pElementMaterial = pMesh->GetElementMaterial();
	if (pElementMaterial)
	{
		// マテリアル解析
		int index = pElementMaterial->GetIndexArray().GetAt(0);

		FbxSurfaceMaterial* pMaterial = pMesh->GetNode()->GetSrcObject<FbxSurfaceMaterial>(index);
		if (pMaterial)
		{
			FbxProperty prop = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);

			//	テクスチャ読み込み
			const char* filename = NULL;
			int fileTextureCount = prop.GetSrcObjectCount<FbxFileTexture>();
			if (fileTextureCount > 0) {
				FbxFileTexture* FileTex = prop.GetSrcObject<FbxFileTexture>(0);
				filename = FileTex->GetFileName();
			}
			else {
				int numLayer = prop.GetSrcObjectCount<FbxLayeredTexture>();
				if (numLayer > 0) {
					FbxLayeredTexture* LayerTex = prop.GetSrcObject<FbxLayeredTexture>(0);
					FbxFileTexture* FileTex = LayerTex->GetSrcObject<FbxFileTexture>(0);
					filename = FileTex->GetFileName();
				}
			}
			if (filename == NULL) return;

			//	テクスチャーの取得
			char* pFileName;
			size_t size = 0;
			FbxUTF8ToAnsi(filename, pFileName, &size);

			// PSDが使用されている場合は読めないのでTGAで試す
			char* ext = (char*)strstr(pFileName, ".psd");
			if (ext)
			{
				strcpy_s(ext, 5, ".tga");
			}

			char path[MAX_PATH];
			if (strstr(pFileName, "\\"))
			{
				strcpy_s(path, pFileName);
			}
			else
			{
				strcpy_s(path, m_rootDir);
				strcat_s(path, "/texture/");
				strcat_s(path, pFileName);
			}
			GetMaterial(matIdx)->texture.Load(path);

			FbxFree(pFileName);
		}
	}
}

int FbxModel::FindBone(const char* pName)
{
	for (UINT boneIdx = 0; boneIdx < m_boneNum; boneIdx++)
	{
		if (strcmp(m_bone[boneIdx].name, pName) == 0)
		{
			return (int)boneIdx;
		}
	}
	return -1;
}

void FbxModel::LoadBone(UINT matIdx, FbxMesh* pMesh)
{
	MeshData* pMeshData = GetMesh(matIdx);
	// スキン情報の有無
	int skinCount = pMesh->GetDeformerCount(FbxDeformer::eSkin);
	if (skinCount <= 0)
	{
		return;
	}
	int vertexNum = pMeshData->vertexNum;
	UINT size = (UINT)(vertexNum * sizeof(MeshVertex));

	MeshVertex* pVertices;
	// バッファをロックしてデータを書き込む
	pMeshData->vertexBuffer.GetBuffer()->Lock(0, size, (void**)&pVertices, 0);

	FbxSkin* pSkin = (FbxSkin*)pMesh->GetDeformer(0, FbxDeformer::eSkin);
	// ボーン数
	int nBone = pSkin->GetClusterCount();
	//	全ボーン情報取得
	for (int bone = 0; bone < nBone; bone++)
	{
		//	ボーン情報取得
		FbxCluster* pCluster = pSkin->GetCluster(bone);
		FbxAMatrix trans;
		pCluster->GetTransformMatrix(trans);
		trans.mData[0][1] *= -1;
		trans.mData[0][2] *= -1;
		trans.mData[1][0] *= -1;
		trans.mData[2][0] *= -1;
		trans.mData[3][0] *= -1;

		//	ボーン名取得
		const char* pName = pCluster->GetLink()->GetName();

		Bone* pBone;
		//	ボーン検索
		int bone_no = FindBone(pName);
		if (bone_no != -1)
		{
			pBone = &m_bone[bone_no];
		}
		else
		{
			bone_no = m_boneNum;
			pBone = &m_bone[bone_no];
			m_boneNum++;

			strcpy_s(pBone->name, pName);
			//	オフセット行列作成
			FbxAMatrix LinkMatrix;
			pCluster->GetTransformLinkMatrix(LinkMatrix);
			LinkMatrix.mData[0][1] *= -1;
			LinkMatrix.mData[0][2] *= -1;
			LinkMatrix.mData[1][0] *= -1;
			LinkMatrix.mData[2][0] *= -1;
			LinkMatrix.mData[3][0] *= -1;

			FbxAMatrix Offset = LinkMatrix.Inverse() * trans;
			FbxDouble* OffsetM = (FbxDouble*)Offset;

			//	オフセット行列保存
			for (int i = 0; i < 16; i++)
			{
				pBone->offset.m[i / 4][i % 4] = static_cast<float>(OffsetM[i]);
			}
			//	キーフレーム読み込み
			LoadKeyFrames("default", bone_no, pCluster->GetLink());
		}

		//	ウェイト読み込み
		int weightCount = pCluster->GetControlPointIndicesCount();
		int* pWeightIndex = pCluster->GetControlPointIndices();
		double* wgt = pCluster->GetControlPointWeights();

		int* index = pMesh->GetPolygonVertices();


		for (int i = 0; i < weightCount; i++)
		{
			int wgtIdx2 = pWeightIndex[i];
			//	全ポリゴンからwgtIdx2番目の頂点検索
			for (int vtxIdx = 0; vtxIdx < vertexNum; vtxIdx++)
			{
				if (index[vtxIdx] != wgtIdx2) continue;
				//	頂点にウェイト保存
				int weightCount;
				for (weightCount = 0; weightCount < 4; weightCount++)
				{
					if (pVertices[vtxIdx].weight[weightCount] <= 0.0f)
					{
						break;
					}
				}
				if (4 <= weightCount) continue;

				pVertices[vtxIdx].index[weightCount] = bone_no;
				pVertices[vtxIdx].weight[weightCount] = static_cast<float>(wgt[i]);
			}
		}
	}
	//	ウェイト正規化
	// ５本以上にまたっがてる場合のため
	for (int vtxIdx = 0; vtxIdx < vertexNum; vtxIdx++)
	{
		float n = 0;
		int weightCount;
		//	頂点のウェイトの合計値
		for (weightCount = 0; weightCount < 4; weightCount++)
		{
			if (pVertices[vtxIdx].weight[weightCount] <= 0.0f)
			{
				break;
			}
			n += pVertices[vtxIdx].weight[weightCount];
		}
		//	正規化
		for (weightCount = 0; weightCount < 4; weightCount++)
		{
			pVertices[vtxIdx].weight[weightCount] /= n;
		}
	}
	pMeshData->vertexBuffer.GetBuffer()->Unlock();
}

void FbxModel::LoadKeyFrames(std::string name, int bone, FbxNode* pBoneNode)
{
	//	メモリ確保
	Motion* pMotion = &m_motion[name];
	pMotion->Key[bone].resize(pMotion->numFrame);

	double time = (double)m_startFrame * (1.0 / 60);
	FbxTime T;
	for (UINT f = 0; f < pMotion->numFrame; f++)
	{
		T.SetSecondDouble(time);
		//	T秒の姿勢行列をGet
		FbxMatrix m = pBoneNode->EvaluateGlobalTransform(T);
		m.mData[0][1] *= -1;// _12
		m.mData[0][2] *= -1;// _13
		m.mData[1][0] *= -1;// _21
		m.mData[2][0] *= -1;// _31
		m.mData[3][0] *= -1;// _41

		FbxDouble* mat = (FbxDouble*)m;
		for (int i = 0; i < 16; i++)
		{
			pMotion->Key[bone][f].m[i / 4][i % 4] = static_cast<float>(mat[i]);
		}

		time += 1.0 / 60.0;
	}
}

void FbxModel::LoadMotion(std::string name, const char* pFilename)
{
	FbxManager* pManager = FbxManager::Create();
	FbxScene* pScene = FbxScene::Create(pManager, "");

	//	ファイルからシーンに読み込み
	FbxImporter* pImporter = FbxImporter::Create(pManager, "");
	pImporter->Initialize(pFilename);
	pImporter->Import(pScene);
	pImporter->Destroy();

	//	モーション情報取得
	FbxArray<FbxString*> names;
	pScene->FillAnimStackNameArray(names);

	FbxTakeInfo* take = pScene->GetTakeInfo(names[0]->Buffer());
	FbxLongLong start = take->mLocalTimeSpan.GetStart().Get();
	FbxLongLong stop = take->mLocalTimeSpan.GetStop().Get();
	FbxLongLong fps60 = FbxTime::GetOneFrameValue(FbxTime::eFrames60);

	m_startFrame = (int)(start / fps60);
	m_motion[name].numFrame = (int)((stop - start) / fps60);
	//	ルートノード取得
	FbxNode* root = pScene->GetRootNode();

	//	全ボーン読み込み
	for (int b = 0; b < (int)m_boneNum; b++)
	{
		//	ボーンノード検索
		FbxNode* pBone = root->FindChild(m_bone[b].name);
		if (pBone == NULL) continue;

		//	キーフレーム読み込み
		LoadKeyFrames(name, b, pBone);
	}
	//	解放
	pScene->Destroy();
	pManager->Destroy();
}

