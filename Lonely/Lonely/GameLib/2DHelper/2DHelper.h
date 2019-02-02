﻿///**
//* @file 2DHelper.h
//* @brief 2DHelperクラスのヘッダファイル
//* @author shion-sagawa
//*/
//
#pragma once

#include <windows.h>
//
//#include "../DirectX/DirectX.h"
//#include "../FBX/Texture.h"
//
//
//#define FVF_SIMPLE_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
//#define FVF_SIMPLE_TEX_2D   (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//
//

// シンプルなテクスチャ―付き頂点情報
struct Simple2DVertex
{
	float x, y, z;
	float rhw;
	DWORD color;
	float u, v;
};

/**
* @brief ２Dのゲームのよく使用する処理をまとめたクラス
*/
class Helper2D
{
public:

	Helper2D();
	~Helper2D();

	/**
	* @brief 中心点から横幅、縦幅を使って矩形を作る関数
	* @param 頂点情報
	* @param 中心点のX座標
	* @param 中心点のY座標
	* @param 中心点からの横幅
	* @param 中心点からの縦幅
	* @param 矩形の右のTU（デフォルトなら１を代入）
	* @param 矩形の下のTV（デフォルトなら１を代入）
	* @param 矩形の左のTU（デフォルトなら０を代入）
	* @param 矩形の上のTV（デフォルトなら０を代入）
	*/
	void SetVerticesFromCenterType(Simple2DVertex* vertices, float posCenterX, float posCenterY, float posWidthFromCenter, float posHeightFromCenter, float rightTU = 1.0f, float bottomTV = 1.0f, float leftTU = 0.0f, float topTV = 0.0f);

	/**
	* @brief 左上頂点から横幅、縦幅を使って矩形を作る関数
	* @param 頂点情報
	* @param 左上頂点のX座標
	* @param 左上頂点のY座標
	* @param 矩形の横幅
	* @param 矩形の縦幅
	* @param 矩形の右のTU（デフォルトなら１を代入）
	* @param 矩形の下のTV（デフォルトなら１を代入）
	* @param 矩形の左のTU（デフォルトなら０を代入）
	* @param 矩形の上のTV（デフォルトなら０を代入）
	*/
	void SetVerticesFromLeftTopType(Simple2DVertex* vertices, float posLeftTopX, float posLeftTopY, float rectWidth, float rectHeight, float rightTU = 1.0f, float bottomTV =1.0f, float leftTU = 0.0f, float topTV = 0.0f);

	/**
	* @brief ���㒸�_���牡���A�c�����g���ċ��`�������֐�
	* @param ���_����
	* @param ���㒸�_��X���W
	* @param ���㒸�_��Y���W
	* @brief 矩形4頂点のTUTVを変える関数
	* @param 頂点の先頭アドレス
	* @param 矩形の右のTU
	* @param 矩形の下のTV
	* @param 矩形の左のTU
	* @param 矩形の上のTV
	*/
	void SetVerticesFromLeftTopType(Simple2DVertex* vertices, float posLeftTopX, float posLeftTopY);
	void SetVerticesTuTv(Simple2DVertex* vertices, float rightTU, float bottomTV, float leftTU, float topTV);


	/**
	* @brief 矩形４頂点の色情報を変える関数
	* @param 頂点の先頭アドレス
	* @param 変えたい色情報（ARGB） 
	*/
	void SetVerticesColor(Simple2DVertex* vertices, DWORD color);

	/**
	* @brief １頂点の色情報を変える関数
	* @param 頂点の先頭アドレス
	* @param 変えたい色情報（ARGB）
	*/
	void SetVertexColor(Simple2DVertex* vertices, DWORD color);

private:

};
