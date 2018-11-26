/**
* @file Object.h
* @brief Object�N���X�̃w�b�_�t�@�C��
* @author ����
*/

#pragma once

#include <vector>

/**
* @brief Object�̊��N���X
*/
class Object
{
public:

	Object();
	virtual ~Object();

	/**
	* @brief ���������s���֐�
	*/
	virtual bool Initialize();

	/**
	* @brief ������s���֐�
	*/
	virtual void Finalize();

	/**
	* @brief ����̍X�V���s���֐�
	*/
	virtual void Update();

	/**
	* @brief �`����s���֐�
	*/
	virtual void Render();

private:

};
