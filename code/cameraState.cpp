//*****************************************************
//
// カメラのステイト[cameraState.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "cameraState.h"
#include "camera.h"
#include "player.h"
#include "motion.h"
#include "player.h"
#include "enemyboss.h"
#include "universal.h"

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
const float DIST_MIN_BOSS = 85.0f;	// ボス戦のときの最小距離
}

//====================================================
// コンストラクタ
//====================================================
CCameraState::CCameraState()
{

}

//====================================================
// デストラクタ
//====================================================
CCameraState::~CCameraState()
{

}

//************************************************************
// プレイヤー追従
//************************************************************

//====================================================
// コンストラクタ
//====================================================
CCameraStateFollowPlayer::CCameraStateFollowPlayer()
{

}

//====================================================
// デストラクタ
//====================================================
CCameraStateFollowPlayer::~CCameraStateFollowPlayer()
{

}

//====================================================
// 初期化
//====================================================
void CCameraStateFollowPlayer::Init(CCamera *pCamera)
{
	pCamera->SetDist(DIST_FOLLOW_DEFAULT);
}

//====================================================
// 更新処理
//====================================================
void CCameraStateFollowPlayer::Update(CCamera *pCamera)
{
	// カメラの振動
	pCamera->Quake();

	// プレイヤー取得
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
	{
		return;
	}

	CCamera::S_InfoCamera *pInfoCamera = pCamera->GetInfo();
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
CCameraStateApperPlayer::CCameraStateApperPlayer()
{

}

//====================================================
// デストラクタ
//====================================================
CCameraStateApperPlayer::~CCameraStateApperPlayer()
{

}

//====================================================
// 初期化
//====================================================
void CCameraStateApperPlayer::Init(CCamera *pCamera)
{
	pCamera->SetDist(DIST_APPER_PLAYER);
}

//====================================================
// 更新処理
//====================================================
void CCameraStateApperPlayer::Update(CCamera *pCamera)
{
	// プレイヤー取得
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == nullptr)
	{
		return;
	}

	CCamera::S_InfoCamera *pInfoCamera = pCamera->GetInfo();
	D3DXVECTOR3 pos = pPlayer->GetPosition();

	pInfoCamera->posR = pos;

	pInfoCamera->posV =
	{
		pInfoCamera->posRDest.x + sinf(ANGLE_FOLLOW) * sinf(D3DX_PI) * pInfoCamera->fLength,
		pInfoCamera->posRDest.y + cosf(ANGLE_FOLLOW) * pInfoCamera->fLength,
		pInfoCamera->posRDest.z + sinf(ANGLE_FOLLOW) * cosf(D3DX_PI) * pInfoCamera->fLength
	};
}

//************************************************************
// ボス戦時の動き
//************************************************************

//====================================================
// コンストラクタ
//====================================================
CCameraStateBossBattle::CCameraStateBossBattle()
{

}

//====================================================
// デストラクタ
//====================================================
CCameraStateBossBattle::~CCameraStateBossBattle()
{

}

//====================================================
// 初期化
//====================================================
void CCameraStateBossBattle::Init(CCamera *pCamera)
{

}

//====================================================
// 更新処理
//====================================================
void CCameraStateBossBattle::Update(CCamera *pCamera)
{
	CPlayer *pPlayer = CPlayer::GetInstance();
	CEnemyBoss *pBoss = CEnemyBoss::GetInstance();

	if (pBoss == nullptr || pPlayer == nullptr)
		return;

	CMotion *pPlayerBody = pPlayer->GetBody();

	if (pPlayerBody == nullptr)
		return;

	// ボスとプレイヤーの中心を映す
	D3DXVECTOR3 posPlayer = pPlayerBody->GetMtxPos(0);
	D3DXVECTOR3 posBoss = pBoss->GetMtxPos(CEnemyBoss::IDXPARTS::IDX_HEAD);

	D3DXVECTOR3 vecDiff = posBoss - posPlayer;

	D3DXVECTOR3 posMid = posPlayer + vecDiff * 0.5f;

	// 注視点を中間位置に設定
	CCamera::S_InfoCamera *pInfoCamera = pCamera->GetInfo();
	
	pInfoCamera->posRDest = posMid;

	// カメラの画角内に二体を収める
	float fAngleView = pInfoCamera->fViewAngle;

	float fAngle = (D3DX_PI - D3DXToRadian(fAngleView)) * 0.5f;	// キャラクター間のベクトルの端からの角度

	float fLengthDiff = D3DXVec3Length(&vecDiff) * 0.5f;	// プレイヤーと敵の距離の半分

	float fLengthToPosV = fLengthDiff / tanf(universal::DegreeToRadian(fAngleView * 0.5f));

	universal::LimitValue(&fLengthToPosV, FLT_MAX, DIST_MIN_BOSS);

	// 注視点からの極座標に視点を設定
	pInfoCamera->posVDest =
	{
		pInfoCamera->posRDest.x + sinf(ANGLE_FOLLOW) * sinf(D3DX_PI) * fLengthToPosV,
		pInfoCamera->posRDest.y + cosf(ANGLE_FOLLOW) * fLengthToPosV,
		pInfoCamera->posRDest.z + sinf(ANGLE_FOLLOW) * cosf(D3DX_PI) * fLengthToPosV
	};

	// 位置の補正
	pInfoCamera->posR += (pInfoCamera->posRDest - pInfoCamera->posR) * SPEED_FOLLOW;
	pInfoCamera->posV += (pInfoCamera->posVDest - pInfoCamera->posV) * SPEED_FOLLOW;
}