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
#include "blur.h"

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CObject *CObject::s_apTop[NUM_PRIORITY] = {};	// �擪�̃I�u�W�F�N�g�̃|�C���^
CObject *CObject::s_apCur[NUM_PRIORITY] = {};	// �Ō���̃I�u�W�F�N�g�̃|�C���^
int CObject::s_nNumAll = 0;	// ����

//=====================================================
// �D�揇�ʂ����߂�R���X�g���N�^
//=====================================================
CObject::CObject(int nPriority) : m_pPrev(nullptr),m_pNext(nullptr),m_bDeath(false),m_bWire(false),m_bZtest(false),
									m_bLighting(true),m_bAdd(false),m_bFog(true),m_bCull(true),m_type(E_TYPE::TYPE_NONE),m_nID(-1), m_dwAlpha(0)
{
	s_nNumAll++;

	// �v���C�I���e�B�ݒ�
	m_nPriority = nPriority;

	if (s_apTop[nPriority] == nullptr)
	{// �擪�ƍŌ���A�h���X�̑��
		s_apTop[nPriority] = this;
		s_apCur[nPriority] = this;

		return;
	}

	// �O�̃A�h���X�ɍŌ���̃A�h���X��������
	m_pPrev = s_apCur[nPriority];

	// �Ō���̃A�h���X�������ɂ���
	s_apCur[nPriority] = this;

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
	s_nNumAll--;
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
	if (s_apCur[m_nPriority] != this && s_apTop[m_nPriority] != this)
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

	if (s_apTop[m_nPriority] == this)
	{// �擪�A�h���X�̔j��
		if (m_pNext != nullptr)
		{
			m_pNext->m_pPrev = nullptr;
		}

		// �擪�A�h���X�����̃A�h���X�Ɉ����p��
		s_apTop[m_nPriority] = m_pNext;
	}
	
	if (s_apCur[m_nPriority] == this)
	{// �Ō���A�h���X�̔j��
		if (m_pPrev != nullptr)
		{
			m_pPrev->m_pNext = nullptr;
		}

		// �Ō���A�h���X��O�̃A�h���X�Ɉ����p��
		s_apCur[m_nPriority] = m_pPrev;
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
		CObject *pObject = s_apTop[nCntPri];

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
		CObject *pObject = s_apTop[nCntPri];

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
		CObject *pObject = s_apTop[nCntPri];

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
		CObject *pObject = s_apTop[nCntPri];

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
// �I�u�W�F�N�g�̍폜
//=====================================================
void CObject::DeleteAll(void)
{
	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		// �擪�I�u�W�F�N�g����
		CObject *pObject = s_apTop[nCntPri];

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
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// �u���[�̎擾
	CBlur * pBlur = CBlur::GetInstance();

	if (pBlur != nullptr)
	{
		pBlur->SaveRenderInfo();	// �`��̏���ۑ�
		pBlur->ChangeTarget();	// �����_�[�^�[�Q�b�g�̕ύX

		// �N���A����
		pDevice->Clear(0, nullptr,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
			D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
	}

	// �J�����̎擾
	CCamera *pCamera = Manager::GetCamera();

	if (pCamera != nullptr)
	{// �J�����̐ݒ�
		pCamera->SetCamera();
	}

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		// �擪�I�u�W�F�N�g����
		CObject *pObject = s_apTop[nCntPri];

		while (pObject != nullptr)
		{
			// ���̃A�h���X��ۑ�
			CObject *pObjectNext = pObject->m_pNext;

			if (pObject->m_bWire)
			{// ���C���[�t���[���̐ݒ�
				pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			}

			if (pObject->m_bZtest)
			{// Z�e�X�g�̐ݒ�
				pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			}

			if (pObject->m_bLighting == false)
			{
				// ���C�e�B���O�𖳌���
				pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			}

			if (pObject->m_bAdd)
			{
				// ���Z�������ǂ���
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			}

			if (pObject->m_bCull == false)
			{
				pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			}

			//�A���t�@�e�X�g�̗L����
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, pObject->m_dwAlpha);

			pDevice->SetRenderState(D3DRS_FOGENABLE, pObject->m_bFog && CRenderer::GetInstance()->IsFog());

			// �`�揈��
			pObject->Draw();

			if (pObject->m_bWire)
			{
				pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			}

			if (pObject->m_bZtest)
			{// Z�e�X�g�̐ݒ�
				pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
			}

			if (pObject->m_bLighting == false)
			{
				// ���C�e�B���O��L����
				pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			}

			if (pObject->m_bAdd)
			{
				// ���Z������߂�
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			}

			if (pObject->m_bCull == false)
			{
				pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			}

			// �A���t�@�e�X�g�̖�����
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

			// ���̃A�h���X����
			pObject = pObjectNext;
		}
	}

	if (pBlur != nullptr)
	{
		pBlur->OverlapLastTexture();	// �O��̃e�N�X�`�����d�˂�
		pBlur->RestoreTarget();	// �����_�[�^�[�Q�b�g�̕���
		pBlur->DrawBuckBuffer();	// �o�b�N�o�b�t�@�ւ̕`��
		pBlur->SwapBuffer();	// �o�b�t�@�[�̓���ւ�
	}

	DeleteAll();
}

//=====================================================
//�^�C�v�ݒ菈��
//=====================================================
void CObject::SetType(E_TYPE type)
{
	m_type = type;
}

namespace Object
{
void DeleteObject(CObject **ppObject,int nSize)
{// �I�u�W�F�N�g�̍폜
	for (int i = 0; i < nSize; i++)
	{
		if (ppObject[i] != nullptr)
		{
			ppObject[i]->Uninit();
			ppObject[i] = nullptr;
		}
	}
}
}