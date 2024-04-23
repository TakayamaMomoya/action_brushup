//*****************************************************
//
// �����L���O�̏���[Ranking.cpp]
//Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "main.h"
#include "ranking.h"
#include "fade.h"
#include <stdio.h>
#include "object.h"
#include "manager.h"
#include "texture.h"
#include "inputManager.h"
#include "skybox.h"
#include "universal.h"
#include "sound.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define NUM_PLACE					(6)										// �X�R�A�̌���
#define TIMER_TRANS					(360)									// �J�ڎ���
#define RANKING_WIDTH			(80)	// ����
#define RANKING_HEIGHT			(80)	// ����
#define FLASH_SPEED					(10)	// �_�ŃX�s�[�h
#define RANKING_BIN_FILE			"data\\BIN\\ranking"								// �����L���O�t�@�C����
#define RANKING_TEX_FILE			"data\\TEXTURE\\UI\\Number000.png"		// �����L���O�e�N�X�`����
#define BG_TEX_FILE					"data\\TEXTURE\\BG\\ResultBg000.png"	// �����L���O�w�i�e�N�X�`����
#define RANKING_PATH	"data\\TEXTURE\\UI\\ranking.png"	// ���ڃe�N�X�`����
#define ROTATION_SPEED	(0.001f)	// ��]���x

//=====================================================
// �R���X�g���N�^
//=====================================================
CRanking::CRanking()
{
	ZeroMemory(&m_apNumber[0],sizeof(m_apNumber));
	m_nCntState = 0;
	m_nRankUpdate = -1;
	m_nScore = 0;
	m_nTimerTrans = 0;
	ZeroMemory(&m_aScore[0],sizeof(int) * NUM_RANK);
	m_state = STATE_NORMAL;
	m_pSkybox = nullptr;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CRanking::~CRanking()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CRanking::Init(void)
{
	// ���ڂ̐���
	CObject2D *pObject2D = CObject2D::Create();
	pObject2D->SetSize(300.0f,90.0f);
	pObject2D->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 100.0f, 0.0f));

	int nIdx = CTexture::GetInstance()->Regist(RANKING_PATH);
	pObject2D->SetIdxTexture(nIdx);
	pObject2D->SetVtx();

	// �����̐���
	for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
	{
		m_apNumber[nCnt] = CNumber::Create(NUM_PLACE, 0);
	}

	// �����ݒ�
	Reset();
	Sort();

	// �X�R�A�̎擾
	int nScore = CManager::GetScore();

	// �擾�����X�R�A�Ń����L���O�ݒ�
	Set(nScore);

	// �ۑ�
	Save();

	// �X�J�C�{�b�N�X
	m_pSkybox = CSkybox::Create();

	CSound *pSound = CSound::GetInstance();

	if (pSound != nullptr)
	{
		pSound->Play(CSound::LABEL_BGM000);
	}

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CRanking::Uninit(void)
{
	if (m_pSkybox != nullptr)
	{
		m_pSkybox->Uninit();
		m_pSkybox = nullptr;
	}

	CObject::ReleaseAll();
}

//=====================================================
// �X�V����
//=====================================================
void CRanking::Update(void)
{
	CInputManager *pInputManager = CInputManager::GetInstance();
	CFade *pFade = CFade::GetInstance();

	// �V�[���̍X�V
	CScene::Update();

	// �J�E���g�A�b�v
	m_nCntState++;

	if (m_nRankUpdate != -1)
	{// �����L���O���X�V���ꂽ
		// �Y���̃����N��_��==================================
		
		if (m_nCntState >= FLASH_SPEED)
		{// �J�E���^�����̒l�ɒB������
			switch (m_state)
			{
			case STATE_NORMAL:
				m_state = STATE_DIFF;
				break;
			case STATE_DIFF:
				m_state = STATE_NORMAL;
				break;
			}

			m_nCntState = 0;
		}

		// �ϐ��錾
		D3DXCOLOR colRanking = {0.0f,0.0f,0.0f,0.0f};

		switch (m_state)
		{// ��Ԃɂ�镪��
		case STATE_NORMAL:
			colRanking = { 1.0f,1.0f,1.0f,1.0f};
			break;
		case STATE_DIFF:
			colRanking = { 0.5f,1.0f,0.5f,1.0f };
			break;
		}

		if (m_apNumber[m_nRankUpdate] != nullptr)
		{
			m_apNumber[m_nRankUpdate]->SetColor(colRanking);
		}
	}

	// ��ʑJ��==========================================
	if (pInputManager->GetTrigger(CInputManager::BUTTON_ENTER))
	{//ENTER�L�[�������ꂽ��
		//�^�C�g���Ɉڍs
		if (pFade != nullptr)
		{
			pFade->SetFade(CScene::MODE_TITLE);
		}
	}

	// �X�J�C�{�b�N�X�̉�]
	if (m_pSkybox != nullptr)
	{
		D3DXVECTOR3 rot = m_pSkybox->GetRot();

		rot.y += ROTATION_SPEED;

		universal::LimitRot(&rot.y);

		m_pSkybox->SetRot(rot);
	}

	// �J�ڃ^�C�}�[�i�s
	m_nTimerTrans++;
}

