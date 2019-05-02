/**
* @file 2DHelper.cpp
* @brief 2DHelperクラスのソースファイル
* @author shion-sagawa
*/

#include "2DHelper.h"

Helper2D::Helper2D()
{
}

Helper2D::~Helper2D()
{
}

//中心点から横幅縦幅を使って、矩形を作る関数
void Helper2D::SetVerticesFromCenterType(Simple2DVertex* vertices, float posCenterX, float posCenterY, float posWidthFromCenter, float posHeightFromCenter, float rightTU, float bottomTV, float leftTU, float topTV)
{
	vertices[0] = { posCenterX - posWidthFromCenter,  posCenterY - posHeightFromCenter, 0.0f, 1.0f, 0xffffffff,  leftTU,    topTV };
	vertices[1] = { posCenterX + posWidthFromCenter,  posCenterY - posHeightFromCenter, 0.0f, 1.0f, 0xffffffff, rightTU,    topTV };
	vertices[2] = { posCenterX + posWidthFromCenter,  posCenterY + posHeightFromCenter, 0.0f, 1.0f, 0xffffffff, rightTU, bottomTV };
	vertices[3] = { posCenterX - posWidthFromCenter,  posCenterY + posHeightFromCenter, 0.0f, 1.0f, 0xffffffff,  leftTU, bottomTV };
}

//左上頂点から横幅縦幅を使って、矩形を作る関数
void Helper2D::SetVerticesFromLeftTopType(Simple2DVertex* vertices, float posLeftTopX, float posLeftTopY, float rectWidth, float rectHeight, float rightTU, float bottomTV, float leftTU, float topTV)
{
	vertices[0] = { posLeftTopX            ,  posLeftTopY             , 0.0f, 1.0f, 0xffffffff,  leftTU,    topTV };
	vertices[1] = { posLeftTopX + rectWidth,  posLeftTopY             , 0.0f, 1.0f, 0xffffffff, rightTU,    topTV };
	vertices[2] = { posLeftTopX + rectWidth,  posLeftTopY + rectHeight, 0.0f, 1.0f, 0xffffffff, rightTU, bottomTV };
	vertices[3] = { posLeftTopX            ,  posLeftTopY + rectHeight, 0.0f, 1.0f, 0xffffffff,  leftTU, bottomTV };
}

//頂点情報の位置だけをセットし直す関数
void Helper2D::SetVerticesFromLeftTopType(Simple2DVertex* vertices, float posLeftTopX, float posLeftTopY)
{
	//頂点の位置とセットし直したい位置の差分を計算
	float movementX = vertices[0].x - posLeftTopX;
	float movementY = vertices[0].y - posLeftTopY;
	
	//その差分をすべての頂点に適応させる
	vertices[0].x = vertices[0].x - movementX;
	vertices[0].y = vertices[0].y - movementY;

	vertices[1].x = vertices[1].x - movementX;
	vertices[1].y = vertices[1].y - movementY;

	vertices[2].x = vertices[2].x - movementX;
	vertices[2].y = vertices[2].y - movementY;

	vertices[3].x = vertices[3].x - movementX;
	vertices[3].y = vertices[3].y - movementY;
}

//TU、TVを変える関数
void Helper2D::SetVerticesTuTv(Simple2DVertex* vertices, float rightTU, float bottomTV, float leftTU, float topTV)
{
	vertices[0].u = leftTU;
	vertices[0].v = topTV;
	vertices[1].u = rightTU;
	vertices[1].v = topTV;
	vertices[2].u = rightTU;
	vertices[2].v = bottomTV;
	vertices[3].u = leftTU;
	vertices[3].v = bottomTV;
}

//矩形の色情報を変える関数
void Helper2D::SetVerticesColor(Simple2DVertex* vertices, DWORD color)
{
	vertices[0].color = color;
	vertices[1].color = color;
	vertices[2].color = color;
	vertices[3].color = color;
}

//1頂点の色情報を変える関数
void Helper2D::SetVertexColor(Simple2DVertex* vertices, DWORD color)
{
	vertices->color = color;
}

//指定したカウントでアルファ値を下げてくれる関数
bool Helper2D::DecrementVerticesAlpha(Simple2DVertex* vertices
	, int* currentDecrementCount
	, const int duration
	, const int startingDecrementCount
	, const bool repeat)
{
	if (*currentDecrementCount >= duration || startingDecrementCount >= duration)
	{
		return false;
	}

	//　減少時間        = 所要時間 - 減算し始める時間
	int decrementCount = duration - startingDecrementCount;

	//減少時間でアルファ値が０に近い値になるように、減らす量を計算
	DWORD decrementAlpha = 0x000000ff / decrementCount;
	decrementAlpha = decrementAlpha << 24;
	
	//算出したアルファ値を引く
	if (*currentDecrementCount >= startingDecrementCount)
	{
		vertices[0].color -= decrementAlpha;
		vertices[1].color -= decrementAlpha;
		vertices[2].color -= decrementAlpha;
		vertices[3].color -= decrementAlpha;
	}

	//カウントを増やす
	++*currentDecrementCount;

	//目的の所要時間までカウントが達していたらTRUEを返す
	if (*currentDecrementCount >= duration && repeat == false)
	{
		*currentDecrementCount = 0;
		return true;
	}//繰り返すように設定されていたら、アルファ値を初期化してTRUEを返す
	else if (*currentDecrementCount >= duration && repeat == true)
	{
		*currentDecrementCount = 0;
		vertices[0].color = 0xffffffff;
		vertices[1].color = 0xffffffff;
		vertices[2].color = 0xffffffff;
		vertices[3].color = 0xffffffff;

		return true;
	}

	return false;
}
