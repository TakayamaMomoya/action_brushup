//*****************************************************
//
// �}�l�[�W���[����[manager.cpp]
// Author:���R����
//
//*****************************************************

//*****************************************************
// �C���N���[�h
//*****************************************************
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "sound.h"
#include "object.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "texture.h"
#include "particle.h"
#include "fade.h"
#include "block.h"
#include "inputManager.h"

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CManager *CManager::s_pManager = nullptr;	// ���g�̃|�C���^

//=====================================================
// �R���X�g���N�^
//=====================================================
CManager::CManager()
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CManager::~CManager()
{

}

//=====================================================
// ��������
//=====================================================
CManager *CManager::Create(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	if (s_pManager == nullptr)
	{
		s_pManager = new CManager;

		if (s_pManager != nullptr)
		{
			s_pManager->Init(hInstance, hWnd, bWindow);
		}
	}

	return s_pManager;
}

//=====================================================
// ����������
//=====================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �����_���[�̐���
	CRenderer::Create(hWnd, bWindow);

	// ���̓}�l�[�W���[����
	CInputManager::Create(hInstance, hWnd);

	// �f�o�b�O�\���̐���
	CDebugProc::Create();

	// �T�E���h����
	CSound::Create(hWnd);

	if (m_pCamera == nullptr)
	{// �J��������
		m_pCamera = new CCamera;

		if (m_pCamera != nullptr)
		{
			// ������
			if (FAILED(m_pCamera->Init()))
			{// �������Ɏ��s�����ꍇ
				return E_FAIL;
			}
		}
	}

	if (m_pLight == nullptr)
	{// ���C�g����
		m_pLight = new CLight;

		if (m_pLight != nullptr)
		{
			// ������
			if (FAILED(m_pLight->Init()))
			{// �������Ɏ��s�����ꍇ
				return E_FAIL;
			}
		}
	}

	// �e�N�X�`���Ǘ��̐���
	CTexture::Create();

	// �t�F�[�h�̐���
	CFade::Create();

	// �p�[�e�B�N���̓Ǎ�
	CParticle::Load();

	// �u���b�N�ԍ��Ǎ�
	CBlock::LoadModel();

	SetMode(m_mode);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CManager::Uninit(void)
{
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
	}

	// �t�F�[�h�I��
	CFade *pFade = CFade::GetInstance();

	if (pFade != nullptr)
	{
		pFade->Uninit();
	}

	// �p�[�e�B�N�����j��
	CParticle::Unload();

	// �u���b�N���폜
	CBlock::DeleteAll();

	// �u���b�N�ԍ��폜
	CBlock::DeleteIdx();

	// �����_���[�I��
	CRenderer *pRenderer = CRenderer::GetInstance();

	if (pRenderer != nullptr)
	{
		pRenderer->Uninit();
	}

	// ���̓}�l�[�W���[�I��
	CInputManager *pInputManager = CInputManager::GetInstance();

	if (pInputManager != nullptr)
	{
		pInputManager->Uninit();
	}

	CSound *pSound = CSound::GetInstance();

	if (pSound != nullptr)
	{// �T�E���h�̏I���E�j��
		pSound->Uninit();
		pSound = nullptr;
	}

	// �f�o�b�O�v���V�[�W���̏I��
	CDebugProc *pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc != nullptr)
	{
		pDebugProc->Uninit();
	}

	if (m_pLight != nullptr)
	{// ���C�g�̏I���E�j��
		m_pLight->Uninit();

		delete m_pLight;
		m_pLight = nullptr;
	}

	if (m_pCamera != nullptr)
	{// �J�����̏I���E�j��
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = nullptr;
	}

	// �e�N�X�`���̏I���E�j��
	CTexture *pTexture = CTexture::GetInstance();

	if (pTexture != nullptr)
	{
		pTexture->Unload();

		delete pTexture;
		pTexture = nullptr;
	}

	// ���f���j��
	CModel::Unload();
}

