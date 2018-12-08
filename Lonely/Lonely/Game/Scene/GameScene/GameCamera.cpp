/**
* @file GameCamera.cpp
* @brief GameCamera�N���X�̃\�[�X�t�@�C��
* @author ����
*/

#include "GameCamera.h"
#include "../../../GameLib/GameLib.h"


GameCamera::GameCamera()
{
}

GameCamera::~GameCamera()
{
}

//����������
bool GameCamera::Initialize()
{
	m_position = { 0.f,0.f,0.f };
	m_lookAt = { 1.0f,0.f,0.f };
	m_rotation = { 0.f,0.f,0.f };
	m_perspective = D3DX_PI / 4;

	return true;
}

//�������
void GameCamera::Finalize()
{

}

//�X�V����
void GameCamera::Update()
{
	IDirect3DDevice9* pDevice = GameLib::Instance.GetDirect3DDevice();
	DirectX* pDirectX = GameLib::Instance.GetDirectX();

	//���[���h�g�����X�t�H�[���i��΍��W�ϊ��j
	D3DXMATRIXA16 matWorld, matMovement;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matMovement);

	/*D3DXMatrixTranslation(&matMovement,
	pThing->vecPosition.x,
	pThing->vecPosition.y,
	pThing->vecPosition.z);
	*/

	D3DXMatrixMultiply(&matWorld, &matWorld, &matMovement);

	pDevice->SetTransform(D3DTS_WORLD, &matWorld);


	// �r���[�g�����X�t�H�[���i���_���W�ϊ��j
	D3DXVECTOR3 vecEyePt(m_position.x, m_position.y, m_position.z);//�J�����i���_�j�ʒu
	D3DXVECTOR3 vecLookatPt(m_lookAt.x, m_lookAt.y, m_lookAt.z);//�����ʒu
	D3DXVECTOR3 vecUpVec(0.0f, 1.0f, 0.0f);//����ʒu

	D3DXMATRIXA16 matView, matRotationY;

	D3DXMatrixRotationY(&matRotationY, m_rotation.y);
	D3DXVec3TransformCoord(&vecEyePt, &vecEyePt, &matRotationY); //�S�s��ƂR�s���������֐�

	D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);

	pDevice->SetTransform(D3DTS_VIEW, &matView);


	// �v���W�F�N�V�����g�����X�t�H�[���i�ˉe�ϊ��j

	D3DXMatrixPerspectiveFovLH(&m_matProjection, m_perspective, 1.0f, 1.0f, 100.0f);
	pDevice->SetTransform(D3DTS_PROJECTION, &m_matProjection);


	// ���C�g�����Ă� ���F�ŋ��ʔ��˂���ɐݒ�
	D3DXVECTOR3 vecDirection(0, 0, 1);
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Specular.r = 1.0f;
	light.Specular.g = 1.0f;
	light.Specular.b = 1.0f;
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDirection);
	light.Range = 200.0f;


	pDevice->SetLight(0, &light);
	pDevice->LightEnable(0, TRUE);

}
