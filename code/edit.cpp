//*****************************************************
//
// �G�f�B�^�[�̏���[edit.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "edit.h"
#include "objectX.h"
#include "inputkeyboard.h"
#include "manager.h"
#include "debugproc.h"
#include "block.h"
#include "enemy.h"
#include "enemyManager.h"
#include <assert.h>

//*****************************************************
// �}�N����`
//*****************************************************
#define SPEED_MOVE	(0.5f)	// �ړ����x
#define SPEED_ROTATION	(0.01f)	// ��]

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CEdit *CEdit::m_pEdit = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CEdit::CEdit()
{
	m_pObjectCursor = nullptr;
	m_nIdxObject = 0;
	m_type = CBlock::TYPE_FLOOR;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEdit::~CEdit()
{

}

//=====================================================
// ��������
//=====================================================
CEdit *CEdit::Create(void)
{
	if (m_pEdit == nullptr)
	{// �C���X�^���X����
		m_pEdit = new CEdit;

		// ����������
		m_pEdit->Init();
	}

	return m_pEdit;
}

//=====================================================
// ����������
//=====================================================
HRESULT CEdit::Init(void)
{
	// �ԍ��擾
	int *pIdx = CBlock::GetIndex();

	m_pObjectCursor = nullptr;

	m_pObjectCursor = CObjectX::Create();

	// �^�C�v�̏����ݒ�
	m_type = CBlock::TYPE_FLOOR;

	// ���f���ԍ��̐ݒ�
	m_pObjectCursor->SetIdxModel(pIdx[m_type]);
	m_pObjectCursor->BindModel(pIdx[m_type]);

	m_pObjectCursor->SetEmissiveCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CEdit::Uninit(void)
{
	if (m_pObjectCursor != nullptr)
	{
		m_pObjectCursor->Uninit();
		m_pObjectCursor = nullptr;
	}

	m_pEdit = nullptr;

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CEdit::Update(void)
{
	// �ԍ��擾
	int *pIdx = CBlock::GetIndex();

	// ���擾
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();

	// �ϐ��錾
	D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f };
	float fSpeed = SPEED_MOVE;
	CBlock **pBlock = CBlock::GetBlock();

	if (m_pObjectCursor != nullptr && pKeyboard != nullptr)
	{
		if (pKeyboard->GetPress(DIK_RSHIFT))
		{
			fSpeed *= 5.0f;
		}

		if (pKeyboard->GetPress(DIK_J))
		{
			pos.x -= fSpeed;
		}
		if (pKeyboard->GetPress(DIK_L))
		{
			pos.x += fSpeed;
		}
		if (pKeyboard->GetPress(DIK_I))
		{
			pos.z += fSpeed;
		}
		if (pKeyboard->GetPress(DIK_K))
		{
			pos.z -= fSpeed;
		}
		if (pKeyboard->GetPress(DIK_U))
		{
			pos.y += fSpeed;
		}
		if (pKeyboard->GetPress(DIK_O))
		{
			pos.y -= fSpeed;
		}

		// ��]
		if (pKeyboard->GetPress(DIK_N))
		{
			rot.y += SPEED_ROTATION;
		}
		if (pKeyboard->GetPress(DIK_M))
		{
			rot.y -= SPEED_ROTATION;
		}

		if (pKeyboard->GetTrigger(DIK_B))
		{
			m_pObjectCursor->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}

		if (pKeyboard->GetTrigger(DIK_RETURN))
		{// �u���b�N�̐���
			CBlock::Create(m_pObjectCursor->GetPosition(), m_pObjectCursor->GetRot(),m_type);
		}

		if (pKeyboard->GetTrigger(DIK_BACKSPACE))
		{// �G�̐���
			CEnemyManager *pEnemyManager = nullptr;

			pEnemyManager = CEnemyManager::GetInstance();

			if (pEnemyManager != nullptr)
			{
				pEnemyManager->CreateEnemy(m_pObjectCursor->GetPosition(), CEnemy::TYPE_DRONE);
			}
		}

		if (pKeyboard->GetTrigger(DIK_0) && CBlock::GetNumAll() != 0)
		{// �I�u�W�F�N�g�I������
			if (pBlock[m_nIdxObject] != nullptr)
			{
				pBlock[m_nIdxObject]->ResetColor();
			}

			m_nIdxObject = (m_nIdxObject + 1) % CBlock::GetNumAll();

			if (pBlock[m_nIdxObject] != nullptr)
			{
				pBlock[m_nIdxObject]->SetEmissiveCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			}
		}

		if (pKeyboard->GetTrigger(DIK_MINUS) && CBlock::GetNumAll() != 0)
		{// �I�u�W�F�N�g�I������
			if (pBlock[m_nIdxObject] != nullptr)
			{
				pBlock[m_nIdxObject]->ResetColor();
			}
			
			m_nIdxObject = (m_nIdxObject + CBlock::GetNumAll() - 1) % CBlock::GetNumAll();

			if (pBlock[m_nIdxObject] != nullptr)
			{
				pBlock[m_nIdxObject]->SetEmissiveCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			}
		}

		if (pKeyboard->GetTrigger(DIK_6))
		{
			m_type = (CBlock::TYPE)((m_type + CBlock::TYPE_MAX - 1) % CBlock::TYPE_MAX);

			// ���f���ԍ��̐ݒ�
			m_pObjectCursor->SetIdxModel(pIdx[m_type]);
			m_pObjectCursor->BindModel(pIdx[m_type]);
		}

		if (pKeyboard->GetTrigger(DIK_7))
		{// �u���b�N�^�C�v�؂�ւ�
			m_type = (CBlock::TYPE)((m_type + 1) % CBlock::TYPE_MAX);

			// ���f���ԍ��̐ݒ�
			m_pObjectCursor->SetIdxModel(pIdx[m_type]);
			m_pObjectCursor->BindModel(pIdx[m_type]);
		}

		if(pKeyboard->GetTrigger(DIK_9))
		{// �w��̃u���b�N���폜
			CBlock::Delete(m_nIdxObject);
		}

		if (pKeyboard->GetTrigger(DIK_8))
		{// �u���b�N�̕ۑ�
			CBlock::Save();
		}

		if (m_pObjectCursor != nullptr)
		{// �J�[�\���̃g�����X�t�H�[��
			m_pObjectCursor->SetPosition(m_pObjectCursor->GetPosition() + pos);
			m_pObjectCursor->SetRot(m_pObjectCursor->GetRot() + rot);
		}

		CDebugProc::GetInstance()->Print("\n//=======================\n");
		CDebugProc::GetInstance()->Print("// �G�f�B�^�[\n");
		CDebugProc::GetInstance()->Print("//=======================\n");
		CDebugProc::GetInstance()->Print("�G�f�B�^�[�̈ʒu�F[%f,%f,%f]\n", m_pObjectCursor->GetPosition().x, m_pObjectCursor->GetPosition().y, m_pObjectCursor->GetPosition().z);
		CDebugProc::GetInstance()->Print("�G�f�B�^�[�̌����F[%f,%f,%f]\n", m_pObjectCursor->GetRot().x, m_pObjectCursor->GetRot().y, m_pObjectCursor->GetRot().z);
		CDebugProc::GetInstance()->Print("�ړ�[IJKL]\n");
		CDebugProc::GetInstance()->Print("�㉺�ړ�[UO]\n");
		CDebugProc::GetInstance()->Print("�ݒu[ENTER]\n");
		CDebugProc::GetInstance()->Print("�ۑ�[8]\n");
		CDebugProc::GetInstance()->Print("�I�𒆂̃u���b�N�F[%d]:[0]\n", m_nIdxObject);
		CDebugProc::GetInstance()->Print("�I���u���b�N�폜[9]\n");
		CDebugProc::GetInstance()->Print("�ݒu����^�C�v�F[%d]:[7]\n", m_type);
		CDebugProc::GetInstance()->Print("//=======================\n");
	}
}