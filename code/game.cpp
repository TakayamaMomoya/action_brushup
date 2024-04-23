//*****************************************************
//
// �Q�[������[game.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "object.h"
#include "universal.h"
#include "particle.h"
#include "inputkeyboard.h"
#include "inputjoypad.h"
#include "fade.h"
#include "camera.h"
#include "effect3D.h"
#include "sound.h"
#include "scene.h"
#include "player.h"
#include "block.h"
#include "edit.h"
#include "enemy.h"
#include "skybox.h"
#include "enemyManager.h"
#include "animEffect3D.h"
#include "debugproc.h"
#include <stdio.h>
#include "UIManager.h"
#include "anim3D.h"
#include "texture.h"
#include "timer.h"
#include "pause.h"
#include "inputManager.h"

//*****************************************************
// �}�N����`
//*****************************************************
#define TRANS_TIME	(60)	// �I���܂ł̗]�C�̃t���[����
#define RESULT_TIME	(5)	// ���U���g��ʕ\���܂ł̃��O
#define BOSS_LINE	(2737.0f)	// �{�X��ɓ˓����郉�C��
#define CHECKPOINT_PATH "data\\MAP\\checkpoint.txt"	// �`�F�b�N�|�C���g�f�[�^�̃p�X

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CGame::STATE CGame::m_state = STATE_NONE;	// ���
int CGame::m_nProgress = 0;	// �i�s��
CGame *CGame::m_pGame = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CGame::CGame()
{
	m_pPosCheckPoint = nullptr;
	m_nNumCheckPoint = 0;
	m_nCntState = 0;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CGame::~CGame()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CGame::Init(void)
{
	m_pGame = this;

	m_state = STATE_NORMAL;

	// �J���������̐ݒ�
	CCamera *pCamera = CManager::GetCamera();

	if (pCamera != nullptr)
	{
		pCamera->SetDist(180.0f);
	}

	// ���X�|�[���n�_�ݒ�
	LoadCheckPoint();

	// �X�J�C�{�b�N�X
	CSkybox *pSkybox = CSkybox::Create();
	pSkybox->SetRot(D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));

	// �u���b�N�z�u�Ǎ�
	CBlock::Load("data\\MAP\\map01.bin");

	// UI�}�l�[�W���[
	CUIManager::Create();

	// �v���C���[����
	CPlayer *pPlayer = CPlayer::Create();

	if (pPlayer != nullptr && m_pPosCheckPoint != nullptr)
	{// �X�|�[���n�_�̐ݒ�
		pPlayer->SetPosition(m_pPosCheckPoint[m_nProgress]);
	}

	// �G�}�l�[�W���[����
	CEnemyManager::Create();

	// �RD�G�t�F�N�g�Ǘ�����
	CAnimEffect3D::Create();

	// �`���[�g���A���̐���
	CreateTutorial();

#ifdef _DEBUG
	//CEdit::Create();
#endif

	m_bStop = false;

	CSound *pSound = CSound::GetInstance();

	if (pSound != nullptr)
	{
		pSound->Play(CSound::LABEL_BGM_BATTLE);
	}

	return S_OK;
}

//=====================================================
// �`�F�b�N�|�C���g�̓Ǎ�
//=====================================================
void CGame::LoadCheckPoint(void)
{
	// �ϐ��錾
	char cTemp[256];
	int nCntPos = 0;

	// �t�@�C������ǂݍ���
	FILE *pFile = fopen(CHECKPOINT_PATH, "r");

	if (pFile != nullptr)
	{// �t�@�C�����J�����ꍇ
		while (true)
		{
			// �����ǂݍ���
			fscanf(pFile, "%s", &cTemp[0]);

			if (strcmp(cTemp, "NUM_CHECKPOINT") == 0)
			{// �`�F�b�N�|�C���g���Ǎ�
				fscanf(pFile, "%s", &cTemp[0]);

				fscanf(pFile, "%d", &m_nNumCheckPoint);

				if (m_pPosCheckPoint == nullptr)
				{// ������̐���
					m_pPosCheckPoint = new D3DXVECTOR3[m_nNumCheckPoint];

					for (int i = 0; i < m_nNumCheckPoint; i++)
					{// ���̃N���A
						m_pPosCheckPoint[i] = { 0.0f,0.0f,0.0f };
					}
				}
				else
				{
					break;
				}

				if (m_pPosCheckPoint == nullptr)
				{// �����ł��Ȃ������ꍇ
					break;
				}

				while (true)
				{
					// �����ǂݍ���
					fscanf(pFile, "%s", &cTemp[0]);

					if (strcmp(cTemp, "CHECKPOINTSET") == 0)
					{// �p�����[�^�[�Ǎ��J�n
						while (true)
						{
							// �����ǂݍ���
							fscanf(pFile, "%s", &cTemp[0]);

							if (strcmp(cTemp, "POS") == 0)
							{//�ʒu�ǂݍ���
								fscanf(pFile, "%s", &cTemp[0]);

								for (int i = 0; i < 3; i++)
								{
									fscanf(pFile, "%f", &m_pPosCheckPoint[nCntPos][i]);
								}
							}

							if (strcmp(cTemp, "END_CHECKPOINTSET") == 0)
							{// �p�����[�^�[�Ǎ��I��
								nCntPos++;

								break;
							}
						}
					}

					if (m_nNumCheckPoint <= nCntPos)
					{
						break;
					}
				}
			}
			if (strcmp(cTemp, "END_SCRIPT") == 0)
			{// �I������
				break;
			}
		}

		// �t�@�C�������
		fclose(pFile);
	}
}

