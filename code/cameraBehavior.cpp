//*****************************************************
//
// カメラのビヘイビア[cameraBehavior.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "cameraBehavior.h"
#include "camera.h"
#include "player.h"
#include "motion.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const float ANGLE_FOLLOW = D3DX_PI * 0.4f;	// 追従時の角度
const float SPEED_FOLLOW = 0.3f;	// 追従時の速度
const float RATE_ADVANCE_FOLLOW = 10.0f;	// 追従時、移動量に対する先を見る割合
const float DIST_FOLLOW_DEFAULT = 100.0f;	// 追従時のデフォルトカメラ距離
const float DIST_APPER_PLAYER = 100.0f;	// プレイヤー出現時のカメラ距離
}

//====================================================
// コンストラクタ
//====================================================
CCameraBehavior::CCameraBehavior()
{

}

//====================================================
// デストラクタ
//====================================================
CCameraBehavior::~CCameraBehavior()
{

}

//************************************************************
// プレイヤー追従
//************************************************************

//====================================================
// コンストラクタ
//====================================================
CCameraBehaviorFollowPlayer::CCameraBehaviorFollowPlayer()
{

}

//====================================================
// デストラクタ
//====================================================
CCameraBehaviorFollowPlayer::~CCameraBehaviorFollowPlayer()
{

}

//====================================================
// 初期化
//====================================================
void CCameraBehaviorFollowPlayer::Init(CCamera *pCamera)
{
	pCamera->SetDist(DIST_FOLLOW_DEFAULT);
}

//====================================================
// 更新処理
//====================================================
void CCameraBehaviorFollowPlayer::Update(CCamera *pCamera)
{
	// カメラの振動
	pCamera->Quake();

	// プレイヤー取得
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
	{
		return;
	}

	CCamera::Camera *pInfoCamera = pCamera->GetCamera();
	D3DXVECTOR3 pos = pPlayer->GetPosition();
	D3DXVECTOR3 move = pPlayer->GetMove();

	// 注視点は横のみ移動方向を先読みして動く
	pInfoCamera->posRDest.x = pos.x + move.x * RATE_ADVANCE_FOLLOW;
	pInfoCamera->posRDest.z = pos.z + move.z * RATE_ADVANCE_FOLLOW;
	pInfoCamera->posRDest.y = pos.y;

	// 注視点からの極座標に視点を設定
	pInfoCamera->posVDest =
	{
		pInfoCamera->posRDest.x + sinf(ANGLE_FOLLOW) * sinf(D3DX_PI) * pInfoCamera->fLength,
		pInfoCamera->posRDest.y + cosf(ANGLE_FOLLOW) * pInfoCamera->fLength,
		pInfoCamera->posRDest.z + sinf(ANGLE_FOLLOW) * cosf(D3DX_PI) * pInfoCamera->fLength
	};

	// 位置の補正
	pInfoCamera->posR += (pInfoCamera->posRDest - pInfoCamera->posR) * SPEED_FOLLOW;
	pInfoCamera->posV += (pInfoCamera->posVDest - pInfoCamera->posV) * SPEED_FOLLOW;
}

//************************************************************
// プレイヤー登場
//************************************************************

//====================================================
// コンストラクタ
//====================================================
CCameraBehaviorApperPlayer::CCameraBehaviorApperPlayer()
{

}

//====================================================
// デストラクタ
//====================================================
CCameraBehaviorApperPlayer::~CCameraBehaviorApperPlayer()
{

}

//====================================================
// 初期化
//====================================================
void CCameraBehaviorApperPlayer::Init(CCamera *pCamera)
{
	pCamera->SetDist(DIST_APPER_PLAYER);
}

//====================================================
// 更新処理
//====================================================
void CCameraBehaviorApperPlayer::Update(CCamera *pCamera)
{
	// プレイヤー取得
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
	{
		return;
	}

	CCamera::Camera *pInfoCamera = pCamera->GetCamera();
	D3DXVECTOR3 pos = pPlayer->GetPosition();

	pInfoCamera->posR = pos;

	pInfoCamera->posV =
	{
		pInfoCamera->posRDest.x + sinf(ANGLE_FOLLOW) * sinf(D3DX_PI) * pInfoCamera->fLength,
		pInfoCamera->posRDest.y + cosf(ANGLE_FOLLOW) * pInfoCamera->fLength,
		pInfoCamera->posRDest.z + sinf(ANGLE_FOLLOW) * cosf(D3DX_PI) * pInfoCamera->fLength
	};
}