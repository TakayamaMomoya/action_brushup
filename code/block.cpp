//*****************************************************
//
// �u���b�N�̏���[block.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "block.h"
#include "renderer.h"
#include "manager.h"
#include "object.h"
#include "collision.h"
#include <stdio.h>

//*****************************************************
// �}�N����`
//*****************************************************
#define SPEED_MOVE	(1.0f)	// �ړ����x
#define MAP_FILE	"data\\MAP\\map00.bin"	// �}�b�v�̃t�@�C���p�X

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CBlock *CBlock::m_apBlock[NUM_OBJECT] = {};	// �u���b�N�̔z��
int CBlock::m_nNumAll = 0;	// ����
int *CBlock::m_pIdxObject = nullptr;	// �ԍ��̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CBlock::CBlock(int nPriority)
{
	m_type = TYPE_FLOOR;

	for (int nCntBlock = 0;nCntBlock < NUM_OBJECT;nCntBlock++)
	{
		if (m_apBlock[nCntBlock] == nullptr)
		{// �ۑ��p�z��ɃR�s�[
			m_apBlock[nCntBlock] = this;

			break;
		}
	}

	m_nNumAll++;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CBlock::~CBlock()
{
	m_nNumAll--;
}

//=====================================================
// ����������
//=====================================================
HRESULT CBlock::Init(void)
{
	// �p���N���X�̏�����
	CObjectX::Init();

	// �^�C�v�̐ݒ�
	SetType(TYPE_BLOCK);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CBlock::Uninit(void)
{
	if (m_pCollisionCube != nullptr)
	{// �����蔻��̏���
		m_pCollisionCube->Uninit();

		m_pCollisionCube = nullptr;
	}

	// �p���N���X�̏I��
	CObjectX::Uninit();
}

//=====================================================
// �X�V����
//=====================================================
void CBlock::Update(void)
{
	// �p���N���X�̍X�V
	CObjectX::Update();
}

//=====================================================
// �`�揈��
//=====================================================
void CBlock::Draw(void)
{
	// �p���N���X�̕`��
	CObjectX::Draw();
}

//=====================================================
// ��������
//=====================================================
CBlock *CBlock::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot ,TYPE type)
{
	CBlock *pBlock = nullptr;

	if (type <= CBlock::TYPE_NONE && type >= CBlock::TYPE_MAX)
	{// �͈͊O�̎�ނ��n���ꂽ��nullptr��Ԃ�
		return nullptr;
	}

	if (pBlock == nullptr)
	{// �C���X�^���X����
		pBlock = new CBlock;

		pBlock->SetPosition(pos);
		pBlock->SetRot(rot);

		// ����������
		pBlock->m_type = type;
		pBlock->Init();

		// ��ނ��Ƃ̃��f���Ǎ�
		pBlock->SetIdxModel(m_pIdxObject[type]);
		pBlock->BindModel(m_pIdxObject[type]);

		if (pBlock->m_pCollisionCube == nullptr)
		{// �����蔻�萶��
			pBlock->m_pCollisionCube = CCollisionCube::Create(CCollision::TAG_BLOCK, pBlock);

			if (pBlock->m_pCollisionCube != nullptr)
			{
				pBlock->m_pCollisionCube->SetPosition(pBlock->GetPosition());

				pBlock->m_pCollisionCube->SetVtx(pBlock->GetVtxMax(), pBlock->GetVtxMin());
			}
		}
	}

	return pBlock;
}

//=====================================================
// �����폜
//=====================================================
void CBlock::Delete(int nIdx)
{
	if (m_apBlock[nIdx] != nullptr)
	{// �폜����
		m_apBlock[nIdx]->Uninit();

		m_apBlock[nIdx] = nullptr;
	}

	// �z����l�߂�
	for (int nCntBlock = nIdx; nCntBlock < NUM_OBJECT - 1; nCntBlock++)
	{
		if (m_apBlock[nCntBlock + 1] != nullptr)
		{
			m_apBlock[nCntBlock] = m_apBlock[nCntBlock + 1];
			m_apBlock[nCntBlock + 1] = nullptr;
		}
	}
}

//=====================================================
// �S�폜����
//=====================================================
void CBlock::DeleteAll(void)
{
	for (int nCntBlock = 0;nCntBlock < NUM_OBJECT;nCntBlock++)
	{
		if (m_apBlock[nCntBlock] != nullptr)
		{
			m_apBlock[nCntBlock] = nullptr;
		}
	}
}

//=====================================================
// �ԍ��폜����
//=====================================================
void CBlock::DeleteIdx(void)
{
	if (m_pIdxObject != nullptr)
	{// �ԍ��|�C���^�̔j��
		delete m_pIdxObject;
		m_pIdxObject = nullptr;
	}
}

//=====================================================
// �Ǎ�����
//=====================================================
HRESULT CBlock::Load(char *pPath)
{
	int nNumBlock;
	MemBlock memBlock;

	//�|�C���^�錾
	FILE *pFile;

	//�t�@�C�����J��
	pFile = fopen(pPath, "rb");

	if (pFile != nullptr)
	{//�t�@�C�����J�����ꍇ
		
		// ���̓Ǎ�
		fread(&nNumBlock, sizeof(int), 1, pFile);

		for (int nCntBlock = 0;nCntBlock < nNumBlock;nCntBlock++)
		{
			// �u���b�N�̓Ǎ�
			fread(&memBlock, sizeof(MemBlock), 1, pFile);

			// �u���b�N�̐���
			Create(memBlock.pos, memBlock.rot,memBlock.type);
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
	}

	return S_OK;
}

//=====================================================
// �e�̃`�F�b�N����
//=====================================================
float CBlock::CheckShadow(D3DXVECTOR3 pos)
{
	float fHeight = -1000;

	for (int i = 0; i < NUM_OBJECT; i++)
	{
		if (m_apBlock[i] != nullptr)
		{
			// �u���b�N�̏��擾
			D3DXVECTOR3 posBlock = m_apBlock[i]->GetPosition();
			D3DXVECTOR3 vtxMax = m_apBlock[i]->GetVtxMax() + posBlock;
			D3DXVECTOR3 vtxMin = m_apBlock[i]->GetVtxMin() + posBlock;

			if (pos.x >= vtxMin.x && pos.x <= vtxMax.x &&
				vtxMax.z >= pos.z && vtxMin.z <= pos.z)
			{// ���ȓ��ɂ���Ƃ�
				if (pos.y >= posBlock.y)
				{
					float fDiff = vtxMax.y - pos.y;
					float fDiffMax = fHeight - pos.y;

					if (fDiff * fDiff < fDiffMax * fDiffMax)
					{// �ŏ��̍�����菬����������
						fHeight = vtxMax.y;
					}
				}
			}
		}
	}

	return fHeight;
}

//=====================================================
// ���f���ԍ��Ǎ�����
//=====================================================
void CBlock::LoadModel(void)
{
	char *pPath[CBlock::TYPE_MAX] =
	{
		"data\\MODEL\\BLOCK\\floor.x",	// ��
		"data\\MODEL\\BLOCK\\chair00.x",	// �֎q
		"data\\MODEL\\BLOCK\\desk00.x",	// ��
		"data\\MODEL\\BLOCK\\document.x",	// ����
		"data\\MODEL\\BLOCK\\fun00.x",	// ���C��
		"data\\MODEL\\BLOCK\\locker00.x",	// ���b�J�[
		"data\\MODEL\\BLOCK\\window.x",	// ��
		"data\\MODEL\\BLOCK\\floorbig.x",	// �ł���
		"data\\MODEL\\BLOCK\\windowbig.x",	// �ł���
		"data\\MODEL\\BLOCK\\case00.x",	// ���ӂ���b
		"data\\MODEL\\BLOCK\\case01.x",	// ���ӂ���
		"data\\MODEL\\BLOCK\\case02.x",	// ���ӂ���
		"data\\MODEL\\BLOCK\\floor4.x",	// ���~�S
		"data\\MODEL\\BLOCK\\rooftopbig.x",	// ���㏰
		"data\\MODEL\\BLOCK\\rooftop4.x",	// ���㏰�~�S
		"data\\MODEL\\BLOCK\\rooftop1.x",	// ���㏰�~�P
		"data\\MODEL\\BLOCK\\heliport.x",	// �w���|�[�g
		"data\\MODEL\\BLOCK\\windowFront.x",	// ��O�̑�
		"data\\MODEL\\BLOCK\\windowside.x",	// ���̑�
		"data\\MODEL\\BLOCK\\wall.x",	// ��
		"data\\MODEL\\BLOCK\\wall2.x",	// ��2
		"data\\MODEL\\BLOCK\\wall3.x",	// ��3
		"data\\MODEL\\BLOCK\\windowsidebig.x",	// �ł�����
		"data\\MODEL\\BLOCK\\windowFront4.x",	// ��O��4
		"data\\MODEL\\BLOCK\\longdesk.x",	// ����
	};

	if (m_pIdxObject == nullptr)
	{
		// �ԍ��̐���
		m_pIdxObject = new int[CBlock::TYPE_MAX];

		// �l�̏�����
		ZeroMemory(m_pIdxObject,sizeof(int) * CBlock::TYPE_MAX);

		for (int nCntBlock = 0; nCntBlock < CBlock::TYPE_MAX; nCntBlock++)
		{
			m_pIdxObject[nCntBlock] = CModel::Load(pPath[nCntBlock]);
		}
	}
}

//=====================================================
// �ۑ�����
//=====================================================
void CBlock::Save(void)
{
	//�|�C���^�錾
	FILE *pFile;

	// ���󂯎��p�\����
	MemBlock memBlock;

	//�t�@�C�����J��
	pFile = fopen(MAP_FILE, "wb");

	if (pFile != nullptr)
	{//�t�@�C�����J�����ꍇ
		fwrite(&m_nNumAll, sizeof(int), 1, pFile);

		for (int nCntBlock = 0; nCntBlock < m_nNumAll; nCntBlock++)
		{
			if (m_apBlock[nCntBlock] != nullptr)
			{
				memBlock.pos = m_apBlock[nCntBlock]->GetPosition();
				memBlock.rot = m_apBlock[nCntBlock]->GetRot();
				memBlock.type = m_apBlock[nCntBlock]->m_type;

				//�o�C�i���t�@�C���ɏ�������
				fwrite(&memBlock, sizeof(MemBlock), 1, pFile);
			}
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ

	}
}