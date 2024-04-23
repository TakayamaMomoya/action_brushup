//*****************************************************
//
// ���[�_�[�̏���[rader.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "shockwave.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "debugproc.h"
#include "universal.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define MESHCYLINDER_TEX_FILE		"data\\TEXTURE\\BG\\sky000.png"				// �e�N�X�`���t�@�C����
#define MESH_LENGTH					(230.0f)									// ���b�V���̈�ӂ̒���
#define MESH_U						(256)										// ���̃u���b�N��
#define MESH_V						(1)	// �c�̃u���b�N��
#define SPLIT_TEX_U					(3)	// ���̃e�N�X�`��������
#define SPLIT_TEX_V					(1)	// �c�̃e�N�X�`��������
#define MESH_HEIGHT	(10.0f)	// ���b�V���̍���
#define ADD_HEIGHT	(100.0f)	// �ڕW����̍���
#define WAVE_ANGLE	(D3DX_PI * 0.1f)	// �g�ł͈͂̊p�x
#define WAVE_HEIGHT	(50.0f)	// �g�ł���
#define WAVE_LENGTH	(100.0f)	// �g�ł͈͂̋���
#define CHANGE_COl	(0.15f)	// �F�̕ς�銄��
#define RAND_HEIGHT	(5.0f)	// �U��镝
#define WAVE_SIZE	(0.04f)	// �g�̑傫��
#define SHAKE_SIZE	(0.005f)	// �h��̑傫��

//=====================================================
// �R���X�g���N�^
//=====================================================
CShockWave::CShockWave(void)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CShockWave::~CShockWave()
{

}

//=====================================================
// ��������
//=====================================================
CShockWave *CShockWave::Create(void)
{
	CShockWave *pShockWave = nullptr;

	if (pShockWave == nullptr)
	{
		pShockWave = new CShockWave;

		if (pShockWave != nullptr)
		{
			pShockWave->Init();
		}
	}

	return pShockWave;
}

//=====================================================
//����������
//=====================================================
HRESULT CShockWave::Init(void)
{
	// �p���N���X�̏�����
	CMeshCylinder::Init();

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CShockWave::Uninit(void)
{
	// �p���N���X�̏I��
	CMeshCylinder::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CShockWave::Update(void)
{
	// �p���N���X�̍X�V
	CMeshCylinder::Update();

	// �g�`�ɓ�������
	Wave();
}

//=====================================================
// �g�`�ɓ�������
//=====================================================
void CShockWave::Wave(void)
{
	// ���_�o�b�t�@�擾
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = CMeshCylinder::GetVtxBuff();

	// ���_���̃|�C���^
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MESH_U + 1; nCnt++)
	{// �S���_���`�F�b�N
		D3DXVECTOR3 pos;

		pVtx[nCnt].tex.y += 0.03f;
		pVtx[nCnt + MESH_U + 1].tex.y += 0.03f;

		//pos = pVtx[nCnt].pos;
		//D3DXVec3Normalize(&pos,&pos);
		//pVtx[nCnt].pos.x += pos.x;
		//pVtx[nCnt].pos.z += pos.z;

		//pos = pVtx[nCnt + MESH_U + 1].pos;
		//D3DXVec3Normalize(&pos, &pos);
		//pVtx[nCnt + MESH_U + 1].pos.x += pos.x;
		//pVtx[nCnt + MESH_U + 1].pos.z += pos.z;
	}

	// ���̓�_����������
	pVtx[MESH_U].pos = pVtx[0].pos;
	pVtx[MESH_U * 2 + 1].pos = pVtx[MESH_U + 1].pos;

	// ���_�o�b�t�@���A�����b�N
	pVtxBuff->Unlock();
}

//=====================================================
// �`�揈��
//=====================================================
void CShockWave::Draw(void)
{
	CMeshCylinder::Draw();
}