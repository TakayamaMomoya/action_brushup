//*****************************************************
//
// ボスのステイトの処理[enemybossState.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "enemybossState.h"
#include "enemyboss.h"
#include "sound.h"
#include "manager.h"
#include "missile.h"
#include "universal.h"
#include "bullet.h"
#include "camera.h"
#include "cameraState.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const float MID_POINT = 2740.0f;	// ボス戦ステージの中央X座標
const float FLOAT_HEIGHT = 180.0f;	// 浮かんでいる高さ
const float WIDTH_STAGE = 160.0f;	// ステージの幅
const float DELAY_MISSILE = 0.2f;	// ミサイル発射のディレイ
const float INITIALSPEED_MISSILE = 3.0f;	// ミサイルの初速
const int NUM_MISSILE = 3;	// ミサイルの発射数
const float SHOT_HEIGHT = 30.0f;	// 射撃時の高さ
const float BULLET_SPEED = 2.0f;	// 弾の速度
const float BULLET_SIZE = 2.5f;	// 弾の大きさ
const float DELAY_SHOT = 0.02f; // 射撃のディレイ
}

//************************************************************
// 出現状態
//************************************************************
//=====================================================
// コンストラクタ
//=====================================================
CEnemyBossStateApper::CEnemyBossStateApper()
{

}

//=====================================================
// デストラクタ
//=====================================================
CEnemyBossStateApper::~CEnemyBossStateApper()
{

}

//=====================================================
// 初期化処理
//=====================================================
void CEnemyBossStateApper::Init(CEnemyBoss *pBoss)
{
	// モーション設定
	pBoss->SetMotion(CEnemyBoss::MOTION_APPER);
	pBoss->InitPose(CEnemyBoss::MOTION_APPER);

	// 出現地点合わせ
	pBoss->SetMatrix();

	pBoss->FollowCollision();
}

//=====================================================
// 更新
//=====================================================
void CEnemyBossStateApper::Update(CEnemyBoss *pBoss)
{
	bool bFinish = pBoss->IsFinish();

	if (bFinish)
	{
		pBoss->SwitchState();

		// カメラをボス戦に切り替え
		CCamera *pCamera = Manager::GetCamera();

		if (pCamera != nullptr)
		{
			pCamera->ChangeState(new CCameraStateBossBattle);
		}
	}
}

//************************************************************
// 射撃攻撃
//************************************************************
//=====================================================
// コンストラクタ
//=====================================================
CEnemyBossStateShot::CEnemyBossStateShot() : m_fTimerAttack(0.0f)
{

}

//=====================================================
// デストラクタ
//=====================================================
CEnemyBossStateShot::~CEnemyBossStateShot()
{

}

//=====================================================
// 初期化処理
//=====================================================
void CEnemyBossStateShot::Init(CEnemyBoss *pBoss)
{
	int nRand = rand() % 2;

	if (nRand == 1)
	{
		pBoss->SetMotion(CEnemyBoss::MOTION_SHOT_UPPER);
	}
	else
	{
		pBoss->SetMotion(CEnemyBoss::MOTION_SHOT_UNDER);
	}

	D3DXVECTOR3 pos = pBoss->GetPosition();

	D3DXVECTOR3 posDest;

	if (pos.x < MID_POINT)
	{// 左にいた場合
		posDest = { MID_POINT - WIDTH_STAGE, FLOAT_HEIGHT + SHOT_HEIGHT, 0.0f };
	}
	else
	{
		posDest = { MID_POINT + WIDTH_STAGE, FLOAT_HEIGHT + SHOT_HEIGHT, 0.0f };
	}

	pBoss->SetPosDest(posDest);
}

