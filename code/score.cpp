//*****************************************************
//
// �X�R�A�̏���[score.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "score.h"
#include "timer.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "number.h"
#include "UI.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define NUM_PLACE	(6)	// ����
#define SCORE_SPEED	(71)	// �X�R�A�̕ς��X�s�[�h
#define RANK_BONUS	(0.05f)	// 1�����N�ɂ�����{�[�i�X�{��
#define RANK_RATE	(0.0004f)	// �����N�̏オ��{��
#define MAX_TIME	(180)	// �^�C���{�[�i�X���t�^�����Œ᎞��
#define TIME_BONUS	(500)	// ��b������̃{�[�i�X

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CScore *CScore::m_pScore = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CScore::CScore()
{
	m_pObjNumber = nullptr;
	m_nScore = 0;
	m_nSocreDest = 0;
	m_nIdxTexture = -1;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CScore::~CScore()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CScore::Init(void)
{
	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CScore::Uninit(void)
{
	if (m_pObjNumber != nullptr)
	{
		m_pObjNumber = nullptr;
	}

	m_pScore = nullptr;

	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CScore::Update(void)
{
	//�X�R�A�l�㏸���o==============================
	if (m_nScore >= m_nSocreDest)
	{
		m_nScore = m_nSocreDest;
	}
	else
	{
		m_nScore += 50;
	}

	if (m_pObjNumber != nullptr)
	{
		m_pObjNumber->SetValue(m_nScore, NUM_PLACE);
	}
}

//=====================================================
// �X�R�A���Z
//=====================================================
int CScore::AddScore(int nValue)
{
	m_nSocreDest += nValue;

	return nValue;
}

//=====================================================
// ��������
//=====================================================
CScore *CScore::Create(void)
{
	if (m_pScore == nullptr)
	{
		m_pScore = new CScore;

		if (m_pScore->m_pObjNumber == nullptr)
		{
			m_pScore->m_pObjNumber = CNumber::Create(NUM_PLACE, m_pScore->m_nScore);
			m_pScore->m_pObjNumber->SetPosition(D3DXVECTOR3(1100.0f, 80.0f, 0.0f));
			m_pScore->m_pObjNumber->SetSizeAll(15.0f,32.5f);

			CUI *pObject2D = CUI::Create();

			if (pObject2D != nullptr)
			{
				pObject2D->SetPosition(D3DXVECTOR3(1030.0f, 80.0f, 0.0f));
				pObject2D->SetSize(70.0f, 35.0f);

				// �e�N�X�`���ԍ��擾
				int nIdx = CTexture::GetInstance()->Regist("data\\TEXTURE\\UI\\scoreBack.png");

				pObject2D->SetIdxTexture(nIdx);
				pObject2D->SetVtx();
			}
		}
	}

	return m_pScore;
}

//=====================================================
// ���U���g�X�R�A�ݒ�
//=====================================================
void CScore::SetResultScore(void)
{
	CTimer *pTimer = CTimer::GetInstance();
	int nTime = 0;
	int nScore = GetScore();

	if (pTimer != nullptr)
	{// ���Ԃ̎擾
		nTime = pTimer->GetSecond();
	}

	int nBonus = 0;

	// �{�[�i�X�̌v�Z
	nBonus = (MAX_TIME - nTime) * TIME_BONUS;

	// �{�[�i�X�����Z
	nScore += nBonus;

	CManager::SetScore(nScore);
}