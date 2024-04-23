//*****************************************************
//
// カメラのビヘイビア[cameraBehavior.cpp]
// Author:��山桃也
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
const float RATE_ADVANCE_FOLLOW = 1.5f;	// 追従時、移動量に対する先を見る割合
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

	pInfoCamera->posRDest = pos + move * RATE_ADVANCE_FOLLOW;

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