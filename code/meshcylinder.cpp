//*****************************************************
//
//meshcylinder.cpp
//Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "meshcylinder.h"
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
#define MESHCYLINDER_TEX_FILE		"data\\TEXTURE\\EFFECT\\boost.png"				// �e�N�X�`���t�@�C����
#define MESH_LENGTH					(10.0f)									// ���b�V���̈�ӂ̒���
#define MESH_U						(256)										// ���̃u���b�N��
#define MESH_V						(1)											// �c�̃u���b�N��
#define SPLIT_TEX_U					(3)											// ���̃e�N�X�`��������
#define SPLIT_TEX_V					(1)											// �c�̃e�N�X�`��������
#define MESH_HEIGHT	(50.0f)	// ���b�V���̍���
#define ADD_HEIGHT	(100.0f)	// �ڕW����̍���
#define WAVE_ANGLE	(D3DX_PI * 0.1f)	// �g�ł͈͂̊p�x
#define WAVE_HEIGHT	(50.0f)	// �g�ł���
#define WAVE_LENGTH	(100.0f)	// �g�ł͈͂̋���

//=====================================================
// �R���X�g���N�^
//=====================================================
CMeshCylinder::CMeshCylinder(int nPriority) : CObject(nPriority)
{
	ZeroMemory(&m_meshCylinder, sizeof(m_meshCylinder));
	m_pIdxBuff = nullptr;
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_col = { 0.0f,0.0f,0.0f,0.0f };
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CMeshCylinder::~CMeshCylinder()
{

}

//=====================================================
// ��������
//=====================================================
CMeshCylinder *CMeshCylinder::Create(void)
{
	CMeshCylinder *pMeshCylinder = nullptr;

	if (pMeshCylinder == nullptr)
	{
		pMeshCylinder = new CMeshCylinder;

		if (pMeshCylinder != nullptr)
		{
			pMeshCylinder->Init();
		}
	}

	return pMeshCylinder;
}

//=====================================================
//����������
//=====================================================
HRESULT CMeshCylinder::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (MESH_U + 1) * (MESH_V + 1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * ((MESH_U + 1) * (MESH_V + 1) + ((MESH_V + 1) - 2) * (MESH_U + 1) + (((MESH_V + 1) - 2) * 2)),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	// �e�N�X�`���̓Ǎ�
	D3DXCreateTextureFromFile
	(pDevice, MESHCYLINDER_TEX_FILE, &m_pTexture);

	//���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	WORD *pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//�ő咸�_���v�Z
	m_meshCylinder.nNumVtx = (MESH_U + 1) * (MESH_V + 1);

	//�ϐ�������
	m_meshCylinder.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_meshCylinder.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�v�Z�p�ϐ�
	float fRot;
	D3DXVECTOR3 VecRot;

	//���_���==================================================================================
	for (int nCountV = 0; nCountV < MESH_V + 1; nCountV++)
	{//���_���W�̐ݒ�
		for (int nCountU = 0; nCountU < MESH_U + 1; nCountU++)
		{
			//�p�x�Z�o
			fRot = nCountU * (D3DX_PI / MESH_U) * 2;

			pVtx[nCountV * (MESH_U + 1) + nCountU].pos.x = (float)sin(fRot) * MESH_LENGTH;
			pVtx[nCountV * (MESH_U + 1) + nCountU].pos.y = (MESH_V - nCountV) * MESH_HEIGHT;
			pVtx[nCountV * (MESH_U + 1) + nCountU].pos.z = cosf(fRot) * MESH_LENGTH;

			//�e�N�X�`�����W
			pVtx[nCountV * (MESH_U + 1) + nCountU].tex = D3DXVECTOR2
			(
				((float)SPLIT_TEX_U / MESH_U) * nCountU,
				((float)SPLIT_TEX_V / MESH_V) * nCountV
			);

			VecRot = D3DXVECTOR3
			(
				pVtx[nCountV * (MESH_U + 1) + nCountU].pos.x,
				0.0f,
				pVtx[nCountV * (MESH_U + 1) + nCountU].pos.z
			);

			//�x�N�g�����K��
			D3DXVec3Normalize(&VecRot, &VecRot);

			//�@���x�N�g���̐ݒ�
			pVtx[nCountV * (MESH_U + 1) + nCountU].nor = VecRot;
		}
	}

	for (int nCnt = 0; nCnt < m_meshCylinder.nNumVtx; nCnt++)
	{
		//���_�J���[�̐ݒ�
		pVtx[nCnt].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	//�C���f�b�N�X==================================================================================
	m_meshCylinder.nNumIdx = (MESH_U + 1) * (MESH_V + 1) + ((MESH_V + 1) - 2) * (MESH_U + 1) + (((MESH_V + 1) - 2) * 2);

	for (int nCount = 0; nCount < m_meshCylinder.nNumIdx / 2; nCount++)
	{//�C���f�b�N�X����
		if (
			nCount % ((MESH_U + 1) + (MESH_U + 2) * (nCount / (MESH_U + 2))) == 0
			&& nCount != 0
			)
		{
			pIdx[nCount * 2 + 1] = ((MESH_U + 1) * 2) + (MESH_U + 1) * (nCount / (MESH_U + 2));

			pIdx[nCount * 2] = MESH_U + (MESH_U + 1) * (nCount / (MESH_U + 2));
		}
		else
		{
			pIdx[nCount * 2 + 1] = nCount - (nCount / (MESH_U + 2));

			pIdx[nCount * 2] = (nCount - (nCount / (MESH_U + 2))) + (MESH_U + 1);
		}
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuff->Unlock();

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CMeshCylinder::Uninit(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	if (m_pVtxBuff != NULL)
	{//���_�o�b�t�@�|�C���^�̔j��
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	if (m_pIdxBuff != NULL)
	{//�C���f�b�N�X�o�b�t�@�|�C���^�̔j��
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CMeshCylinder::Update(void)
{

}

//=====================================================
// �`�揈��
//=====================================================
void CMeshCylinder::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �J�����O�𖳌���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&m_meshCylinder.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_meshCylinder.rot.y, m_meshCylinder.rot.x, m_meshCylinder.rot.z);
	D3DXMatrixMultiply(&m_meshCylinder.mtxWorld, &m_meshCylinder.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_meshCylinder.pos.x, m_meshCylinder.pos.y, m_meshCylinder.pos.z);
	D3DXMatrixMultiply(&m_meshCylinder.mtxWorld, &m_meshCylinder.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_meshCylinder.mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���`��
	pDevice->DrawIndexedPrimitive
	(
		D3DPT_TRIANGLESTRIP,
		0,
		0,
		m_meshCylinder.nNumVtx,								//���_��
		0,													//�ŏ��̃C���f�b�N�X
		m_meshCylinder.nNumIdx - 2							//�|���S����
	);

	// �J�����O��L����
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}