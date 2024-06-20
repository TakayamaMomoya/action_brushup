//*****************************************************
//
// スローの処理[slow.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "slow.h"
#include "debugproc.h"
#include "manager.h"
#include "universal.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const float DEFAULT_TIMESCALE = 1.0f;	// タイムスケールのデフォルト値
}

//*****************************************************
// 静的メンバ変数宣言
//*****************************************************
CSlow *CSlow::s_pSlow = nullptr;	// 自身のポインタ

//=====================================================
// コンストラクタ
//=====================================================
CSlow::CSlow() : m_fTimeScale(0.0f), m_fTimeSlow(0.0f)
{

}

//=====================================================
// デストラクタ
//=====================================================
CSlow::~CSlow()
{

}

//=====================================================
// 生成処理
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
// 初期化処理
//=====================================================
HRESULT CSlow::Init(void)
{
	m_fTimeScale = DEFAULT_TIMESCALE;

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CSlow::Uninit(void)
{
	s_pSlow = nullptr;

	Release();
}

//=====================================================
// 更新処理
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
// 描画処理
//=====================================================
void CSlow::Draw(void)
{
#ifdef _DEBUG	// デバッグ表示
	CDebugProc *pDebugProc = CDebugProc::GetInstance();

	if (pDebugProc != nullptr)
	{
		pDebugProc->Print("\nタイムスケール[%f]",m_fTimeScale);
	}
#endif
}

//=====================================================
// スケールの設定
//=====================================================
void CSlow::SetScale(float fScale)
{
	if (fScale >= 0.0f)
	{
		m_fTimeScale = fScale;
	}
}

//=====================================================
// スロータイムの設定
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
// タイムスケール取得（ショートカット関数）
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