//=====================================================
// �`���[�g���A���\�L�̐���
//=====================================================
void CGame::CreateTutorial(void)
{
	D3DXVECTOR3 aPos[5] =
	{
		{ 161.0f, 15.0f, 20.0f },
		{ 300.0f, 15.0f, 20.0f },
		{ 526.0f, 11.0f, 20.0f },
		{ 631.0f, 80.0f, 20.0f },
		{ 842.0f, 80.0f, 20.0f },
	};

	char *apPath[5] = 
	{
		"data\\TEXTURE\\UI\\tutorial00.png",
		"data\\TEXTURE\\UI\\tutorial01.png",
		"data\\TEXTURE\\UI\\tutorial02.png",
		"data\\TEXTURE\\UI\\tutorial03.png",
		"data\\TEXTURE\\UI\\tutorial04.png",
	};

	for (int i = 0; i < 5; i++)
	{
		// �C���X�^���X����
		CAnim3D *pAnim3D = CAnim3D::Create(aPos[i], 2, 40, true);

		if (pAnim3D != nullptr)
		{
			// �F�̐ݒ�
			CTexture *pTexture = CTexture::GetInstance();

			if (pTexture != nullptr)
			{// �e�N�X�`���̐ݒ�
				int nIdx = pTexture->Regist(apPath[i]);
				pAnim3D->SetIdxTexture(nIdx);
				pAnim3D->SetSize(35.0f, 25.0f);
			}
		}
	}
}

//=====================================================
// �I������
//=====================================================
void CGame::Uninit(void)
{
	if (m_pPosCheckPoint != nullptr)
	{
		delete[] m_pPosCheckPoint;
		m_pPosCheckPoint = nullptr;
	}

	// �u���b�N���폜
	CBlock::DeleteAll();

	// �I�u�W�F�N�g�S��
	CObject::ReleaseAll();

	m_pGame = nullptr;
}

//=====================================================
// �X�V����
//=====================================================
void CGame::Update(void)
{
	CFade *pFade = CFade::GetInstance();
	CInputManager *pInputManager = CInputManager::GetInstance();

	if (m_bStop == false)
	{
		// �V�[���̍X�V
		CScene::Update();

		if (pInputManager != nullptr)
		{
			if (pInputManager->GetTrigger(CInputManager::BUTTON_PAUSE))
			{
				CPause::Create();
			}
		}
	}
	else
	{
#ifdef DEBUG
		CEdit *pEdit = CEdit::GetInstatnce();

		if (pEdit != nullptr)
		{
			pEdit->Update();
		}
#endif // DEBUG

		CPause *pPause = CPause::GetInstance();

		if (pPause != nullptr)
		{
			pPause->Update();
		}
	}

	// ��ԊǗ�
	ManageState();

#ifdef _DEBUG
	Debug();
#endif
}

//=====================================================
// ��ԊǗ�
//=====================================================
void CGame::ManageState(void)
{
	CFade *pFade = CFade::GetInstance();

	switch (m_state)
	{
	case CGame::STATE_NORMAL:
	{
		// �v���C���[�擾
		CPlayer *pPlayer = nullptr;
		pPlayer = CPlayer::GetInstance();

		if (pPlayer != nullptr)
		{
			D3DXVECTOR3 pos = pPlayer->GetPosition();

			if (pos.x >= BOSS_LINE)
			{// �{�X��ֈڍs
				CEnemyManager *pEnemyManager = nullptr;

				pEnemyManager = CEnemyManager::GetInstance();

				if (pEnemyManager != nullptr)
				{
					pEnemyManager->CreateEnemy(D3DXVECTOR3(BOSS_LINE,190.0f,0.0f), CEnemy::TYPE_BOSS);
				}

				m_state = STATE_BOSS;
			}

			if (m_nProgress < m_nNumCheckPoint - 1)
			{
				if (pos.x >= m_pPosCheckPoint[m_nProgress + 1].x)
				{// �`�F�b�N�|�C���g�̐ݒ�
					m_nProgress++;
				}
			}
		}
	}
		break;
	case CGame::STATE_BOSS:
		break;
	case CGame::STATE_RESULT:
		break;
	case CGame::STATE_END:

		m_nCntState++;

		if (m_nCntState >= 300 && pFade != nullptr)
		{
			pFade->SetFade(CScene::MODE_RANKING);
		}

		break;
	default:
		break;
	}
}

//=====================================================
// �f�o�b�O����
//=====================================================
void CGame::Debug(void)
{
	// ���͎擾
	CInputKeyboard *pKeyboard = CInputKeyboard::GetInstance();

	if (pKeyboard == nullptr)
	{
		return;
	}

	if (pKeyboard->GetTrigger(DIK_F))
	{
		m_bStop = m_bStop ? false : true;
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CGame::Draw(void)
{
	CDebugProc::GetInstance()->Print("\n�i�s�󋵁F[%d]", m_nProgress);
}