//=====================================================
// �`�揈��
//=====================================================
void CRanking::Draw(void)
{

}

//=====================================================
// �ݒ菈��
//=====================================================
void CRanking::Set(int nScore)
{
	// �ϐ��錾
	D3DXVECTOR3 pos;
	char *apPath[NUM_RANK] = 
	{
		"data\\TEXTURE\\UI\\1st.png",
		"data\\TEXTURE\\UI\\2nd.png",
		"data\\TEXTURE\\UI\\3rd.png",
		"data\\TEXTURE\\UI\\4th.png",
		"data\\TEXTURE\\UI\\5th.png",
	};

	// �\�[�g
	Sort();

	if (nScore > m_aScore[NUM_RANK - 1])
	{// �ŏ��l���z��������
		m_aScore[NUM_RANK - 1] = nScore;

		// �ă\�[�g
		Sort();

		for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
		{// �������l�ƍ��v����L�^��T��
			if (nScore == m_aScore[nCnt])
			{// �j���[���R�[�h�ԍ����L�^
				m_nRankUpdate = nCnt;
			}
		}
	}

	if (m_aScore != nullptr)
	{
		// �����̐ݒ�
		for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
		{
			if (m_apNumber[nCnt] != nullptr)
			{
				// �l�̐ݒ�
				m_apNumber[nCnt]->SetValue(m_aScore[nCnt], NUM_PLACE);

				// �ʒu�̐ݒ�
				pos = D3DXVECTOR3{ 450.0f,250.0f + RANKING_HEIGHT * nCnt,0.0f };

				m_apNumber[nCnt]->SetPosition(pos);

				pos = m_apNumber[nCnt]->GetPosition();

				m_apNumber[nCnt]->SetSizeAll(RANKING_WIDTH * 0.5f, RANKING_HEIGHT * 0.5f);

				// ���ʂ̐���
				CObject2D *pObject2D = CObject2D::Create();
				pObject2D->SetSize(60.0f, 40.0f);
				pos.x -= 100 + RANKING_WIDTH * 0.5f;

				pObject2D->SetPosition(pos);

				int nIdx = CTexture::GetInstance()->Regist(apPath[nCnt]);
				pObject2D->SetIdxTexture(nIdx);
				pObject2D->SetVtx();
			}
		}
	}

	// �ۑ�����
#ifndef _DEBUG
	Save();
#endif
}

//=====================================================
// �����L���O�\�[�g
//=====================================================
void CRanking::Sort(void)
{
	for (int nCntRanking = 0; nCntRanking < NUM_RANK - 1; nCntRanking++)
	{//�����L���O���\�[�g
	 //���[�̒l���ő�l�Ƃ���
		int nTop = nCntRanking;

		for (int nCount2 = nCntRanking + 1; nCount2 < NUM_RANK; nCount2++)
		{//���̒l�ƑΏۂ̒l���r
			if (m_aScore[nTop] < m_aScore[nCount2])
			{//������r����������������������
				nTop = nCount2;
			}
		}

		//�v�f�̓���ւ�
		int nTemp = m_aScore[nCntRanking];
		m_aScore[nCntRanking] = m_aScore[nTop];
		m_aScore[nTop] = nTemp;
	}
}

//=====================================================
// �����L���O��񃊃Z�b�g
//=====================================================
void CRanking::Reset(void)
{
	//�O���t�@�C���ǂݍ���
	Load();

#if 1
	//�����L���O�����ݒ�
	m_aScore[0] = 32;
	m_aScore[1] = 31;
	m_aScore[2] = 30;
	m_aScore[3] = 29;
	m_aScore[4] = 28;
#endif
}

//=====================================================
// �����L���O���ۑ�
//=====================================================
void CRanking::Save(void)
{
	//�|�C���^�錾
	FILE *pFile;

	//�t�@�C�����J��
	pFile = fopen(RANKING_BIN_FILE, "wb");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

	    //�o�C�i���t�@�C���ɏ�������
		fwrite(&m_aScore[0], sizeof(int), NUM_RANK, pFile);

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ

	}
}

//=====================================================
//�����L���O���ǂݍ���
//=====================================================
void CRanking::Load(void)
{
	//�|�C���^�錾
	FILE *pFile;

	//�t�@�C�����J��
	pFile = fopen(RANKING_BIN_FILE, "rb");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

	    //�o�C�i���t�@�C������ǂݍ���
		fread(&m_aScore[0], sizeof(int), NUM_RANK, pFile);

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
	}
}