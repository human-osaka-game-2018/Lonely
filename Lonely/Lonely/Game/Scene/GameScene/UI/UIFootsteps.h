/**
* @file UIFootsteps.h
* @brief UIFootsteps�N���X�̃w�b�_�t�@�C��
* @author shion-sagawa
*/

#pragma once

#include "../../../../GameLib/ObjectManager/Object2DBase.h"
#include "../../../../GameLib/DirectX/DirectX.h"
#include "../../../../GameLib/2DHelper/2DHelper.h"


/**
* @brief �������m�֌W���܂Ƃ߂��N���X
*/
class UIFootsteps : public Object2DBase
{
public:

	UIFootsteps();
	~UIFootsteps();

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

};
