//*****************************************************
//
// カメラの処理[camera.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "manager.h"
#include "renderer.h"
#include "main.h"
#include "camera.h"
#include "inputkeyboard.h"
#include "inputmouse.h"
#include "debugproc.h"
#include "game.h"
#include "player.h"
#include "cameraState.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const float INITIAL_FOV = 45.0f;	// 初期の視野角
const float DECREASE_QUAKE = 0.03f;	// 揺れの収まる速度
const int RATE_FLOAT = 100;	// float型の倍率
}

//====================================================
// コンストラクタ
//====================================================
CCamera::CCamera()
{
	ZeroMemory(&m_camera, sizeof(S_InfoCamera));
	m_pState = nullptr;
}

//====================================================
// デストラクタ
//====================================================
CCamera::~CCamera()
{

}

//====================================================
// 初期化処理
//====================================================
HRESULT CCamera::Init(void)
{
	m_camera.fViewAngle = INITIAL_FOV;
	m_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CCamera::Uninit(void)
{

}

//====================================================
// 更新処理
//====================================================
void CCamera::Update(void)
{
	if (m_pState != nullptr)
	{
		m_pState->Update(this);
	}
}

//====================================================
// デバッグ処理
//====================================================
void CCamera::Debug(void)
{

}

//====================================================
// 振動処理
//====================================================
void CCamera::Quake(void)
{
	// 画面振動
	if (m_camera.nTimerQuake > 0)
	{
		// 時間を減らす
		m_camera.nTimerQuake--;

		// 視点注視点を動かしてカメラを揺らす
		m_camera.posV.x += (float)(rand() % RATE_FLOAT) / (float)RATE_FLOAT * m_camera.fQuakeSize * sinf(m_camera.rot.y);
		m_camera.posV.y += (float)(rand() % RATE_FLOAT) / (float)RATE_FLOAT * m_camera.fQuakeSize;
		m_camera.posV.z += (float)(rand() % RATE_FLOAT) / (float)RATE_FLOAT * m_camera.fQuakeSize * cosf(m_camera.rot.y);

		m_camera.posR.x += (float)(rand() % RATE_FLOAT) / (float)RATE_FLOAT * m_camera.fQuakeSize * sinf(m_camera.rot.y);
		m_camera.posR.y += (float)(rand() % RATE_FLOAT) / (float)RATE_FLOAT * m_camera.fQuakeSize;
		m_camera.posR.z += (float)(rand() % RATE_FLOAT) / (float)RATE_FLOAT * m_camera.fQuakeSize * cosf(m_camera.rot.y);

		// 徐々に揺れのサイズを小さくする
		m_camera.fQuakeSize += (0.0f - m_camera.fQuakeSize) * DECREASE_QUAKE;
	}
}

//====================================================
// 振動設定
//====================================================
void CCamera::SetQuake(float fQuakeSize, int nTime)
{
	if (fQuakeSize > 0.0f)
	{
		// 揺れる時間代入
		m_camera.nTimerQuake = nTime;

		// 揺れの大きさ代入
		m_camera.fQuakeSize = fQuakeSize;
	}
}

//====================================================
// 視点設定
//====================================================
void CCamera::SetPosV(void)
{
	m_camera.posV =
	{
		m_camera.posR.x + sinf(m_camera.rot.x) * sinf(m_camera.rot.y) * m_camera.fLength,
		m_camera.posR.y + cosf(m_camera.rot.x) * m_camera.fLength,
		m_camera.posR.z + sinf(m_camera.rot.x) * cosf(m_camera.rot.y) * m_camera.fLength
	};
}

//====================================================
// 注視点設定
//====================================================
void CCamera::SetPosR(void)
{
	m_camera.posR =
	{
		m_camera.posV.x - sinf(m_camera.rot.x) * sinf(m_camera.rot.y) * m_camera.fLength,
		m_camera.posV.y - cosf(m_camera.rot.x) * m_camera.fLength,
		m_camera.posV.z - sinf(m_camera.rot.x) * cosf(m_camera.rot.y) * m_camera.fLength
	};
}

//====================================================
// 設定処理
//====================================================
void CCamera::SetCamera(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	// プロジェクションマトリックス初期化
	D3DXMatrixIdentity(&m_camera.mtxProjection);

	// プロジェクションマトリックス作成
	D3DXMatrixPerspectiveFovLH(&m_camera.mtxProjection,
		D3DXToRadian(m_camera.fViewAngle),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		MIN_DRAW,
		MAX_DRAW);

	// プロジェクションマトリックス設定
	pDevice->SetTransform(D3DTS_PROJECTION,&m_camera.mtxProjection);

	// ビューマトリックス初期化
	D3DXMatrixIdentity(&m_camera.mtxView);

	// ビューマトリックス作成
	D3DXMatrixLookAtLH(&m_camera.mtxView,
		&m_camera.posV,
		&m_camera.posR,
		&m_camera.vecU);

	// ビューマトリックス設定
	pDevice->SetTransform(D3DTS_VIEW, &m_camera.mtxView);

#ifdef _DEBUG	// デバッグ表示
	CDebugProc::GetInstance()->Print("\n視点の位置：[%f,%f,%f]", m_camera.posV.x, m_camera.posV.y, m_camera.posV.z);
	CDebugProc::GetInstance()->Print("\n注視点の位置：[%f,%f,%f]", m_camera.posR.x, m_camera.posR.y, m_camera.posR.z);
	CDebugProc::GetInstance()->Print("\nカメラ距離：[%f]", m_camera.fLength);
#endif
}

//====================================================
// ステイトの変更
//====================================================
void CCamera::ChangeState(CCameraState *pBehavior)
{
	if (m_pState != nullptr)
	{
		delete m_pState;
		m_pState = nullptr;
	}

	m_pState = pBehavior;

	if (m_pState != nullptr)
	{
		m_pState->Init(this);
	}
}

//====================================================
// 情報取得
//====================================================
CCamera::S_InfoCamera *CCamera::GetInfo(void)
{
	return &m_camera;
}