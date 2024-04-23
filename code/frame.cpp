//*****************************************************
//
// Frame�̏���[Frame.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "frame.h"
#include "object2D.h"
#include "UIManager.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define FRAME_HEIGHT	(50.0f)	// �t���[���̍���

//=====================================================
// �D�揇�ʂ����߂�R���X�g���N�^
//=====================================================
CFrame::CFrame(int nPriority) : CObject(nPriority)
{
	ZeroMemory(&m_info, sizeof(SInfo));
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CFrame::~CFrame()
{

}

//=====================================================
// ��������
//=====================================================
CFrame *CFrame::Create(int nTimeIn, int nTimeWait, int nTimeOut)
{
	CFrame *pFrame = nullptr;

	if (pFrame == nullptr)
	{
		// �C���X�^���X����
		pFrame = new CFrame;

		if (pFrame != nullptr)
		{
			// �����󂯎��
			pFrame->m_info.nTimeIn = nTimeIn;
			pFrame->m_info.nTimeWait = nTimeWait;
			pFrame->m_info.nTimeOut = nTimeOut;

			// ����������
			pFrame->Init();
		}
	}

	return pFrame;
}

//=====================================================
// ������
//=====================================================
HRESULT CFrame::Init(void)
{
	// UI���\���ɂ���
	CUIManager *pUIManager = CUIManager::GetInstance();

	m_info.state = STATE_IN;

	if (pUIManager != nullptr)
	{
		pUIManager->EnableDisp(false);
	}

	// �|���S���̐���
	if (m_info.pUpper == nullptr)
	{
		m_info.pUpper = CObject2D::Create(7);

		if (m_info.pUpper != nullptr)
		{
			m_info.pUpper->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 0.0f, 0.0f));
			m_info.pUpper->SetSize(SCREEN_WIDTH * 0.5f, 0.0f);
			m_info.pUpper->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
			m_info.pUpper->SetVtx();
		}
	}

	if (m_info.pUnder == nullptr)
	{
		m_info.pUnder = CObject2D::Create(7);

		if (m_info.pUnder != nullptr)
		{
			m_info.pUnder->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT, 0.0f));
			m_info.pUnder->SetSize(SCREEN_WIDTH * 0.5f, 0.0f);
			m_info.pUnder->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
			m_info.pUnder->SetVtx();
		}
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CFrame::Uninit(void)
{
	// UI��\������
	CUIManager *pUIManager = CUIManager::GetInstance();

	if (pUIManager != nullptr)
	{
		pUIManager->EnableDisp(true);
	}

	// �|���S���̔j��
	if (m_info.pUnder != nullptr)
	{
		m_info.pUnder->Uninit();
		m_info.pUnder = nullptr;
	}

	if (m_info.pUpper != nullptr)
	{
		m_info.pUpper->Uninit();
		m_info.pUpper = nullptr;
	}

	// ���g�̔j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CFrame::Update(void)
{
	// ��Ԃ̊Ǘ�
	ManageState();

	if (m_info.state != STATE_WAIT)
	{
		// �㑤�̊Ǘ�
		ManageUpper();

		// �����̊Ǘ�
		ManageUnder();
	}
}

//=====================================================
// ��Ԃ̊Ǘ�
//=====================================================
void CFrame::ManageState(void)
{
	switch (m_info.state)
	{
	case STATE_IN:

		m_info.nCntFade++;

		if (m_info.nTimeIn <= m_info.nCntFade)
		{
			m_info.state = STATE_WAIT;

			m_info.nCntFade = 0;
		}

		break;
	case STATE_WAIT:

		m_info.nCntFade++;

		if (m_info.nTimeWait <= m_info.nCntFade)
		{
			m_info.state = STATE_OUT;

			m_info.nCntFade = m_info.nTimeOut;
		}

		break; 
	case STATE_OUT:

		m_info.nCntFade--;

		if (0 >= m_info.nCntFade)
		{// �I������
			Uninit();
		}

		break;
	default:
		break;
	}
}

//=====================================================
// �㑤�̊Ǘ�
//=====================================================
void CFrame::ManageUpper(void)
{
	if (m_info.pUpper == nullptr)
	{
		return;
	}

	int nTime = 0;

	switch (m_info.state)
	{
	case STATE_IN:

		nTime = m_info.nTimeIn;

		break;
	case STATE_OUT:

		nTime = m_info.nTimeOut;

		break;
	default:
		break;
	}

	float fRate = (float)m_info.nCntFade / (float)nTime;

	float fHeight = fRate * FRAME_HEIGHT;

	// �ʒu�ݒ�
	D3DXVECTOR3 pos = { SCREEN_WIDTH * 0.5f,fHeight,0.0f };

	// �T�C�Y�ݒ�
	m_info.pUpper->SetPosition(pos);
	m_info.pUpper->SetSize(SCREEN_WIDTH * 0.5f, fHeight);
	m_info.pUpper->SetVtx();
}

//=====================================================
// �����̊Ǘ�
//=====================================================
void CFrame::ManageUnder(void)
{
	if (m_info.pUnder == nullptr)
	{
		return;
	}

	int nTime = 0;

	switch (m_info.state)
	{
	case STATE_IN:

		nTime = m_info.nTimeIn;

		break;
	case STATE_OUT:

		nTime = m_info.nTimeOut;

		break;
	default:
		break;
	}

	float fRate = (float)m_info.nCntFade / (float)nTime;

	float fHeight = fRate * FRAME_HEIGHT;

	// �ʒu�ݒ�
	D3DXVECTOR3 pos = { SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT - fHeight,0.0f };

	// �T�C�Y�ݒ�
	m_info.pUnder->SetPosition(pos);
	m_info.pUnder->SetSize(SCREEN_WIDTH * 0.5f, fHeight);
	m_info.pUnder->SetVtx();
}

//=====================================================
// �`��
//=====================================================
void CFrame::Draw(void)
{

}