//=====================================================
// 更新
//=====================================================
void CEnemyBossStateShot::Update(CEnemyBoss *pBoss)
{
	pBoss->RotDest();

	pBoss->FollowDest();

	bool bFinish = pBoss->IsFinish();
	int nKey = pBoss->GetKey();

	if (nKey == 3)
	{
		m_fTimerAttack += Manager::GetDeltaTime();

		if (m_fTimerAttack >= DELAY_SHOT)
		{
			D3DXMATRIX mtxWeapon = *pBoss->GetParts(CEnemyBoss::IDX_WEAPON)->m_pParts->GetMatrix();
			D3DXMATRIX mtxMazzle;
			D3DXMATRIX mtxMazzleVec;

			// オフセットの位置設定
			universal::SetOffSet(&mtxMazzle, mtxWeapon, D3DXVECTOR3(5.0f, -30.0f, 0.0f));
			universal::SetOffSet(&mtxMazzleVec, mtxMazzle, D3DXVECTOR3(0.0f, -1.0f, 0.0f));

			// 差分のベクトルを取得
			D3DXVECTOR3 posMazzle =
			{
				mtxMazzle._41,
				mtxMazzle._42,
				mtxMazzle._43,
			};
			D3DXVECTOR3 posBullet =
			{
				mtxMazzleVec._41,
				mtxMazzleVec._42,
				mtxMazzleVec._43,
			};

			D3DXVECTOR3 vecBullet = posBullet - posMazzle;

			D3DXVec3Normalize(&vecBullet, &vecBullet);

			vecBullet *= BULLET_SPEED;

			CBullet::Create(posMazzle, vecBullet, 400, CBullet::TYPE_ENEMY, false, 10.0f, 5.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

			m_fTimerAttack = 0;

			CSound *pSound = CSound::GetInstance();

			if (pSound != nullptr)
			{
				pSound->Play(CSound::LABEL_SE_BULLET);
			}
		}
	}

	if (bFinish)
	{// 状態切り替え
		// 目標位置追従
		pBoss->SwitchState();
	}
}

//************************************************************
// ミサイル攻撃
//************************************************************
//=====================================================
// コンストラクタ
//=====================================================
CEnemyBossStateMissile::CEnemyBossStateMissile() : m_fTimerAttack(0.0f), m_nCntAttack(0)
{

}

//=====================================================
// デストラクタ
//=====================================================
CEnemyBossStateMissile::~CEnemyBossStateMissile()
{

}

//=====================================================
// 初期化処理
//=====================================================
void CEnemyBossStateMissile::Init(CEnemyBoss *pBoss)
{
	pBoss->SetMotion(CEnemyBoss::MOTION_MISSILE);
}

//=====================================================
// 更新
//=====================================================
void CEnemyBossStateMissile::Update(CEnemyBoss *pBoss)
{
	D3DXVECTOR3 pos = pBoss->GetPosition();

	// プレイヤーの方を向く処理
	pBoss->RotDest();

	// 目標位置の設定処理
	D3DXVECTOR3 posDest;

	if (pos.x < MID_POINT)
	{// 左にいた場合
		posDest = { MID_POINT - WIDTH_STAGE, FLOAT_HEIGHT, 0.0f };
	}
	else
	{
		posDest = { MID_POINT + WIDTH_STAGE, FLOAT_HEIGHT, 0.0f };
	}

	pBoss->SetPosDest(posDest);
	
	bool bArrival = pBoss->FollowDest();	// 目標位置追従

	// ミサイルを発射する
	if (bArrival)
	{// 目標地点に着いていたら攻撃する
		m_fTimerAttack += Manager::GetDeltaTime();

		if (DELAY_MISSILE <= m_fTimerAttack)
		{// 一定時間ごとにミサイルを発射
			// ミサイルの生成
			D3DXVECTOR3 posMissile = pBoss->GetMtxPos(CEnemyBoss::IDX_SHOULDER_L);
			CMissile *pMissile = CMissile::Create(posMissile);

			if (pMissile != nullptr)
			{
				// ミサイルに初速を与える
				pMissile->SetMove(D3DXVECTOR3(0.0f, INITIALSPEED_MISSILE, 0.0f));
			}

			// 発射音再生
			Sound::Play(CSound::LABEL_SE_MISSILE);

			m_fTimerAttack = 0;	// タイマーのリセット
			m_nCntAttack++;	// カウンターの加算

			if (m_nCntAttack >= NUM_MISSILE)
			{// 状態を切り替える
				pBoss->SwitchState();
			}
		}
	}
}

//************************************************************
// 突進攻撃
//************************************************************
//=====================================================
// コンストラクタ
//=====================================================
CEnemyBossStateDash::CEnemyBossStateDash()
{

}

//=====================================================
// デストラクタ
//=====================================================
CEnemyBossStateDash::~CEnemyBossStateDash()
{

}

//=====================================================
// 初期化処理
//=====================================================
void CEnemyBossStateDash::Init(CEnemyBoss *pBoss)
{
	pBoss->SetMotion(CEnemyBoss::MOTION_DASH);

	D3DXVECTOR3 pos = pBoss->GetPosition();

	D3DXVECTOR3 posDest;

	if (pos.x < MID_POINT)
	{// 左にいた場合
		posDest = { MID_POINT + WIDTH_STAGE, FLOAT_HEIGHT, 0.0f };
	}
	else
	{// 右にいた場合
		posDest = { MID_POINT - WIDTH_STAGE, FLOAT_HEIGHT, 0.0f };
	}

	pBoss->SetPosDest(posDest);
}

//=====================================================
// 更新
//=====================================================
void CEnemyBossStateDash::Update(CEnemyBoss *pBoss)
{
	bool bFinish = pBoss->IsFinish();

	if (bFinish)
	{// 状態切り替え
		// 目標位置追従
		bool bEnd = pBoss->FollowDest();

		if (bEnd)
		{
			pBoss->SwitchState();
		}
	}
	else
	{
		pBoss->RotDest();
	}
}