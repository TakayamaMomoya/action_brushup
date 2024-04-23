//*****************************************************
//
// �I�u�W�F�N�g�̏���[object.h]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "object.h"
#include "camera.h"
#include "manager.h"
#include "collision.h"
#include "renderer.h"

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CObject *CObject::m_apTop[NUM_PRIORITY] = {};	// �擪�̃I�u�W�F�N�g�̃|�C���^
CObject *CObject::m_apCur[NUM_PRIORITY] = {};	// �Ō���̃I�u�W�F�N�g�̃|�C���^
int CObject::m_nNumAll = 0;	// ����

//=====================================================
// �D�揇�ʂ����߂�R���X�g���N�^
//=====================================================
CObject::CObject(int nPriority)
{
	m_nNumAll++;

	// �l�̃N���A
	m_pPrev = nullptr;
	m_pNext = nullptr;
	m_bDeath = false;
	m_bWire = false;

	if (nPriority == 7)
	{
		int n = 10;
	}

	m_nPriority = nPriority;

	if (m_apTop[nPriority] == nullptr)
	{// �擪�ƍŌ���A�h���X�̑��
		m_apTop[nPriority] = this;
		m_apCur[nPriority] = this;

		return;
	}

	// �O�̃A�h���X�ɍŌ���̃A�h���X��������
	m_pPrev = m_apCur[nPriority];

	// �Ō���̃A�h���X�������ɂ���
	m_apCur[nPriority] = this;

	if (m_pPrev != nullptr)
	{
		// �O�̃I�u�W�F�N�g�̎��̃A�h���X�������ɂ���
		m_pPrev->m_pNext = this;
	}
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CObject::~CObject()
{
	m_nNumAll--;
}

//=====================================================
// �ʃ����[�X����
//=====================================================
void CObject::Release(void)
{
	// ���S�t���O�𗧂Ă�
	m_bDeath = true;
}

//=====================================================
// �j������
//=====================================================
void CObject::Delete(void)
{
	if (m_apCur[m_nPriority] != this && m_apTop[m_nPriority] != this)
	{// �^�񒆂̃A�h���X�̔j��
		if (m_pPrev != nullptr)
		{
			// �O�̃A�h���X���玟�̃A�h���X���Ȃ�
			m_pPrev->m_pNext = m_pNext;
		}

		if (m_pNext != nullptr)
		{
			// ���̃A�h���X����O�̃A�h���X���Ȃ�
			m_pNext->m_pPrev = m_pPrev;
		}
	}

	if (m_apTop[m_nPriority] == this)
	{// �擪�A�h���X�̔j��
		if (m_pNext != nullptr)
		{
			m_pNext->m_pPrev = nullptr;
		}

		// �擪�A�h���X�����̃A�h���X�Ɉ����p��
		m_apTop[m_nPriority] = m_pNext;
	}
	
	if (m_apCur[m_nPriority] == this)
	{// �Ō���A�h���X�̔j��
		if (m_pPrev != nullptr)
		{
			m_pPrev->m_pNext = nullptr;
		}

		// �Ō���A�h���X��O�̃A�h���X�Ɉ����p��
		m_apCur[m_nPriority] = m_pPrev;
	}

	// ���g�̔j��
	delete this;
}

// �ÓI�����o�֐�======================================

//=====================================================
// �S�����[�X����
//=====================================================
void CObject::ReleaseAll(void)
{
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		// �擪�I�u�W�F�N�g����
		CObject *pObject = m_apTop[nCntPri];

		while (pObject != nullptr)
		{
			// ���̃A�h���X��ۑ�
			CObject *pObjectNext = pObject->m_pNext;

			// �I������
			pObject->Uninit();

			// ���̃A�h���X����
			pObject = pObjectNext;
		}
	}

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		// �擪�I�u�W�F�N�g����
		CObject *pObject = m_apTop[nCntPri];

		while (pObject != nullptr)
		{
			// ���̃A�h���X��ۑ�
			CObject *pObjectNext = pObject->m_pNext;

			if (pObject->m_bDeath)
			{
				// �폜
				pObject->Delete();
			}

			// ���̃A�h���X����
			pObject = pObjectNext;
		}
	}
}

//=====================================================
// �S�X�V����
//=====================================================
void CObject::UpdateAll(void)
{
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		// �擪�I�u�W�F�N�g����
		CObject *pObject = m_apTop[nCntPri];

		while (pObject != nullptr)
		{

			// ���̃A�h���X��ۑ�
			CObject *pObjectNext = pObject->m_pNext;

			// �X�V����
			pObject->Update();

			// ���̃A�h���X����
			pObject = pObjectNext;
		}
	}

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		// �擪�I�u�W�F�N�g����
		CObject *pObject = m_apTop[nCntPri];

		while (pObject != nullptr)
		{
			// ���̃A�h���X��ۑ�
			CObject *pObjectNext = pObject->m_pNext;

			if (pObject->m_bDeath)
			{
				// �I������
				pObject->Delete();
			}

			// ���̃A�h���X����
			pObject = pObjectNext;
		}
	}
}

//=====================================================
// �S�`�揈��
//=====================================================
void CObject::DrawAll(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// �J�����̎擾
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera != nullptr)
	{// �J�����̐ݒ�
		pCamera->SetCamera();
	}

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		// �擪�I�u�W�F�N�g����
		CObject *pObject = m_apTop[nCntPri];

		while (pObject != nullptr)
		{
			// ���̃A�h���X��ۑ�
			CObject *pObjectNext = pObject->m_pNext;

			if (pObject->m_bWire)
			{
				pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			}

			// �`�揈��
			pObject->Draw();

			if (pObject->m_bWire)
			{
				pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			}

			// ���̃A�h���X����
			pObject = pObjectNext;
		}
	}
}

//=====================================================
//�^�C�v�ݒ菈��
//=====================================================
void CObject::SetType(TYPE type)
{
	m_type = type;
}