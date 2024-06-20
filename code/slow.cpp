//*****************************************************
//
// �X���[�̏���[slow.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "slow.h"
#include "debugproc.h"
#include "manager.h"
#include "universal.h"

//*****************************************************
// �萔��`
//*****************************************************
namespace
{
const float DEFAULT_TIMESCALE = 1.0f;	// �^�C���X�P�[���̃f�t�H���g�l
}

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CSlow *CSlow::s_pSlow = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CSlow::CSlow() : m_fTimeScale(0.0f), m_fTimeSlow(0.0f)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CSlow::~CSlow()
{

}

//=====================================================
// ��������
//=====================================================
CSlow *CSlow::Create(void)
{
	if (s_pSlow == nullptr)
	{
		s_pSlow = new CSlow;

		if (s_pSlow != nullptr)
		{
			s_pSlow->Init();
		}
	}

	return s_pSlow;
}

//=====================================================
// ����������
//=====================================================
HRESULT CSlow::Init(void)
{
	m_fTimeScale = DEFAULT_TIMESCALE;

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CSlow::Uninit(void)
{
	s_pSlow = nullptr;

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CSlow::Update(void)
{
	if (m_fTimeSlow > 0.0f)
	{
		float fDeltaTime = Manager::GetDeltaTime();

		m_fTimeSlow -= fDeltaTime;

		if (m_fTimeSlow <= 0.0f)
		{
			SetScale(DEFAULT_TIMESCALE);
		}
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CSlow::Draw(void)
{
#ifdef _DEBUG	// �f�o�b�O�\��
	CDebugProc *pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc != nullptr)
	{
		pDebugProc->Print("\n�^�C���X�P�[��[%f]",m_fTimeScale);
	}
#endif
}

//=====================================================
// �X�P�[���̐ݒ�
//=====================================================
void CSlow::SetScale(float fScale)
{
	if (fScale >= 0.0f)
	{
		m_fTimeScale = fScale;
	}
}

//=====================================================
// �X���[�^�C���̐ݒ�
//=====================================================
void CSlow::SetSlowTime(float fTime, float fScale)
{
	m_fTimeSlow = fTime;

	universal::LimitValue(&m_fTimeSlow, FLT_MAX, 0.0f);
	
	SetScale(fScale);
}

namespace Slow
{
//=====================================================
// �^�C���X�P�[���擾�i�V���[�g�J�b�g�֐��j
//=====================================================
float GetTimeScale(void)
{
	float fScale = DEFAULT_TIMESCALE;

	CSlow *pSlow = CSlow::GetInstance();

	if (pSlow != nullptr)
	{
		fScale = pSlow->GetScale();
	}

	return fScale;
}
}