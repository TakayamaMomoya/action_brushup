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
#include "object2D.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "debugproc.h"
#include "effect2D.h"
#include "effect3D.h"
#include "sound.h"
#include "score.h"
#include "timer.h"
#include "object.h"
#include "camera.h"
#include "light.h"
#include "object3D.h"
#include "objectX.h"
#include "billboard.h"
#include "model.h"
#include "texture.h"
#include "universal.h"
#include "particle.h"
#include "fade.h"
#include "block.h"
#include "inputManager.h"

//*****************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************
CCamera *CManager::m_pCamera = nullptr;	// �J�����̃|�C���^
CLight *CManager::m_pLight = nullptr;	// ���C�g�̃|�C���^
CScene *CManager::m_pScene = nullptr;	// �V�[���ւ̃|�C���^
CScene::MODE CManager::m_mode = CScene::MODE_RANKING;	// ���݂̃��[�h
int CManager::m_nScore = 0;	// �X�R�A�ۑ��p
float CManager::m_fDeltaTime = 0.0f;	// �O�̃t���[�����炩����������

//=====================================================
// �R���X�g���N�^
//=====================================================
CManager::CManager()
{
	m_pScene = nullptr;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CManager::~CManager()
{

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