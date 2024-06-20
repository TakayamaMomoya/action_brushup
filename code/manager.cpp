//*****************************************************
//
// マネージャー処理[manager.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
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
// 静的メンバ変数宣言
//*****************************************************
CManager *CManager::s_pManager = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CManager::CManager()
{

}

//=====================================================
// デストラクタ
//=====================================================
CManager::~CManager()
{

}

//=====================================================
// 生成処理
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
// 初期化処理
//=====================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// レンダラーの生成
	CRenderer::Create(hWnd, bWindow);

	// 入力マネージャー生成
	CInputManager::Create(hInstance, hWnd);

	// デバッグ表示の生成
	CDebugProc::Create();

	// サウンド生成
	CSound::Create(hWnd);

	if (m_pCamera == nullptr)
	{// カメラ生成
		m_pCamera = new CCamera;

		if (m_pCamera != nullptr)
		{
			// 初期化
			if (FAILED(m_pCamera->Init()))
			{// 初期化に失敗した場合
				return E_FAIL;
			}
		}
	}

	if (m_pLight == nullptr)
	{// ライト生成
		m_pLight = new CLight;

		if (m_pLight != nullptr)
		{
			// 初期化
			if (FAILED(m_pLight->Init()))
			{// 初期化に失敗した場合
				return E_FAIL;
			}
		}
	}

	// テクスチャ管理の生成
	CTexture::Create();

	// フェードの生成
	CFade::Create();

	// パーティクルの読込
	CParticle::Load();

	// ブロック番号読込
	CBlock::LoadModel();

	SetMode(m_mode);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CManager::Uninit(void)
{
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
	}

	// フェード終了
	CFade *pFade = CFade::GetInstance();

	if (pFade != nullptr)
	{
		pFade->Uninit();
	}

	// パーティクル情報破棄
	CParticle::Unload();

	// ブロック情報削除
	CBlock::DeleteAll();

	// ブロック番号削除
	CBlock::DeleteIdx();

	// レンダラー終了
	CRenderer *pRenderer = CRenderer::GetInstance();

	if (pRenderer != nullptr)
	{
		pRenderer->Uninit();
	}

	// 入力マネージャー終了
	CInputManager *pInputManager = CInputManager::GetInstance();

	if (pInputManager != nullptr)
	{
		pInputManager->Uninit();
	}

	CSound *pSound = CSound::GetInstance();

	if (pSound != nullptr)
	{// サウンドの終了・破棄
		pSound->Uninit();
		pSound = nullptr;
	}

	// デバッグプロシージャの終了
	CDebugProc *pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc != nullptr)
	{
		pDebugProc->Uninit();
	}

	if (m_pLight != nullptr)
	{// ライトの終了・破棄
		m_pLight->Uninit();

		delete m_pLight;
		m_pLight = nullptr;
	}

	if (m_pCamera != nullptr)
	{// カメラの終了・破棄
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = nullptr;
	}

	// テクスチャの終了・破棄
	CTexture *pTexture = CTexture::GetInstance();

	if (pTexture != nullptr)
	{
		pTexture->Unload();

		delete pTexture;
		pTexture = nullptr;
	}

	// モデル破棄
	CModel::Unload();
}

//=====================================================
// 更新処理
//=====================================================
void CManager::Update(void)
{
	// フェード更新
	CFade *pFade = CFade::GetInstance();

	if (pFade != nullptr)
	{
		pFade->Update();
	}

	if (m_pScene != nullptr)
	{
		m_pScene->Update();
	}

	// 入力マネージャー更新
	CInputManager *pInputManager = CInputManager::GetInstance();

	if (pInputManager != nullptr)
	{
		pInputManager->Update();
	}

	CSound *pSound = CSound::GetInstance();

	if (pSound != nullptr)
	{// サウンドの更新
		pSound->Update();
	}

	// デバッグプロシージャの更新
	CDebugProc *pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc != nullptr)
	{
		pDebugProc->Update();
	}

	// ライトの更新
	if (m_pLight != nullptr)
	{
		m_pLight->Update();
	}

	// カメラの更新
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}
}

//=====================================================
// 描画処理
//=====================================================
void CManager::Draw(void)
{
	if (m_pScene != nullptr)
	{
		m_pScene->Draw();
	}

	// レンダラー描画
	CRenderer *pRenderer = CRenderer::GetInstance();

	if (pRenderer != nullptr)
	{
		pRenderer->Draw();
	}
}

//=====================================================
// モード設定
//=====================================================
void CManager::SetMode(CScene::MODE mode)
{
	CSound *pSound = CSound::GetInstance();

	if (pSound != nullptr)
	{// 音の停止
		pSound->Stop();
	}

	if (m_pCamera != nullptr)
	{
		m_pCamera->Init();
	}

	// シーンを破棄
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();

		delete m_pScene;
		m_pScene = nullptr;
	}

	// シーン生成
	m_pScene = CScene::Create(mode);

	// モード設定
	m_mode = mode;
}

namespace Manager
{
//=====================================================
// カメラ取得(ショートカット)
//=====================================================
CCamera *GetCamera(void)
{
	CManager *pManager = CManager::GetInstace();

	if (pManager != nullptr)
		return pManager->GetCamera();

	return nullptr;
}

//=====================================================
// ライト取得(ショートカット)
//=====================================================
CLight *GetLight(void)
{
	CManager *pManager = CManager::GetInstace();

	if (pManager != nullptr)
		return pManager->GetLight();

	return nullptr;
}

//=====================================================
// モード設定(ショートカット)
//=====================================================
void SetMode(CScene::MODE mode)
{
	CManager *pManager = CManager::GetInstace();

	if (pManager != nullptr)
		pManager->SetMode(mode);
}

//=====================================================
// モード取得(ショートカット)
//=====================================================
CScene::MODE GetMode(void)
{
	CManager *pManager = CManager::GetInstace();

	if (pManager != nullptr)
		return pManager->GetMode();

	return CScene::MODE::MODE_TITLE;
}

//=====================================================
// スコア設定(ショートカット)
//=====================================================
void SetScore(int nScore)
{
	CManager *pManager = CManager::GetInstace();

	if (pManager != nullptr)
		pManager->SetScore(nScore);
}

//=====================================================
// スコア取得(ショートカット)
//=====================================================
int GetScore(void)
{
	CManager *pManager = CManager::GetInstace();

	if (pManager != nullptr)
		return pManager->GetScore();

	return 0;
}

//=====================================================
// デルタタイム取得(ショートカット)
//=====================================================
float GetDeltaTime(void)
{
	CManager *pManager = CManager::GetInstace();

	if (pManager != nullptr)
		return pManager->GetDeltaTime();

	return 0.0f;
}
}