//=====================================================
// �X�V����
//=====================================================
void CManager::Update(void)
{
	// �t�F�[�h�X�V
	CFade *pFade = CFade::GetInstance();

	if (pFade != nullptr)
	{
		pFade->Update();
	}

	if (m_pScene != nullptr)
	{
		m_pScene->Update();
	}

	// ���̓}�l�[�W���[�X�V
	CInputManager *pInputManager = CInputManager::GetInstance();

	if (pInputManager != nullptr)
	{
		pInputManager->Update();
	}

	CSound *pSound = CSound::GetInstance();

	if (pSound != nullptr)
	{// �T�E���h�̍X�V
		pSound->Update();
	}

	// �f�o�b�O�v���V�[�W���̍X�V
	CDebugProc *pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc != nullptr)
	{
		pDebugProc->Update();
	}

	// ���C�g�̍X�V
	if (m_pLight != nullptr)
	{
		m_pLight->Update();
	}

	// �J�����̍X�V
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CManager::Draw(void)
{
	if (m_pScene != nullptr)
	{
		m_pScene->Draw();
	}

	// �����_���[�`��
	CRenderer *pRenderer = CRenderer::GetInstance();

	if (pRenderer != nullptr)
	{
		pRenderer->Draw();
	}
}

//=====================================================
// ���[�h�ݒ�
//=====================================================
void CManager::SetMode(CScene::MODE mode)
{
	CSound *pSound = CSound::GetInstance();

	if (pSound != nullptr)
	{// ���̒�~
		pSound->Stop();
	}

	if (m_pCamera != nullptr)
	{
		m_pCamera->Init();
	}

	// �V�[����j��
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();

		delete m_pScene;
		m_pScene = nullptr;
	}

	// �V�[������
	m_pScene = CScene::Create(mode);

	// ���[�h�ݒ�
	m_mode = mode;
}

namespace Manager
{
//=====================================================
// �J�����擾(�V���[�g�J�b�g)
//=====================================================
CCamera *GetCamera(void)
{
	CManager *pManager = CManager::GetInstace();

	if (pManager != nullptr)
		return pManager->GetCamera();

	return nullptr;
}

//=====================================================
// ���C�g�擾(�V���[�g�J�b�g)
//=====================================================
CLight *GetLight(void)
{
	CManager *pManager = CManager::GetInstace();

	if (pManager != nullptr)
		return pManager->GetLight();

	return nullptr;
}

//=====================================================
// ���[�h�ݒ�(�V���[�g�J�b�g)
//=====================================================
void SetMode(CScene::MODE mode)
{
	CManager *pManager = CManager::GetInstace();

	if (pManager != nullptr)
		pManager->SetMode(mode);
}

//=====================================================
// ���[�h�擾(�V���[�g�J�b�g)
//=====================================================
CScene::MODE GetMode(void)
{
	CManager *pManager = CManager::GetInstace();

	if (pManager != nullptr)
		return pManager->GetMode();

	return CScene::MODE::MODE_TITLE;
}

//=====================================================
// �X�R�A�ݒ�(�V���[�g�J�b�g)
//=====================================================
void SetScore(int nScore)
{
	CManager *pManager = CManager::GetInstace();

	if (pManager != nullptr)
		pManager->SetScore(nScore);
}

//=====================================================
// �X�R�A�擾(�V���[�g�J�b�g)
//=====================================================
int GetScore(void)
{
	CManager *pManager = CManager::GetInstace();

	if (pManager != nullptr)
		return pManager->GetScore();

	return 0;
}

//=====================================================
// �f���^�^�C���擾(�V���[�g�J�b�g)
//=====================================================
float GetDeltaTime(void)
{
	CManager *pManager = CManager::GetInstace();

	if (pManager != nullptr)
		return pManager->GetDeltaTime();

	return 0.0f;
}
}