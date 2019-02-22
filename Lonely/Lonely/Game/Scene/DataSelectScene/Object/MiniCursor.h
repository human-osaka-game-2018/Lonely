/**
* @file MiniCursor.h
* @brief MiniCursor�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include "../../../../GameLib/ObjectManager/Object2DBase.h"
#include "../../../../GameLib/DirectX/DirectX.h"
#include "../SelectCursorInformation/SelectCursorInformation.h"

/**
* @brief �~�j�J�[�\���̏������܂Ƃ߂��N���X
*/
class MiniCursor : public Object2DBase
{
public:

	MiniCursor();
	~MiniCursor();

	explicit MiniCursor(SelectCursorInformation* instance);

	/**
	* @brief ����������֐�
	* @return ����������肭�ł��Ă��Ȃ���FALSE
	*/
	bool Initialize();

	/**
	* @brief �������֐�
	*/
	void Finalize();

	/**
	* @brief ����֐�
	*/
	void Update();

	/**
	* @brief �`��֐�
	*/
	void Render();

private:

	SelectCursorInformation * m_pSelectCursorInformation;

};

