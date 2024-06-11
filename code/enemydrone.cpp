//*****************************************************
//
// 動く敵の処理[enemyshot.cpp]
// Author:髙山桃也
//
//*****************************************************

//*****************************************************
// インクルード
//*****************************************************
#include "main.h"
#include "enemydrone.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "universal.h"
#include "debugproc.h"
#include "game.h"
#include "bullet.h"

//*****************************************************
// 定数定義
//*****************************************************
namespace
{
const int INITIAL_LIFE = 5;	// 初期体力
const int INITIAL_SCORE = 500;	// 初期スコア
const float DELAY_SHOT = 2.0f;	// 射撃カウンター
const float BULLET_SPEED = 2.0f;	// 弾の速度
const float BULLET_SIZE = 1.0f;	// 弾の大きさ
const float DIST_ATTACK = 200.0f;	// 攻撃する範囲
}

//=====================================================
// コンストラクタ
//=====================================================
CEnemyDrone::CEnemyDrone()
{

}

//=====================================================
// デストラクタ
//=====================================================
CEnemyDrone::~CEnemyDrone()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CEnemyDrone::Init(void)
{
	// 継承クラスの初期化
	CEnemyNormal::Init();

	// 初期の体力設定
	SetLife(INITIAL_LIFE);

	// スコア設定
	SetScore(INITIAL_SCORE);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CEnemyDrone::Uninit(void)
{
	CEnemyNormal::Uninit();
}

//=====================================================
// 更新処理
//=====================================================
void CEnemyDrone::Update(void)
{
	// 位置を保存
	SetPositionOld(GetPosition());

	// 継承クラスの更新
	CEnemyNormal::Update();
	
	// 攻撃の管理
	ManageAttack();

	// 目標を向く処理
	RotDest();
}

//=====================================================
// 攻撃管理
//=====================================================
void CEnemyDrone::ManageAttack(void)
{
	if (GetAttackCounter() >= DELAY_SHOT)
	{// 一定時間経過したら攻撃
		D3DXVECTOR3 pos = GetPosition();
		D3DXVECTOR3 posTarget = { 0.0f,0.0f,0.0f };
		float fRot = GetRot().y;
		D3DXVECTOR3 move;

		CPlayer *pPlayer = CPlayer::GetInstance();

		if (pPlayer != nullptr)
		{
			// プレイヤーの腰パーツを目標にする
			CMotion *pMotion = pPlayer->GetBody();
			posTarget = pMotion->GetMtxPos(0);

			// 差分ベクトルの正規化したものを弾の移動量にする
			move = posTarget - pos;

			float fLength = D3DXVec3Length(&move);

			if (fLength > DIST_ATTACK)
			{// 一定距離以内でないと攻撃しない
				return;
			}

			D3DXVec3Normalize(&move, &move);

			move *= BULLET_SPEED;
		}

		// 弾の生成
		CBullet::Create(pos, move, 500, CBullet::TYPE_ENEMY, false, BULLET_SIZE, 2.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

		SetAttackCounter(0);
	}
}

//=====================================================
// 描画処理
//=====================================================
void CEnemyDrone::Draw(void)
{
	CEnemyNormal::Draw();
}