/**
* @file 2DHelper.cpp
* @brief 2DHelper�N���X�̃\�[�X�t�@�C��
* @author shion-sagawa
*/

#include "2DHelper.h"

Helper2D::Helper2D()
{
}

Helper2D::~Helper2D()
{
}

//���S�_���牡���c�����g���āA��`�����֐�
void Helper2D::SetVerticesFromCenterType(Simple2DVertex* vertices, float posCenterX, float posCenterY, float posWidthFromCenter, float posHeightFromCenter, float rightTU, float bottomTV, float leftTU, float topTV)
{
	vertices[0] = { posCenterX - posWidthFromCenter,  posCenterY - posHeightFromCenter, 0.0f, 1.0f, 0xffffffff,  leftTU,    topTV };
	vertices[1] = { posCenterX + posWidthFromCenter,  posCenterY - posHeightFromCenter, 0.0f, 1.0f, 0xffffffff, rightTU,    topTV };
	vertices[2] = { posCenterX + posWidthFromCenter,  posCenterY + posHeightFromCenter, 0.0f, 1.0f, 0xffffffff, rightTU, bottomTV };
	vertices[3] = { posCenterX - posWidthFromCenter,  posCenterY + posHeightFromCenter, 0.0f, 1.0f, 0xffffffff,  leftTU, bottomTV };
}

//���㒸�_���牡���c�����g���āA��`�����֐�
void Helper2D::SetVerticesFromLeftTopType(Simple2DVertex* vertices, float posLeftTopX, float posLeftTopY, float rectWidth, float rectHeight, float rightTU, float bottomTV, float leftTU, float topTV)
{
	vertices[0] = { posLeftTopX            ,  posLeftTopY             , 0.0f, 1.0f, 0xffffffff,  leftTU,    topTV };
	vertices[1] = { posLeftTopX + rectWidth,  posLeftTopY             , 0.0f, 1.0f, 0xffffffff, rightTU,    topTV };
	vertices[2] = { posLeftTopX + rectWidth,  posLeftTopY + rectHeight, 0.0f, 1.0f, 0xffffffff, rightTU, bottomTV };
	vertices[3] = { posLeftTopX            ,  posLeftTopY + rectHeight, 0.0f, 1.0f, 0xffffffff,  leftTU, bottomTV };
}


//��`�̐F����ς���֐�
void Helper2D::SetVerticesColor(Simple2DVertex* vertices, DWORD color)
{
	vertices[0].color = color;
	vertices[1].color = color;
	vertices[2].color = color;
	vertices[3].color = color;
}

//1���_�̐F����ς���֐�
void Helper2D::SetVertexColor(Simple2DVertex* vertices, DWORD color)
{
	vertices->color = color;
}
